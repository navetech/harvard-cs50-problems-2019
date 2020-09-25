# Censors messages that contain words that appear on a list of supplied "banned words."

from cs50 import get_string
from sys import argv
from sys import exit


def main():

    # TODO
    # Check the correct program's usage:

    # Check if there is only one command-line argument
    if len(argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)

    # Get banned words from the file and put them in banned words dictionary
    bannedWordsFile = argv[1]
    with open(bannedWordsFile) as f:
        # bannedWordsDictionary = list(map(str.rstrip, list(f)))
        bannedWordsDictionary = set(map(str.lower, map(str.rstrip, set(f))))

    # Get message from user
    message = get_string("What message would you like to censor?\n")

    # Get words from message
    messageWords = message.split()

    # Censor message
    for word in messageWords:
        if word.lower() in bannedWordsDictionary:
            print("*" * len(word), end=" ")
        else:
            print(word, end=" ")

    print()


if __name__ == "__main__":
    main()
