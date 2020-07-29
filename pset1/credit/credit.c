#include <cs50.h>
#include <stdio.h>


int main(void)
{
    long num;

//ask for the number

    num = get_long("Number: ");

//checksum is ok
    long total1, total2, total3;
    long calcNum, calcNum2;
    int digit;

//adding all the other numbers times 2
    calcNum = num;
    total1 = 0;

    while (calcNum > 0)
    {
        digit = ((calcNum / 10) % 10) * 2;
        if (digit < 10)
        {
            total1 += digit;
        }
        else
        {
            total1 = total1 + ((digit % 10) + ((digit / 10) % 10));
        }
        calcNum = calcNum / 100;
    }

//adding the remaining digits
    calcNum2 = num;
    total2 = 0;
    while (calcNum2 > 0)
    {
        total2 += (calcNum2) % 10;
        calcNum2 = calcNum2 / 100;
    }

//grand total for digits
    total3 = (total2 + total1) % 10;

//check if it is valid
    if (total3 == 0)
    {

//is it amex
        if (((num / 10000000000000) == 37) || ((num / 10000000000000) == 34))
        {
            printf("AMEX\n");
        }

//is it mastercard
        else if (((num / 100000000000000) == 51) || ((num / 100000000000000) == 52) || ((num / 100000000000000) == 53)
                 || ((num / 100000000000000) == 54) || ((num / 100000000000000) == 55))
        {
            printf("MASTERCARD\n");
        }

//is it visa
        else if (((num / 1000000000000000) == 4) || ((num / 1000000000000) == 4))
        {
            printf("VISA\n");
        }

// it is invalid
        else
        {
            {
                printf("INVALID\n");
            }
        }
    }


    else
    {
        printf("INVALID\n");

    }

}


