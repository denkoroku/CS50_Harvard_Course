#include <cs50.h>
#include <stdio.h>

void makeHash(void);

int main(void)
{
    int h;

//get height from user
    do
    {
        h = get_int("Height: ");
    }

//check height is between 1 and 8
    while (h > 8 || h < 1);

//draw the blocks
    for (int row = 1; row <= h; row++)
    {
        for (int space = 0; space < (h - row); space ++)
        {
            printf(" ");
        }
        for (int hash = 1; hash <= row; hash++)
        {
            makeHash();
        }

        printf("  ");

        for (int hash = 1; hash <= row; hash++)
        {
            makeHash();
        }


        printf("\n");
    }
}


//do the number of hashes

void makeHash(void)
{

    printf("#");
}

