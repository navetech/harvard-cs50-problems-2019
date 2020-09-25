// Figure out the minimum number of coins which with a change can be made

#include <stdio.h>
#include <math.h>

#include <cs50.h>

int main(void)
{
    // Prompt user for the change owed
    // If change invalid, prompt again
    int change_in_cents;
    do
    {
        float change = get_float("Change owed: ");
        
        // Convert dollars to cents and round to the nearest penny
        change_in_cents = (int) round(change * 100);
        
    } while (change_in_cents < 1);
    
    int num_of_coins = 0;
    
    // add number of quarters to number of coins
    num_of_coins += change_in_cents / 25;
    change_in_cents %= 25;
    
    // add number of dimes to number of coins
    num_of_coins += change_in_cents / 10;
    change_in_cents %= 10;
    
    // add number of nickels to number of coins
    num_of_coins += change_in_cents / 5;
    change_in_cents %= 5;
    
    // add number of pennies to number of coins
    num_of_coins += change_in_cents;
    
    printf("%i\n", num_of_coins);
}
