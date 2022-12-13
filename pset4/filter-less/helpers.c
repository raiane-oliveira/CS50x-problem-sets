#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average grayscale
            float average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average sepia for each value
            float sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            float sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            float sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            // Set the average to 255 if it's greater than 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
                if (sepiaGreen > 255)
                {
                    sepiaGreen = 255;
                    if (sepiaBlue > 255)
                    {
                        sepiaBlue = 255;
                    }
                }
            }

            // Change the image
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half = width / 2; j < half; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - (1 + j)];
            image[i][width - (1 + j)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int averageRed = 0, averageGreen = 0, averageBlue = 0, count = 0;
    float countRed = 0.0, countGreen = 0.0, countBlue = 0.0;

    // Copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Keep track of the pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Box blur
            for (int k = 0; k < 3; k++)
            {
                for (int n = 0; n < 3; n++)
                {
                    // Checks that out-of-border numbers will not be added
                    if ((k + i - 1) >= 0 && (k + i - 1) < height
                        && (n + j - 1) >= 0 && (n + j - 1) < width)
                    {
                        countRed += copy[(k + i) - 1][(n + j) - 1].rgbtRed;
                        countGreen += copy[(k + i) - 1][(n + j) - 1].rgbtGreen;
                        countBlue += copy[(k + i) - 1][(n + j) - 1].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculation of averages
            averageRed = round(countRed / count);
            averageGreen = round(countGreen / count);
            averageBlue = round(countBlue / count);

            // Change the image
            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtBlue = averageBlue;

            // Reset count sums
            countRed = 0;
            countGreen = 0;
            countBlue = 0;
            count = 0;
        }
    }
    return;
}