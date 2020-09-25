from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # TODO

    # Get lines from a
    linesA = set(a.split('\n'))

    # Get lines from b
    linesB = set(b.split('\n'))

    # Find lines in both a and b
    linesBoth = set(line for line in linesA if line in linesB)
    return linesBoth


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO

    # Get sentences from a
    sentencesA = sent_tokenize(a)

    # Get sentences from b
    sentencesB = sent_tokenize(b)

    # Find sentences in both a and b
    sentencesBoth = set(sentence for sentence in sentencesA if sentence in sentencesB)
    return sentencesBoth


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO

    # Get substrings from a
    substringsA = getSubstrings(a, n)

    # Get substrings from b
    substringsB = getSubstrings(b, n)

    # Find substrings in both a and b
    substringsBoth = set(substring for substring in substringsA if substring in substringsB)
    return substringsBoth


def getSubstrings(a, n):
    """Return substrings of length n in a string"""

    # Get substrings from string
    substrings = set()
    for i in range(0, len(a) - n + 1):
        substrings.add(a[i:i + n])

    return substrings

