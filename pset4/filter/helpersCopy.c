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
        float average = round((OrigRed + OrigGreen + OrigBlue)/3);

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
            float sepiaBlue = round (.272 * originalRed + .534 * originalGreen + .131 * originalBlue);


            //set the pixel to that number
            if (sepiaRed > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed= sepiaRed;
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
                image[h][w].rgbtBlue= sepiaBlue;
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
    for (int h = 0; h < (height); h++)
    {
        for (int w = 0; w < (width); w++)
        {
        int corner=0;
        int edge= 0;
           //if it is top left corner


           if ( (w == 0) && (h == 0) )
           { corner = 1;
               int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w + 1].rgbtRed +
                image[h + 1][w].rgbtRed +
                image[h + 1][w + 1].rgbtRed ) / 4
                );

                int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w + 1].rgbtGreen +
                image[h + 1][w].rgbtGreen +
                image[h + 1][w + 1].rgbtGreen ) / 4
                );

                int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w + 1].rgbtBlue +
                image[h + 1][w].rgbtBlue +
                image[h + 1][w + 1].rgbtBlue ) / 4
                );

                //set the pixel to that number on copy image
                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;
           }

           //if it is bottom left corner

          else if ( (w == 0) && (h = (height-1) ) )
           {
               corner = 1;
               int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w + 1].rgbtRed +
                image[h + 1][w + 1].rgbtRed +
                image[h + 1][w].rgbtRed ) / 4
                );

                int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w + 1].rgbtGreen +
                image[h + 1][w + 1].rgbtGreen +
                image[h + 1][w].rgbtGreen ) / 4
                );

                int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w + 1].rgbtBlue +
                image[h + 1][w + 1].rgbtBlue +
                image[h + 1][w].rgbtBlue ) / 4
                );
                //set the pixel to that number on copy image

                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;
           }

           //if it is top right corner
          else if ( (w == (width -1)) && (h == 0) )
           {
               corner = 1;
               int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w - 1].rgbtRed +
                image[h - 1][w - 1].rgbtRed +
                image[h - 1][w].rgbtRed )/4
                );

                int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w - 1].rgbtGreen +
                image[h - 1][w - 1].rgbtGreen +
                image[h - 1][w].rgbtGreen )/4
                );

                int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w - 1].rgbtBlue +
                image[h - 1][w - 1].rgbtBlue +
                image[h - 1][w].rgbtBlue )/4
                );
                //set the pixel to that number on copy image

                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;
           }
           //if it is bottom right corner
          else if ( w == (width -1) && (h == (height-1 ) ))
           {
               corner = 1;
               int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w - 1].rgbtRed +
                image[h - 1][w - 1].rgbtRed +
                image[h - 1][w].rgbtRed)/4
                );

                  int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w - 1].rgbtGreen +
                image[h - 1][w - 1].rgbtGreen +
                image[h - 1][w].rgbtGreen)/4
                );

                  int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w - 1].rgbtBlue +
                image[h - 1][w - 1].rgbtBlue +
                image[h - 1][w].rgbtBlue)/4
                );
                //set the pixel to that number on copy image

                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;
           }


           //if it is top edge
          else if (h == 0)
           {
               edge=1;
               int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w + 1].rgbtRed +
                image[h][w - 1].rgbtRed +
                image[h + 1][w - 1].rgbtRed +
                image[h + 1][w].rgbtRed +
                image[h + 1][w + 1].rgbtRed )/6
                );

                 int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w + 1].rgbtGreen +
                image[h][w - 1].rgbtGreen +
                image[h + 1][w - 1].rgbtGreen +
                image[h + 1][w].rgbtGreen +
                image[h + 1][w + 1].rgbtGreen )/6
                );

                 int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w + 1].rgbtBlue +
                image[h][w - 1].rgbtBlue +
                image[h + 1][w - 1].rgbtBlue +
                image[h + 1][w].rgbtBlue +
                image[h + 1][w + 1].rgbtBlue )/6
                );
                //set the pixel to that number on copy image

                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;
           }

           //if it is bottom edge
          else if (h == (height-1) )
           {edge=1;
               int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w + 1].rgbtRed +
                image[h][w - 1].rgbtRed +
                image[h - 1][w - 1].rgbtRed +
                image[h - 1][w].rgbtRed +
                image[h - 1][w + 1].rgbtRed )/6
                );

                int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w + 1].rgbtGreen +
                image[h][w - 1].rgbtGreen +
                image[h - 1][w - 1].rgbtGreen +
                image[h - 1][w].rgbtGreen +
                image[h - 1][w + 1].rgbtGreen )/6
                );

                int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w + 1].rgbtBlue +
                image[h][w - 1].rgbtBlue +
                image[h - 1][w - 1].rgbtBlue +
                image[h - 1][w].rgbtBlue +
                image[h - 1][w + 1].rgbtBlue )/6
                );
                //set the pixel to that number on copy image

                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;
           }

           //if it is left edge
          else if (w == 0)
           {edge=1;
               int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w + 1].rgbtRed +
                image[h - 1][w].rgbtRed +
                image[h - 1][w + 1].rgbtRed +
                image[h + 1][w].rgbtRed +
                image[h + 1][w + 1].rgbtRed )/6
                );

                int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w + 1].rgbtGreen +
                image[h - 1][w].rgbtGreen +
                image[h - 1][w + 1].rgbtGreen +
                image[h + 1][w].rgbtGreen +
                image[h + 1][w + 1].rgbtGreen )/6
                );

                int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w + 1].rgbtBlue +
                image[h - 1][w].rgbtBlue +
                image[h - 1][w + 1].rgbtBlue +
                image[h + 1][w].rgbtBlue +
                image[h + 1][w + 1].rgbtBlue )/6
                );
                //set the pixel to that number on copy image

                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;
           }

           //if it is right edge
          else if (w == (width-1))
           {edge=1;
               int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w - 1].rgbtRed +
                image[h - 1][w - 1].rgbtRed +
                image[h - 1][w].rgbtRed +
                image[h + 1][w - 1].rgbtRed +
                image[h + 1][w].rgbtRed)
               /6
                );

                int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w - 1].rgbtGreen +
                image[h - 1][w - 1].rgbtGreen +
                image[h - 1][w].rgbtGreen +
                image[h + 1][w - 1].rgbtGreen +
                image[h + 1][w].rgbtGreen)
               /6
                );

                int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w - 1].rgbtBlue +
                image[h - 1][w - 1].rgbtBlue +
                image[h - 1][w].rgbtBlue +
                image[h + 1][w - 1].rgbtBlue +
                image[h + 1][w].rgbtBlue)
               /6
                );
                //set the pixel to that number on copy image

                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;
           }

            else if (!edge && !corner)
            {
                int blurRed = round(
                (image[h][w].rgbtRed +
                image[h][w + 1].rgbtRed +
                image[h][w - 1].rgbtRed +
                image[h - 1][w - 1].rgbtRed +
                image[h - 1][w].rgbtRed +
                image[h - 1][w + 1].rgbtRed +
                image[h + 1][w - 1].rgbtRed +
                image[h + 1][w].rgbtRed +
                image[h + 1][w + 1].rgbtRed )/9
                );

                int blurBlue = round(
                (image[h][w].rgbtBlue +
                image[h][w + 1].rgbtBlue +
                image[h][w - 1].rgbtBlue +
                image[h - 1][w - 1].rgbtBlue +
                image[h - 1][w].rgbtBlue +
                image[h - 1][w + 1].rgbtBlue +
                image[h + 1][w - 1].rgbtBlue +
                image[h + 1][w].rgbtBlue +
                image[h + 1][w + 1].rgbtBlue )/9
                );

                int blurGreen = round(
                (image[h][w].rgbtGreen +
                image[h][w + 1].rgbtGreen +
                image[h][w - 1].rgbtGreen +
                image[h - 1][w - 1].rgbtGreen +
                image[h - 1][w].rgbtGreen +
                image[h - 1][w + 1].rgbtGreen +
                image[h + 1][w - 1].rgbtGreen +
                image[h + 1][w].rgbtGreen +
                image[h + 1][w + 1].rgbtGreen )/9
                );
                //set the pixel to that number on copy image
                imageCopy[h][w].rgbtRed = blurRed;
                imageCopy[h][w].rgbtGreen = blurGreen;
                imageCopy[h][w].rgbtBlue = blurBlue;

            }

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
