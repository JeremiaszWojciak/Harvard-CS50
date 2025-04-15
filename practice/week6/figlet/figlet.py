import sys
import random
from pyfiglet import Figlet


def main():
    # Create the Figlet object
    figlet = Figlet()

    # If no arguments are passed, use a random font
    if len(sys.argv) == 1:
        font = random.choice(figlet.getFonts())
        figlet.setFont(font=font)

    # If two arguments are passed, check for the font flag and name
    elif len(sys.argv) == 3:
        if sys.argv[1] not in ["-f", "--font"]:
            sys.exit("Invalid flag. Use -f or --font.")
        if sys.argv[2] not in figlet.getFonts():
            sys.exit("Invalid font name.")
        # Set the specified font
        figlet.setFont(font=sys.argv[2])

    else:
        sys.exit("Usage: figlet.py [-f FONT]")

    # Prompt the user for input text
    text = input("Input: ")

    # Print text in specified font
    print(figlet.renderText(text))


main()
