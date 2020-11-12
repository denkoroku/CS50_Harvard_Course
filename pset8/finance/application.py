import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


# Make sure API key is set pk_ec3a7aa2bc2a42c7a991776d3c155fc9
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")



@app.route("/")
@login_required
def index():
    portfolio = db.execute("SELECT * FROM portfolio WHERE person_id =:uid", uid = session['user_id'])
    grandTotal = 0
    for row in portfolio:
        symbol = row["symbol"]
        data = lookup(symbol)
        shares = row["quantity"]
        price = data["price"]
        total = shares * price
        grandTotal = grandTotal + total
        displayGrandTotal= "{:.2f}".format(grandTotal)

    return render_template("index.html", portfolio = portfolio, grandTotal= displayGrandTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        # lookup the infrmation
        data = lookup(request.form.get("symbol"))

        # save some variables
        symbol = lookup(request.form.get("symbol"))
        numberShares = request.form.get("shares")
        price = data["price"]
        dbInfo = db.execute("SELECT * FROM users WHERE id=:uid", uid = session['user_id'])
        cash = (dbInfo[0]["cash"])
        cost = price * int(numberShares)
        name = data["name"]
        portfolio = db.execute("SELECT * FROM portfolio WHERE person_id =:uid", uid = session['user_id'])

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # ensure symbol exists
        elif data == None:
            return apology("symbol not found", 403)

        # check a number of shares is entered
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 403)

        # check the number is positive integer
        elif int(numberShares) <= 0:
            return apology("must provide a positive number of shares", 403)

        # check if the number is an integer
        #elif not numberShares.is_integer():
            #return apology("must provide an integer", 403)

        #check if has enough money
        elif cost > cash:
            return apology("You don't have enough money" , 403)

        # complete the purchase
        else:

            # subtract cost from persons cash
            newCash = cash - cost

            # update  cash as cash for that person
            db.execute("UPDATE users SET cash = :newCash WHERE id = :id", newCash=newCash, id=int(session['user_id']))

            #add to portfolio
            #seeif the shares are already in the portfolio
            InPortfolio = db.execute("SELECT * FROM portfolio WHERE person_id =:uid AND symbol=:symbol", uid = session['user_id'], symbol = request.form.get("symbol"))
            #if they are not in the portfolio add them
            if InPortfolio == None:
                db.execute("INSERT INTO portfolio (person_id, quantity, symbol, name, price) VALUES (:person_id, :quantity, :symbol, :name, :price)",
                person_id = int(session['user_id']), quantity=numberShares, symbol=request.form.get("symbol"), name=name, price=price)
            #if they are already in portfolio then increase the quantity
            else:
                quantityShares = InPortfolio[0]['quantity'] + int(numberShares)
                db.execute ("UPDATE portfolio SET quantity = :quantity WHERE person_id =:uid AND symbol=:symbol", uid = session['user_id'], symbol=request.form.get("symbol"), quantity = quantityShares)

            #add to transactions
            now = datetime.now()
            date = now.strftime("%d/%m/%Y %H:%M:%S")
            db.execute("INSERT INTO transactions (person_id, quantity, symbol, price, transacted) VALUES (:person_id, :quantity, :symbol, :price, :transacted)",
                person_id = int(session['user_id']), quantity=numberShares, symbol=request.form.get("symbol"), price=price, transacted=date)
        return redirect("/")
    # if it is a GET request
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    transactions = db.execute("SELECT * FROM transactions WHERE person_id = :id", id = int(session['user_id']))
    return render_template("history.html", transactions = transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        #lookup the infrmation
        data = lookup(request.form.get("symbol"))
        return render_template("quoted.html", name=data["name"], symbol=data["symbol"], price=data["price"])

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Get user from database
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure username does not exist
        elif len(rows) != 0:
            return apology("Username already used", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        #Ensure password confirmed
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 403)

        #Ensure passwords match
        elif (request.form.get("password") != request.form.get("confirmation")):
            return apology("passwords must match", 403)

        # write the user into the database
        username=request.form.get("username")
        password=request.form.get("password")
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users(username, hash) VALUES(:username, :hash)", username=username, hash=hash)

        # Get user from database
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))


        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        # lookup the infrmation
        data = lookup(request.form.get("symbol"))

        # save some variables
        symbol = request.form.get("symbol")
        numberShares = request.form.get("shares")
        price = data["price"]
        dbInfo = db.execute("SELECT * FROM users WHERE id=:uid", uid = session['user_id'])
        cash = (dbInfo[0]["cash"])
        value = price * int(numberShares)
        name = data["name"]

        #check if has the shares to sell
        #figure out what shares they already hold
        portfolio = db.execute("SELECT * FROM portfolio WHERE person_id =:uid", uid = session['user_id'])
        holding = 0
        for row in portfolio:
            folioSymbol = row["symbol"]
            data = lookup(symbol)
            shares = row["quantity"]
            price = data["price"]
            total = shares * price

            if folioSymbol == symbol:
                holding = holding + shares

        #if holding is less than sell quantity
        if holding < int(numberShares):
            return apology("you dont have that many", 403)

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # ensure symbol exists
        elif data == None:
            return apology("symbol not found", 403)

        #ensure they have them in their portfolio
        elif holding == 0 or holding == None:
            return apology("You dont have shares of that type", 403)

        # check a number of shares is entered
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 403)

        # check the number is positive integer
        elif int(numberShares) <= 0:
            return apology("must provide a positive number of shares", 403)

        # complete the sale
        else:

            # add value to persons cash
            newCash = cash + value

            # update  cash as cash for that person
            db.execute("UPDATE users SET cash = :newCash WHERE id = :id", newCash=newCash, id=int(session['user_id']))

            #remove from portfolio if selling all
            if int(request.form.get("shares")) == holding:
                db.execute("DELETE  FROM portfolio WHERE person_id =:uid AND symbol=:symbol", uid = session['user_id'], symbol=request.form.get("symbol"))

            #remove only some
            if int(numberShares) < holding:
                remainingShares = holding - int(numberShares)
                db.execute("UPDATE portfolio SET quantity = :quantity WHERE person_id =:uid AND symbol=:symbol", uid = session['user_id'], symbol=request.form.get("symbol"), quantity = remainingShares)

            #add to transactions
            now = datetime.now()
            date = now.strftime("%d/%m/%Y %H:%M:%S")

            negNumShares= int(numberShares) *-1
            db.execute("INSERT INTO transactions (person_id, quantity, symbol, price, transacted) VALUES (:person_id, :quantity, :symbol, :price, :transacted)",
                person_id = int(session['user_id']), quantity=negNumShares, symbol=request.form.get("symbol"), price=price, transacted=date)
        return redirect("/")



    # if it is a GET request
    else:
         #figure out what shares they already hold
        userPortfolio = db.execute("SELECT name,quantity FROM portfolio WHERE person_id=:uid", uid = int(session['user_id']))

        return render_template("sell.html", portfolio = userPortfolio)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
