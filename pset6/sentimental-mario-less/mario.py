from cs50 import get_int

# Only allows inputs from 1 to 8
while (True):
    height = get_int("Height: ")
    if (height > 0 and height < 9):
        break

# Print the pyramid
for i in range(height):
    for j in range(1, height - i, 1):
        print(end=" ")

    for k in range(i + 1):
        print("#", end="")

    print()