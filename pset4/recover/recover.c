#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Size of data block
const int BUFFER_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open memory card.\n");
        return 1;
    }

    uint8_t buffer[BUFFER_SIZE];
    FILE *jpg = NULL;
    char filename[8];
    int jpg_count = 0;

    // Read input file until there is no data left
    while (fread(&buffer, sizeof(uint8_t), BUFFER_SIZE, card) == BUFFER_SIZE)
    {
        // Check for JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a file is already open, close it
            if (jpg != NULL)
            {
                fclose(jpg);
            }

            // Prepare new filename and open new JPEG file
            sprintf(filename, "%03i.jpg", jpg_count);
            jpg = fopen(filename, "w");
            if (jpg == NULL)
            {
                printf("Could not open JPG file.\n");
                return 1;
            }
            jpg_count++;

            // Write the current block to the new file
            fwrite(&buffer, sizeof(uint8_t), BUFFER_SIZE, jpg);
        }
        else if (jpg != NULL)
        {
            // Continue writing to the current JPEG
            fwrite(&buffer, sizeof(uint8_t), BUFFER_SIZE, jpg);
        }
    }

    // Close files
    if (jpg != NULL)
    {
        fclose(jpg);
    }
    fclose(card);

    return 0;
}
