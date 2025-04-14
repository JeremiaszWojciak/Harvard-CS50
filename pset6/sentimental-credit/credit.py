from cs50 import get_string
import re


def main():
    card_number = get_string("Number: ")

    if calculate_checksum(card_number):
        check_card_type(card_number)
    else:
        print("INVALID")


# Function to calculate checksum using Luhn's Algorithm
def calculate_checksum(card_number):
    is_second = False
    checksum = 0

    for d in reversed(card_number):
        digit = int(d)

        if is_second:
            digit *= 2
            if digit > 9:
                digit = digit % 10 + 1

        checksum += digit
        is_second = not is_second

    return checksum % 10 == 0


# Function to determine the card type
def check_card_type(card_number):
    if re.fullmatch("^3[47][0-9]{13}$", card_number):
        print("AMEX")
    elif re.fullmatch("^5[1-5][0-9]{14}$", card_number):
        print("MASTERCARD")
    elif re.fullmatch("^4[0-9]{12}$|^4[0-9]{15}$", card_number):
        print("VISA")
    else:
        print("INVALID")


main()
