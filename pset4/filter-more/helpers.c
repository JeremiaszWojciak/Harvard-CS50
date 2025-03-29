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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Sobel kernels for horizontal (Gx) and vertical (Gy) edge detection
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Initialize gradient accumulators for each color
            int gxBlue = 0, gxGreen = 0, gxRed = 0;
            int gyBlue = 0, gyGreen = 0, gyRed = 0;

            // Loop over the 3×3 neighborhood
            for (int dh = -1; dh <= 1; dh++)
            {
                for (int dw = -1; dw <= 1; dw++)
                {
                    int ch = h + dh;
                    int cw = w + dw;

                    RGBTRIPLE pixel;

                    // Use black for out-of-bounds neighbors
                    if (ch >= 0 && ch < height && cw >= 0 && cw < width)
                    {
                        pixel = copy[ch][cw];
                    }
                    else
                    {
                        pixel.rgbtBlue = 0;
                        pixel.rgbtGreen = 0;
                        pixel.rgbtRed = 0;
                    }

                    // Get the corresponding weights from the kernels
                    int weightX = Gx[dh + 1][dw + 1];
                    int weightY = Gy[dh + 1][dw + 1];

                    // Apply Sobel operator for each color channel
                    gxBlue += pixel.rgbtBlue * weightX;
                    gxGreen += pixel.rgbtGreen * weightX;
                    gxRed += pixel.rgbtRed * weightX;

                    gyBlue += pixel.rgbtBlue * weightY;
                    gyGreen += pixel.rgbtGreen * weightY;
                    gyRed += pixel.rgbtRed * weightY;
                }
            }

            // Calculate gradient magnitude for each channel
            int blue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));
            int green = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int red = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));

            // Clamp values to the maximum 255
            image[h][w].rgbtBlue = blue > 255 ? 255 : blue;
            image[h][w].rgbtGreen = green > 255 ? 255 : green;
            image[h][w].rgbtRed = red > 255 ? 255 : red;
        }
    }
    return;
}
