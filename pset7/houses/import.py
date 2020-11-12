import cs50
import csv
import sys

db = cs50.SQL("sqlite:///students.db")

# if there is not 1 arguments after file name break
while(len(sys.argv) != 2):
    #  remind user of how to run the file
    print('Usage: python import.py data.csv ')
    break

# open the CSV file given in args
with open(sys.argv[1], mode='r') as data_file:
    data = csv.reader(data_file, delimiter=",")

# for each row parse the name
    # split into first middle and last names
    for row in data:
        namestring = row[0]

# check how many names if 2 make it first and last
    # use 'None' value if no middle name present
        allNames = namestring.split()
        if (len(allNames) == 2):
            allNames.insert(1, 'None')
        elif (len(allNames) == 1):
            allNames.clear()

# delete the namestring
        del row[0]

# replace with individual names from allNames

        allData = allNames + row

    # insert each student into the students table of the database
    # use db.EXECUTE to insert new row into table
        if (len(allData) == 2):
            badData = 1
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                        allData[0], allData[1], allData[2], allData[3], allData[4])