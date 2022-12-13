from cs50 import get_int


def main():
    height = get_height()

    # Print the half-pyramids
    for i in range(height):
        for j in range(1, height - i, 1):
            print(end=" ")

        # Print the first pyramid
        for k in range(i + 1):
            print("#", end="")

        print(end="  ")

        # Print the second pyramid
        for l in range(i + 1):
            print("#", end="")

        print()


# Only allows inputs from 1 to 8
def get_height():
    while True:
        h = get_int("Height: ")
        if (h > 0) and (h < 9):
            break
    return h


main()