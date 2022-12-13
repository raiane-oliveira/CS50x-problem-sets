from cs50 import get_float


def main():
    cash = get_cash()
    coins = 0

    # Calculate quarters
    while cash >= 0.25:
        cash -= 0.25
        coins += 1

    # Calculate dimes
    while cash >= 0.10:
        cash -= 0.10
        coins += 1

    # Calculate nickels
    while cash >= 0.005:
        cash -= 0.05
        coins += 1

    # Calculate pennies
    while cash >= 0.001:
        cash -= 0.01
        coins += 1

    # Prints how many coins will be used for change
    print(coins)


# Ask how much money the customer owes
def get_cash():
    while True:
        c = get_float("Change owed: ")
        if c >= 0:
            break
    return c


main()