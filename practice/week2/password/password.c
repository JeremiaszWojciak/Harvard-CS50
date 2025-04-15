// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and "
               "symbol\n");
    }
}

bool valid(string password)
{
    bool lowercase = false, uppercase = false, number = false, symbol = false;

    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (islower(password[i]))
        {
            lowercase = true;
        }
        else if (isupper(password[i]))
        {
            uppercase = true;
        }
        else if (isdigit(password[i]))
        {
            number = true;
        }
        else if (!isalpha(password[i]) && !isdigit(password[i]))
        {
            symbol = true;
        }
    }

    if (lowercase && uppercase && number && symbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}

