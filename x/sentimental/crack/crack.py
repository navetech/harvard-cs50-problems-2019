# Crack passwords

import sys
import cs50
import crypt


# Main function
def main():

    # Check the correct program's usage
    if len(sys.argv) != 2:
        print("Usage: python crack.py hash")
        return 1

    # Get the hashed password
    pwHashed = sys.argv[1]

    # Verify all possible passwords from 1 to 5 letters (upper and lower case)
    for lenPw in range(1, 6):
        pw = crack_pw(pwHashed, "", lenPw)
        if pw != "":
            print(pw)
            return 0


# Verify (recursively) all possible passwords of a given length
# (made only by upper and lower case letters)
def crack_pw(pwHashed, pwPre, lenLeft):

    # If left length greater than zero
    if lenLeft > 0:

        # For each upper and lower case letter,
        # apend this letter to the password and verify all possible passwords of this length minus 1
        aA = ["a", "A"]
        for l in aA:
            o = ord(l)
            for i in range(o, o + 26):
                pw = crack_pw(pwHashed, pwPre + chr(i), lenLeft - 1)
                if pw != "":
                    return pw
        return ""

    # if left length not greater than 0
    else:

        # If password correspond to hashed password
        if crypt.crypt(pwPre, pwHashed) == pwHashed:

            # return found password
            return pwPre

        # If do not correspond
        else:

            # Return empty password (not found)
            return ""


if __name__ == "__main__":
    main()
