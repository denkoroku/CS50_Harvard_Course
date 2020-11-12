from cs50 import get_int
import math

# ask for the number
num = get_int("Number: ")

# adding all the other numbers times 2
calcNum = num
total1 = 0

while (calcNum > 1):
    digit = math.floor(((calcNum / 10) % 10)) * 2
    if (digit < 10):
        total1 += digit
    else:
        total1 = total1 + (math.floor(digit % 10) + (math.floor(digit / 10) % 10))

    calcNum = calcNum / 100

# adding the remaining digits
calcNum2 = num
total2 = 0
while (calcNum2 > 1):
    total2 += math.floor((calcNum2) % 10)
    calcNum2 = calcNum2 / 100

# grand total for digits
total3 = (total2 + total1) % 10

# check if it is valid
if (total3 == 0):

    # is it amex
    if ((math.floor(num / 10000000000000) == 37) or (math.floor(num / 10000000000000) == 34)):
        print("AMEX\n")

# is it mastercard
    elif ((math.floor(num / 100000000000000) == 51) or (math.floor(num / 100000000000000) == 52) or (math.floor(num / 100000000000000) == 53) or (math.floor(num / 100000000000000) == 54) or (math.floor(num / 100000000000000) == 55)):
        print("MASTERCARD\n")

# is it visa
    elif ((math.floor(num / 1000000000000000) == 4) or (math.floor(num / 1000000000000) == 4)):
        print("VISA\n")

# it is invalid
    else:
        print("INVALID\n")

else:
    print("INVALID\n")