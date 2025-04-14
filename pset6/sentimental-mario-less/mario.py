from cs50 import get_int

# Prompt the user for the pyramid's height
while True:
    height = get_int("Set pyramid's height (1-8): ")
    if height >= 1 and height <= 8:
        break

# Print a pyramid of that height
for row in range(height):
    for s in range(height - row - 1):
        print(" ", end="")
    for h in range(row + 1):
        print("#", end="")
    print()
