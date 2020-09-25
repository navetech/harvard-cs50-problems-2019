# Encrypt messages using Caesar’s cipher

import sys
import cs50

# Check the correct program's usage
if len(sys.argv) != 2:
    print("Usage: python caesar.py k")
    sys.exit(1)

# Get the cipher key
k = int(sys.argv[1])

# Get plaintext from the user
plaintext = cs50.get_string("plaintext: ")

# Cipher plaintext
ciphertext = ""
for c in plaintext:
    if c.isalpha():
        if c.isupper():
            i = ord('A')
        else:
            i = ord('a')
        c = chr(((ord(c) - i + k) % 26) + i)
    ciphertext += c

# Print ciphertext
print("ciphertext:", ciphertext)
