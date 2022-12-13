from sys import exit
from cs50 import get_int

# Prompt for input
card = get_int("Number: ")

# Calculate the length of credit card
length = len(str(card))

# Convert card to string to access first digits
digits = str(card)

# Checks if the card length is valid
if length != 13 and length != 15 and length != 16:
    print("INVALID")
    exit(1)

# Set variables to checksum
last_digit = 0
first_digit = 0
sum_first = 0
sum_last = 0

# Calculate checksum
while card > 0:

    # Gets the second-to-last and first digit
    last_digit = card % 10
    card //= 10

    first_digit = card % 10
    card //= 10

    # Digits calculation
    multi_first = first_digit * 2
    sum_first += multi_first // 10 + multi_first % 10
    sum_last += last_digit

total = sum_first + sum_last

# Prints AMEX, MASTERCARD or VISA if valid
if total % 10 != 0:
    print("INVALID")
    exit(2)
else if digits[0] == '3' and (digits[1] == '4' or digits[1] == '7'):
    print("AMEX")
elif digits[0] == '5' and (digits[1] > '0' and digits[1] < '6'):
    print("MASTERCARD")
elif digits[0] == '4':
    print("VISA")
else:
    print("INVALID")