#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
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
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            float b = image[i][j].rgbtBlue;

            float sepiaRed = 0.393 * r + 0.769 * g + 0.189 * b;
            float sepiaGreen = 0.349 * r + 0.686 * g + 0.168 * b;
            float sepiaBlue = 0.272 * r + 0.534 * g + 0.131 * b;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE original = image[i][j];
            image[i][j] = image[i][width - (j + 1)]; // First pixel gets last pixel to the middle
            image[i][width - (j + 1)] = original; // same time last pixel get first pixel to the middle.
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary array to store original image
    RGBTRIPLE temp[height][width];
    int red;
    int blue;
    int green;
    int counter;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = 0;
            blue = 0;
            green = 0;
            counter = 0;
            for (int h = -1; h < 2; h++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if ((i + h) >= 0 && (i + h) <= height && (j + b) >= 0 && (j + b) < width) // do this for pixels within range, otherwise ignore.
                    {
                        red += image[i + h][j + b].rgbtRed; 
                        blue += image[i + h][j + b].rgbtBlue;
                        green += image[i + h][j + b].rgbtGreen;
                        counter ++;
                    }
                }
            }
            unsigned int rounding_bias = (counter - 1) / 2;
            temp[i][j].rgbtRed = round((red + rounding_bias) / counter);
            temp[i][j].rgbtBlue = round((blue + rounding_bias) / counter);
            temp[i][j].rgbtGreen = round((green + rounding_bias) / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
