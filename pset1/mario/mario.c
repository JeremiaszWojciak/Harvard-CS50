#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for the pyramid's height
    int height;
    do
    {
        height = get_int("Set pyramid's height (1-8): ");
    }
    while (height < 1 || height > 8);

    // Print a pyramid of that height
    for (int row = 0; row < height; row++)
    {
        for (int ls = 0; ls < height - row - 1; ls++)
        {
            printf(" ");
        }

        for (int lh = 0; lh < row + 1; lh++)
        {
            printf("#");
        }

        printf("  ");

        for (int rh = 0; rh < row + 1; rh++)
        {
            printf("#");
        }

        printf("\n");
    }
}

