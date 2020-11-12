import csv
import sys


# if there are not 2 arguments after file name
while(len(sys.argv) != 3):
    #  remind user of how to run the file
    print('Usage: python dna.py data.csv sequence.txt')
    break

# open sequence file
with open(sys.argv[2]) as sequence_file:

    # read contents of sequence file to memory
    sequence = sequence_file.read()

# open database file
with open(sys.argv[1], mode='r') as database_file:
    database = csv.reader(database_file, delimiter=",")

    # from the database get the fragments of DNA to look for
    DNA_strss = []
    for row in database:

        # exclude first one as it is 'name'
        i = 1

        # loop over the others but only accept those of 4 characters or more
        while (i < len(row)):
            strs = row[i]
            if (len(strs) >= 4):
                DNA_strss.append(strs)
            i = i+1

# set up a list to contain the counts
fragment_count = []

# for each fragment
for i in DNA_strss:

    # Counting occurrences of the fragment in the sequence
    strss_count = 0
    original = i
    while i in sequence:
        strss_count += 1
        i = i + original
    fragment_count.append(strss_count)

# open database file
with open(sys.argv[1], mode='r') as database_file:
    database = csv.reader(database_file, delimiter=",")
    found = 0
# for each row in database
    for row in database:
        # if the numbers in row match the fragment count
        if (row[1] == str(fragment_count[0]) and row[2] == str(fragment_count[1]) and row[3] == str(fragment_count[2])):
            print(row[0])
            found = 1

if (found == 0):
    print('no match')
