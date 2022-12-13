#include "helpers.h"
#include <math.h>

// Check if the value is greater than 255
int isGreater(int n);

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
    float countRed = 0, countGreen = 0, countBlue = 0, count = 0;

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
                    int h = k + i - 1;
                    int w = n + j - 1;

                    // Checks that out-of-border numbers will not be added
                    if (h >= 0 && h < height && w >= 0 && w < width)
                    {
                        countRed += copy[h][w].rgbtRed;
                        countGreen += copy[h][w].rgbtGreen;
                        countBlue += copy[h][w].rgbtBlue;
                        count++;
                    }
                }
            }

            // Change the image
            image[i][j].rgbtRed = round(countRed / count);
            image[i][j].rgbtGreen = round(countGreen / count);
            image[i][j].rgbtBlue = round(countBlue / count);

            // Reset count sums
            countRed = 0, countGreen = 0, countBlue = 0, count = 0;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int redGx = 0, greenGx = 0, blueGx = 0, redGy = 0, greenGy = 0, blueGy = 0;
    int Gx[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    int Gy[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };

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
            // Sobel operator
            for (int k = 0; k < 3; k++)
            {
                for (int n = 0; n < 3; n++)
                {
                    int h = k + i - 1;
                    int w = n + j - 1;

                    if (h >= 0 && w >= 0 && h < height && w < width)
                    {
                        // Calculate Gx
                        redGx += copy[h][w].rgbtRed * Gx[k][n];
                        greenGx += copy[h][w].rgbtGreen * Gx[k][n];
                        blueGx += copy[h][w].rgbtBlue * Gx[k][n];

                        // Calculate Gy
                        redGy += copy[h][w].rgbtRed * Gy[k][n];
                        greenGy += copy[h][w].rgbtGreen * Gy[k][n];
                        blueGy += copy[h][w].rgbtBlue * Gy[k][n];
                    }
                }
            }

            // Apply the new values to the image
            image[i][j].rgbtRed = isGreater(round(sqrt(pow(redGx, 2) + (pow(redGy, 2)))));
            image[i][j].rgbtGreen = isGreater(round(sqrt(pow(greenGx, 2) + (pow(greenGy, 2)))));
            image[i][j].rgbtBlue = isGreater(round(sqrt(pow(blueGx, 2) + (pow(blueGy, 2)))));

            // Reset Gx e Gy
            redGx = 0, greenGx = 0, blueGx = 0;
            redGy = 0, greenGy = 0, blueGy = 0;
        }
    }
    return;
}

// Check if the value is greater than 255
int isGreater(int n)
{
    if (n < 255)
    {
        return n;
    }
    return n = 255;
}