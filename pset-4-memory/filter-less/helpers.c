#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find average of red, green, blue
            double grayscale_color = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            // Update red, green, blue values
            image[i][j].rgbtRed = round(grayscale_color);
            image[i][j].rgbtGreen = round(grayscale_color);
            image[i][j].rgbtBlue = round(grayscale_color);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            double sepia_r = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            if (sepia_r > 255)
            {
                sepia_r = 255;
            }
            double sepia_g = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            if (sepia_g > 255)
            {
                sepia_g = 255;
            }
            double sepia_b = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if (sepia_b > 255)
            {
                sepia_b = 255;
            }
            // Update pixel with sepia values
            image[i][j].rgbtRed = round(sepia_r);
            image[i][j].rgbtGreen = round(sepia_g);
            image[i][j].rgbtBlue = round(sepia_b);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all rows
    for (int i = 0; i < height; i++)
    {
        // Find the middle point of row
        double middle = round(width / 2);

        // Loop over pixels and swap until middle point is reached
        for (int a = 0; a < middle; a++)
        {
            int b = width - a - 1;
            RGBTRIPLE *x = &image[i][a];
            RGBTRIPLE *y = &image[i][b];
            RGBTRIPLE tmp = *x;
            *x = *y;
            *y = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize variables
            int number_of_pixels = 0;
            double total_red = 0.0;
            double total_green = 0.0;
            double total_blue = 0.0;

            // Loop over each neighboring pixel in copy
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int y_index = i + k;
                    int x_index = j + l;
                    // Check indexes are within the bounds of the array
                    if (y_index >= 0 && y_index < height && x_index >= 0 && x_index < width)
                    {
                        number_of_pixels++;
                        total_red += copy[i + k][j + l].rgbtRed;
                        total_green += copy[i + k][j + l].rgbtGreen;
                        total_blue += copy[i + k][j + l].rgbtBlue;
                    }
                }
            }
            // Compute blur values
            double blur_red = round(total_red / (float) number_of_pixels);
            double blur_green = round(total_green / (float) number_of_pixels);
            double blur_blue = round(total_blue / (float) number_of_pixels);

            // Update image's pixel with blur values
            image[i][j].rgbtRed = blur_red;
            image[i][j].rgbtGreen = blur_green;
            image[i][j].rgbtBlue = blur_blue;
        }
    }
    return;
}
