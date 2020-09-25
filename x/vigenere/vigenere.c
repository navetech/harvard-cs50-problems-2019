#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);

int main(int argc, string argv[])
{
    // If there is not only one command-line argument
    if (argc != 2)
    {
        // Report usage message 
        printf("Usage: ./vigenere keyword\n");
 
        // Return error code
        return 1;
    }

    // If any of the characters of the provided argument are not letters
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (! isalpha(argv[1][i]))
        {
            // Report usage message 
            printf("Usage: ./vigenere keyword\n");
 
            // Return error code
            return 1;
        }
    }

    // Prompt user for plaintext
    string plain_text = get_string("plaintext: ");

    // Point to the first character in the keyword
    int index = 0;
    
    // Iterate over each character of the plaintext:
    printf("ciphertext: ");
    for (int i = 0, len = strlen(plain_text); i < len; i++)
    {
        // Calculate the key for the current character in the keyword
        int key = shift(argv[1][index]);
    
        // If it is a uppercase lettter
        if (isupper(plain_text[i]))
        {
            // Rotate it, preserving case, then print out the rotated character
            printf("%c", (plain_text[i] - 'A' + key) % 26 + 'A');
            
            // Point to the next character in the keyword
            index = (index + 1) % strlen(argv[1]);
        }
        // If it is a lowercase lettter
        else if (islower(plain_text[i]))
        {
            // Rotate it, preserving case, then print out the rotated character
            printf("%c", (plain_text[i] - 'a' + key) % 26 + 'a');
            
            // Point to the next character in the keyword
            index = (index + 1) % strlen(argv[1]);
        }
        // If it is not a letter, print out the character as is
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
    
}

// Calculate the shift value for a character
//   Return Value:
//     (character - 'A'), if is upper case   
//     (character - 'a'), if is lower case
//     -1, if is not a letter   
int shift(char c)
{
    // If character is uppercase
    if (isupper(c))
    {
        // Return shift equals to character minus value of char 'A'
        return c - 'A';
    }
    // If character is lowercase
    else if (islower(c))
    {
        // Return shift equals to character minus value of char 'A'
        return c - 'a';
    }
    // If character is not a letter
    else
    {
        // Return -1 (error)
        return -1;
    }
}
