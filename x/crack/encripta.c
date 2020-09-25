#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <crypt.h>

const int PASSWORD_LEN_MAX = 5;    // Maximum number of characters in a password

// Encript a password
int main(int argc, string argv[])
{
    // If there is not only one command-line argument (the password)
    if (argc != 2)
    {
        // Report usage message 
        printf("Usage: ./encripta password\n");
 
        // Return error code
        return 1;
    }

    // If the password is too long
    if (strlen(argv[1]) > PASSWORD_LEN_MAX)
    {
        // Report usage message 
        printf("Usage: ./encripta password\n");
 
        // Return error code
        return 1;
    }

    // If the password is not apphabetical
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (! isalpha(argv[1][i]))
        {
            // Report usage message 
            printf("Usage: ./encripta password\n");
 
            // Return error code
            return 1;
        }
    }

    // Encrypt the password
    string salt = "50";
    string h = crypt(argv[1], salt);
    printf("%s\n", h);
                
}
