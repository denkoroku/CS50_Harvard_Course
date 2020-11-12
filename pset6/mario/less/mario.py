from cs50 import get_int

# get the height from user make it height variable
height = 0

while height < 1 or height > 8:
    height = get_int("Height: ")
else:
    # make some variables for drawing the hash and spaces
    hash = 1
    space = height - 1

# loop to print but only if height in correct range

    for i in range(height):
        print(" " * space, end="")
        print("#" * hash)
        space = space - 1
        hash = hash + 1