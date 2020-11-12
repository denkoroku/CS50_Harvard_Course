from cs50 import get_string
import string


# ask for the string
text = get_string("Text: ")

# count number of letters

lettersOnly = [c.lower() for c in text if c.isalpha()]
letterCount = len(lettersOnly)

# count number of words
wordCount = len(text.split())

# count sentences
fullstopCount = text.count(".")
exclaimCount = text.count("!")
questionCount = text.count("?")
sentenceCount = (fullstopCount + exclaimCount + questionCount)

# letters per word *100
L = ((letterCount / wordCount) * 100)

#  of sentences per 100 words
S = ((sentenceCount / wordCount) * 100)

# calculate index
index = ((0.0588 * L) - (0.296 * S) - 15.8)

# output grade
grade = round(index)

# output for less than 1
if (grade < 1):
    print("Before Grade 1\n")

# output for more than 16
elif (grade >= 16):
    print("Grade 16+\n")

# main output
else:
    print(f"Grade {grade}")