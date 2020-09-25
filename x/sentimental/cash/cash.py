# Calculates the minimum number of coins required to give a user change

import cs50

# Get change from the user
while True:
    change = cs50.get_float("Change owed: ")
    if change >= 0:
        break

# Convert change to cents
changeInCents = round(change * 100)

# List of available coin
coinsAvailable = [1, 5, 10, 25]

# Initialize number of coins
numberOfCoins = 0

# While there is change owed
while changeInCents > 0:

    # Select next coin
    while True:
        coin = coinsAvailable.pop()
        if changeInCents >= coin:
            break

    # Add up number of coins according change owed and selected coin
    numberOfCoins += changeInCents // coin

    # Update change according selected coin
    changeInCents %= coin

# Print number of coins required
print(numberOfCoins)
