#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    // Open file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    int idx = 0;

    // Read plate numbers in a loop
    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        plates[idx] = malloc(7 * sizeof(char));
        if (plates[idx] == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(infile);
            return 3;
        }

        strcpy(plates[idx], buffer);
        idx++;
    }

    // Print plate numbers
    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    // Free memory
    for (int i = 0; i < 8; i++)
    {
        free(plates[i]);
    }

    // Close file
    fclose(infile);

    return 0;
}
