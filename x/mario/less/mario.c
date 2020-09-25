#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for an integer value of height
    // If height less than 1 or greater than 8
       // Go back to step 1
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    // Iterate from 1 to height
      // On iteration i, print i hashes and a newline
    for (int i = 1; i <= height; i++)
    {
        for (int j = height - i; j >= 1; j--)
        {
            printf(" ");
        }
        for ( int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    

}
