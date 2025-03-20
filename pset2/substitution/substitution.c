#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validate_key(string key);
char substitute(char c, string key);

int main(int argc, string argv[])
{
    // Check the number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key is valid
    if (!validate_key(argv[1]))
    {
        printf("Invalid key!\n");
        return 1;
    }

    // Prompt the user for plaintext
    string text = get_string("plaintext:  ");

    // For each character in the plaintext:
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Substitute the character if it's a letter
        text[i] = substitute(text[i], argv[1]);
    }

    // Print the ciphertext
    printf("ciphertext: %s\n", text);

    return 0;
}

bool validate_key(string key)
{
    // Check if the key contains 26 characters
    if (strlen(key) != 26)
    {
        return false;
    }

    // Check if the key contains only alphabetic characters
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }

    // Check if the key contains each letter exactly once
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                return false;
            }
        }
    }

    return true;
}

char substitute(char c, string key)
{
    char new_c;
    if (islower(c))
    {
        new_c = tolower(key[c - 'a']);
        return new_c;
    }
    else if (isupper(c))
    {
        new_c = toupper(key[c - 'A']);
        return new_c;
    }
    else
    {
        return c;
    }
}
