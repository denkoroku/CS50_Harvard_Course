#include "helpers.h"
#include "stdio.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //get each pixel
    for (int h = 0; h < (height); h++)
    {
        for (int w = 0; w < (width); w++)
        {
            float OrigRed = image[h][w].rgbtRed;
            float OrigGreen = image [h][w].rgbtGreen;
            float OrigBlue = image [h][w].rgbtBlue;

            //calculate the average colour number
            float average = round((OrigRed + OrigGreen + OrigBlue) / 3);

            //set the pixel to that number
            image[h][w].rgbtRed = average;
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
        }
    }


    return;


}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //get each pixel
    for (int h = 0; h < (height); h++)
    {
        for (int w = 0; w < (width); w++)
        {
            float originalRed = image[h][w].rgbtRed;
            float originalGreen = image [h][w].rgbtGreen;
            float originalBlue = image [h][w].rgbtBlue;

            //calculate the new colour number
            float sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            float sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            float sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);


            //set the pixel to that number
            if (sepiaRed > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[h][w].rgbtGreen = 255;
            }

            else
            {
                image[h][w].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[h][w].rgbtBlue = 255;
            }

            else
            {
                image[h][w].rgbtBlue = sepiaBlue;
            }

        }
    }



    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE imageCopy[height][width];

    for (int h = 0; h < (height); h++)
    {
        for (int w = 0; w < (width); w++)
        {
            int dist = width - w - 1;

            //move pixels
            {
                imageCopy[h][dist] = image[h][w];
            }
        }
    }
    //copy the temp image to make it the image
    for (int h = 0; h < (height); h++)
    {
        for (int w = 0; w < (width); w++)
        {
            image[h][w] = imageCopy[h][w];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];

    //get each pixel of the original

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;

            double noPixels = 0;

            //loop through pixels around the center pixel
            for (int r = h - 1; r <= h + 1; r++)
            {
                for (int c = w - 1; c <= w + 1; c++)
                {
                    //does pixel exist?
                    if (!(c < 0) && !(c > width - 1) && !(r < 0) && !(r > height - 1))
                    {
                        //add up totals
                        red += image[r][c].rgbtRed;
                        blue += image[r][c].rgbtBlue;
                        green += image[r][c].rgbtGreen;

                        //increase counter
                        noPixels++;
                    }
                }
            }
            //make the copy image
            imageCopy[h][w].rgbtRed = round(red / noPixels);
            imageCopy[h][w].rgbtBlue = round(blue / noPixels);
            imageCopy[h][w].rgbtGreen = round(green / noPixels);
        }
    }


//replace image with temp image
    for (int k = 0; k < (height); k++)
    {
        for (int l = 0; l < (width); l++)
        {
            image[k][l] = imageCopy[k][l];
        }
    }
    return;
}
