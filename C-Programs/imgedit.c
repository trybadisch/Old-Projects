// Converts to grayscale, sepia, reflects, or blurs an image

#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray_average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = gray_average;
            image[i][j].rgbtGreen = gray_average;
            image[i][j].rgbtBlue = gray_average;
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
            int new_red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int new_green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int new_blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (new_red > 255)
                image[i][j].rgbtRed = 255;
            else image[i][j].rgbtRed = new_red;
            if (new_green > 255)
                image[i][j].rgbtGreen = 255;
            else image[i][j].rgbtGreen = new_green;
            if (new_blue > 255)
                image[i][j].rgbtBlue = 255;
            else image[i][j].rgbtBlue = new_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width-1; j <= k; j++, k--)
        {
            int aux_red = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][k].rgbtRed = aux_red;

            int aux_green = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][k].rgbtGreen = aux_green;

            int aux_blue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][k].rgbtBlue = aux_blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create new struct to temporally store blurred pixels
    RGBTRIPLE blur_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0){
                blur_image[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 4.0);
                blur_image[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 4.0);
                blur_image[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 4.0);
            }
            else if (i == 0 && j == width-1){
                blur_image[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed) / 4.0);
                blur_image[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen) / 4.0);
                blur_image[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue) / 4.0);
            }
            else if (i == height-1 && j == 0){
                blur_image[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed) / 4.0);
                blur_image[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen) / 4.0);
                blur_image[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue) / 4.0);
            }
            else if (i == height-1 && j == width-1){
                blur_image[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed) / 4.0);
                blur_image[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen) / 4.0);
                blur_image[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue) / 4.0);
            }
            else if ( (i == 0 && j != 0) || (i == 0 && j != width-1) ){
                blur_image[i][j].rgbtRed = round((image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                                  image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0);
                blur_image[i][j].rgbtGreen = round((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                                  image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0);
                blur_image[i][j].rgbtBlue = round((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                                  image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0);
            }
            else if ( (i == height-1 && j != 0) || (i == height-1 && j != width-1) ){
                blur_image[i][j].rgbtRed = round((image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                                  image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed) / 6.0);
                blur_image[i][j].rgbtGreen = round((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                                  image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen) / 6.0);
                blur_image[i][j].rgbtBlue = round((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                                  image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue) / 6.0);
            }
            else if ( (j == 0 && i != 0) || (j == 0 && i != height-1) ){
                blur_image[i][j].rgbtRed = round((image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                                                  image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                                  image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0);
                blur_image[i][j].rgbtGreen = round((image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                                                  image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                                  image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0);
                blur_image[i][j].rgbtBlue = round((image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                                                  image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                                  image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0);
            }
            else if ( (j == width-1 && i != 0) || (j == width-1 && i != height-1) ){
                blur_image[i][j].rgbtRed = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed +
                                                  image[i][j-1].rgbtRed + image[i][j].rgbtRed +
                                                  image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed) / 6.0);
                blur_image[i][j].rgbtGreen = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen +
                                                  image[i][j-1].rgbtGreen + image[i][j].rgbtGreen +
                                                  image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen) / 6.0);
                blur_image[i][j].rgbtBlue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue +
                                                  image[i][j-1].rgbtBlue + image[i][j].rgbtBlue +
                                                  image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue) / 6.0);
            }
            else {
                blur_image[i][j].rgbtRed = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                                                 image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                                  image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 9.0);

                blur_image[i][j].rgbtGreen = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                                                  image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                                  image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 9.0);

                blur_image[i][j].rgbtBlue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                                                  image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                                  image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 9.0);
            }
        }
    }
    // Replace original struct with blurred one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blur_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = blur_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blur_image[i][j].rgbtBlue;
        }
    }
    return;
}
