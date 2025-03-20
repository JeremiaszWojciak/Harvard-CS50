#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int key);

int main(int argc, string argv[])
{
    // Check the number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check whether every character in argv[1] is a digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt the user for plaintext
    string text = get_string("plaintext:  ");

    // For each character in the plaintext:
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Rotate the character if it's a letter
        text[i] = rotate(text[i], key);
    }

    // Print the ciphertext
    printf("ciphertext: %s\n", text);

    return 0;
}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int key)
{
    char new_c;
    if (islower(c))
    {
        new_c = (((c - 'a') + key) % 26) + 'a';
        return new_c;
    }
    else if (isupper(c))
    {
        new_c = (((c - 'A') + key) % 26) + 'A';
        return new_c;
    }
    else
    {
        return c;
    }
}
