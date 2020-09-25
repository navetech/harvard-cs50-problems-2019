#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <crypt.h>

const int HASH_LEN = 13;    // Number of characters in the hash
const int PASSWORD_LEN_MAX = 5;    // Maximum number of characters in a password

bool find_password(int len, string password, string hash);

// Crack a password
int main(int argc, string argv[])
{
    // If there is not only one command-line argument (the hash)
    if (argc != 2)
    {
        // Report usage message 
        printf("Usage: ./crack hash\n");
 
        // Return error code
        return 1;
    }

    // If there are not there are exactly number of characters in the hash
    if (strlen(argv[1]) != HASH_LEN)
    {
        // Report usage message 
        printf("Usage: ./crack hash\n");
 
        // Return error code
        return 1;
    }
    
    // Iterate over each possible size of the password:
    for (int i = 1; i <= PASSWORD_LEN_MAX; i++)
    {
        char password[i + 1];
        password[0] = '\0';
        bool found = false;
        found = find_password(i, password, argv[1]);
        if (found)
        {
            break;
        }
    }
    
    return 0;
    
}

// Find recursively a password given a length and a hash
//   Return Value:
//     true, found
//     false, not found
bool find_password(int len, string password, string hash)
{
    bool found = false;
    int len_ant = strlen(password);

    char s[2];
    s[1] = '\0';

    char c_ini[2];
    c_ini[0] = 'A';
    c_ini[1] = 'a';
    char c_fim[2];
    c_fim[0] = 'Z';
    c_fim[1] = 'z';

    // Iterate over all the uppercase and lowercase letters
    for (int i = 0; i < 2; i++)
    {
        s[0] = c_ini[i];
        // Iterate over all the same case letters
        do
        {
            // Append the letter to the password 
            password[len_ant] = '\0';
            strcat(password, s);
            found = false;
            
            // If is not the last character in the password
            if (len > 1)
            {
                // Find recursively a password for the given length minus 1
                found = find_password(len - 1, password, hash);
                if (found)
                {
                    return true;
                }
            }
            // Else is the last character in the password
            else
            {
                // Encrypt the password
                char salt[3];
                strncpy(salt, hash, 2);
                salt[2] = '\0';
                string h = crypt(password, salt);
                
                // If hashes match, return password found
                if (strcmp(hash + 2, h + 2) == 0)
                {
                    printf("%s\n", password);
                    return true;
                }
                
            }
        
            // Get the next letter 
            s[0]++;
        }
        while (s[0] <= c_fim[i]);
        
    }
    
    return found;

}
