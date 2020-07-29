#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int findPosition(int letter);
int sortCase(int plain, int key, int cypherchar);
bool checkFreeOfDuplicates(string key);
int position;


int main(int argc, string argv[])
{
    //check some sort of key is entered
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        //count number of letters in key
        int letterCount = 0;

        //for each character add one if it is a letter
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]))
            {
                letterCount ++;
            }
            //check no digits
            else if (isdigit(argv[1][i]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }

        //check there are 26 characters
        if (letterCount != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        //check for duplicate letters

        int doubleCheck = checkFreeOfDuplicates(argv[1]);
        if (doubleCheck == false)
        {
            printf("Key must contain 26 unique characters.\n");
            return 1;
        }


//ask for the string
        string plaintext = get_string("plaintext: ");

//convert cypher
        //for each character in plaintext

        printf("ciphertext: ");
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            //if its alpha then do crypto stuff
            if (isalpha(plaintext[i]))
            {
                position = findPosition(plaintext[i]);
                char cypherchar = argv[1][position];

                //sort the case
                char finalChar = sortCase(plaintext[i], argv[1][position], cypherchar);
                printf("%c", finalChar);
            }
            //if its not alpha then just print it
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");

    }
}

int findPosition(int letter)
{
//look up the position in the alphabet of the letter
    if (isupper(letter))
    {
        position = (int)letter - 65;
    }
    else if (islower(letter))
    {
        position = (int)letter - 97;
    }
//return the position
    return position;
}

int sortCase(int plain, int key, int cypherchar)
{
    //check to see if the case matches
    if ((islower(plain)) && (isupper(key)))
    {
        cypherchar = cypherchar + 32;
    }

    else if ((isupper(plain)) && (islower(key)))
    {
        cypherchar = cypherchar - 32;
    }
//return the correct case character
    return cypherchar;
}

bool checkFreeOfDuplicates(string key)
{
    int p = 0;
    //if string is unique return true

    //first grab a character
    for (int charCount = 0, n = strlen(key); charCount < n; charCount++)
    {
        //then check all the other characters
        for (int j = 0; j < strlen(key); j++)
        {
            //add one to p if character found
            if (key[charCount] == key[j])
            {
                p++;
            }
        }
    }
    if (p > 26)
    {
        printf("Double returns false\n");
        printf("p returns %i\n", p);
        return false;
    }

    else
    {
        printf("Double returns true\n");
        return true;
    }

}

