#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // If there is not only one command-line argument
    if (argc != 2)
    {
        // Report usage message 
        printf("Usage: ./caesar key\n");
 
        // Return error code
        return 1;
    }
    
    // If any of the characters of the provided argument are not digits
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (! isdigit(argv[1][i]))
        {
            // Report usage message 
            printf("Usage: ./caesar key\n");
 
            // Return error code
            return 1;
        }
    }
    
    //  Convert the provided argument from string to int
    int key = atoi(argv[1]);
    
    // Prompt user for plaintext
    string plain_text = get_string("plaintext: ");
    
    // Cypher plaintext ant print out ciphertext
    printf("ciphertext: ");
    for (int i = 0, len = strlen(plain_text); i < len; i++)
    {
        if (isupper(plain_text[i]))
        {
            printf("%c", (plain_text[i] - 'A' + key) % 26 + 'A');
        }
        else if (islower(plain_text[i]))
        {
            printf("%c", (plain_text[i] - 'a' + key) % 26 + 'a');
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
    
}
