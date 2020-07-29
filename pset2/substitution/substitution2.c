#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
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
        else if(isdigit(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    //check there are 26 characters
    if ((letterCount < 26) || (letterCount > 26))
    {
        printf("Key must contain 26 characters.\n");
    }

    //check some sort of key is entered
    else if (argc==1){
        printf("Usage: ./substitution key\n");
    }

//ask for the string
    string plaintext = get_string("plaintext: ");

//convert cypher
    //for each character in plaintext

printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
//if plaintext is uppercase
        if (isupper(plaintext[i]))
        {
            int upperposition= (int)plaintext[i];
            upperposition=upperposition-65;
//if key is lowercase
            if (islower (argv[1][i]))
            {
                char cypherchar=argv[1][upperposition];
                cypherchar=(int) cypherchar -32;
                printf("%c", cypherchar);
            }
//if key is uppercase
            if(isupper(argv[1][i]))
            {
                char cypherchar=argv[1][upperposition];
                printf("%c", cypherchar);
            }

        }
//if plaintext is lowercase
        else if(islower(plaintext[i]))
        {
            int position= (int)plaintext[i];
            position=position-97;

//if key is uppercase
            if(islower(argv[1][i]))
            {
               char cypherchar=argv[1][position];

                printf("%c", cypherchar);
            }
//if key is uppercase
            if(isupper(argv[1][i]))
            {
               char cypherchar=argv[1][position];
                cypherchar=(int) cypherchar +32;
                printf("%c", cypherchar);
            }

        }
        else{
            printf("%c", plaintext[i]);
        }
    }
printf("\n");

}