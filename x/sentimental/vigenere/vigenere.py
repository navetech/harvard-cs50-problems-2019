# Encrypt messages using Vigenère’s cipher

import sys
import cs50

# Check the correct program's usage:

# Check if there is only one command-line argument
if len(sys.argv) != 2:
    print("Usage: python vigenere.py k")
    sys.exit(1)

# Check if the single command-line argument: a keyword, k, is composed entirely of alphabetical characters
if not (sys.argv[1]).isalpha():
    print("Usage: python vigenere.py k")
    sys.exit(1)

# Get cipher key
key = sys.argv[1]

# Get plaintext from the user
plaintext = cs50.get_string("plaintext: ")

# Cipher plaintext:
ciphertext = ""

#  Point to 0th (first) key character
j = 0

# Iterate over plaintext characters:
for i in range(len(plaintext)):

    # get i-th plaintext character
    cp = plaintext[i]

    # if is alphabetical:
    if cp.isalpha():
        if cp.isupper():
            pi = ord('A')
        else:
            pi = ord('a')

        # get j-th key character
        ck = key[j]

        # Point to next key character
        j = (j + 1) % len(key)

        if ck.isupper():
            ki = ord('A')
        else:
            ki = ord('a')

        shift = ord(ck) - ki

        # Cipher plaintext character
        cp = chr(((ord(cp) - pi + shift) % 26) + pi)

    # Update ciphertext
    ciphertext += cp

# Print ciphertext
print("ciphertext:", ciphertext)
