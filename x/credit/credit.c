// Validate credit card number using Luhn's Algorithm

#include <stdio.h>

#include <cs50.h>

int main(void)
{
    // Prompt for a credit card number
    long number;
    do
    {
        number = get_long("Number: ");
    } while ( (number < 0) || (number > 9999999999999999) );

    // If number of digits less then 13, it is invalid
    if (number <= 999999999999)
    {
        printf("INVALID\n");
        return 0;
    }
    
    // If number of digits equals 14, it is invalid
    if ( (number > 9999999999999) && (number <= 99999999999999) )
    {
        printf("INVALID\n");
        return 0;
    }
    
    // Multiply every other digit by 2, starting with the number’s second-to-last digit,
    //  and then add those products’ digits together
    int sum = 0;
    long tmp = number / 10;
    while (tmp > 0)
    {
        int prod = 2 * (tmp % 10);
        while (prod > 0)
        {
            sum += prod % 10;
            prod /= 10;
        }
        
        tmp /= 100;
    }
    
    // Add the sum to the sum of the digits that weren’t multiplied by 2
    tmp = number;
    while (tmp > 0)
    {
        sum += tmp % 10;
        tmp /= 100;
    }
   
    // If the total’s last digit is 0 (or, put more formally,
    //  if the total modulo 10 is not congruent to 0), the number is invalid
    if ( (sum % 10) != 0 )
    {
        printf("INVALID\n");
        return 0;
    }

    // If number of digits equals 16 and card number starts with 4,
    //  it is Visa
    tmp = number / 1000000000000000;
    if (tmp == 4)
    {
        printf("VISA\n");
        return 0;
    }
    
    // If number of digits equals 16 and card number starts with 51, 52, 53, 54 or 55,
    //  it is Master Card
    tmp = number / 100000000000000;
    switch (tmp)
    {
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            printf("MASTERCARD\n");
            return 0;

        default:
            break;
    }
        
    // If number of digits equals 15 and card number starts with 34 or 37,
    //  it is American Express
    tmp = number / 10000000000000;
    switch (tmp)
    {
        case 34:
        case 37:
            printf("AMEX\n");
            return 0;

        default:
            break;
    }

    
    // If number of digits equals 13 and card number starts with 4,
    //  it is Visa
    tmp = number / 1000000000000;
    if (tmp == 4)
    {
        printf("VISA\n");
        return 0;
    }

}
