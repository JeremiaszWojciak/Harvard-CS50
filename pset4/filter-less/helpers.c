#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Calculate average of red, green, and blue channels
            int avg =
                round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);

            // Set all color channels to the average
            image[h][w].rgbtBlue = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Calculate sepia values using weighted sum of RGB channels
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen +
                                   .131 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen +
                                    .168 * image[h][w].rgbtBlue);
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen +
                                  .189 * image[h][w].rgbtBlue);

            // Clamp values to the maximum 255
            image[h][w].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[h][w].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row
    for (int h = 0; h < height; h++)
    {
        // Swap pixels horizontally across the center
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    // Loop through each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int blueTotal = 0, greenTotal = 0, redTotal = 0;
            int count = 0;

            // Loop over the 3×3 neighborhood
            for (int dh = -1; dh <= 1; dh++)
            {
                for (int dw = -1; dw <= 1; dw++)
                {
                    int ch = h + dh;
                    int cw = w + dw;

                    // Make sure neighbor pixel is within bounds
                    if (ch >= 0 && ch < height && cw >= 0 && cw < width)
                    {
                        blueTotal += copy[ch][cw].rgbtBlue;
                        greenTotal += copy[ch][cw].rgbtGreen;
                        redTotal += copy[ch][cw].rgbtRed;
                        count++;
                    }
                }
            }

            // Set blurred pixel value as average of valid neighbors
            image[h][w].rgbtBlue = round((float) blueTotal / count);
            image[h][w].rgbtGreen = round((float) greenTotal / count);
            image[h][w].rgbtRed = round((float) redTotal / count);
        }
    }
    return;
}
