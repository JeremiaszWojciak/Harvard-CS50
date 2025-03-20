#include <cs50.h>
#include <stdio.h>

int calculate_checksum(long card_number);
void check_card_type(long card_number);

int main(void)
{
    // Prompt the user for credit card number
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number <= 0);

    if (calculate_checksum(card_number))
    {
        check_card_type(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function to calculate checksum using Luhn's Algorithm
int calculate_checksum(long card_number)
{
    int is_second = 0;
    int checksum = 0;

    while (card_number > 0)
    {
        int digit = card_number % 10;
        if (is_second)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = digit % 10 + 1;
            }
        }
        checksum += digit;
        card_number /= 10;
        is_second = !is_second;
    }
    return (checksum % 10) == 0;
}

// Function to determine the card type
void check_card_type(long card_number)
{
    // Get the first two digits and length of the card number
    int length = 0;
    int first_digit = 0;
    int first_two_digits = 0;

    while (card_number > 0)
    {
        if (card_number < 10)
        {
            first_digit = card_number;
        }
        if (card_number >= 10 && card_number < 100)
        {
            first_two_digits = card_number;
        }
        card_number /= 10;
        length++;
    }

    // Check the card type based on length and first digits
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
