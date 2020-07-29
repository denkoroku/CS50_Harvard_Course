#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
//ask for the string
    string text = get_string(" Text: ");

//count number of letters
    float letterCount = 0;

//for each character add one if it is a letter
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letterCount ++;
        }
    }

//count number of words
    float wordCount = 1;

//for each character add one if it is a word
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isblank(text[i]) && isalpha(text[i + 1]))

//rediculous number of comments
        {
            wordCount ++;
        }

//adds a word even after ""
        else if (isblank(text[i]) && text[i + 1] == '"')
        {
            wordCount ++;
        }
    }
//this is bonkers comment

//count number of sentences
    float sentenceCount = 0;
//I really cant add more commients
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ('.') || text[i] == ('?') || text[i] == ('!'))
        {
            sentenceCount++;
        }
    }

//calculate the grade
//letters per word *100
    float L = (letterCount / wordCount) * 100;

//number of sentences per 100 words
    float S = ((sentenceCount / wordCount) * 100);

//calculate index
    float index = ((0.0588 * L) - (0.296 * S) - 15.8);

//output grade
    int grade = round(index);
//output for less than 1
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

//output for more than 16
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

//main output
    else
    {
        printf("Grade %i\n", grade);
    }
}
