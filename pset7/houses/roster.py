from cs50 import SQL
import sys

# if there is not 1 arguments after file name break
while(len(sys.argv) != 2):
    #  remind user of how to run the file
    print('Usage: python roster.py house')
    break

# query database for all students in house
db = SQL("sqlite:///students.db")
inputHouse = sys.argv[1].lower()
infoFromDb = db.execute('SELECT * from students WHERE lower(house) = "{}" ORDER BY last, first'.format(inputHouse))

# print out each students full name and birth year
for row in infoFromDb:
    first = row.get("first")
    middle = row.get("middle")
    last = row.get("last")
    year = row.get("birth")

# only show middle name if it is not none

    if (middle == "None"):
        fullname = first + " " + last
    else:
        fullname = first + " " + middle + " " + last

    print(f"{fullname}, born {year}")