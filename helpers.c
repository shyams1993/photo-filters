#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /* We use a nested loop to compute each pixel's red, green and blue value separately */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;
            /* Once we compute the individual color values, we perform an average of the 3 colors by type casting the variables to a float */
            float avg = ((float)(blue + green + red) / (float)3);
            int result = round(avg);
            /* Upon computing the average, we apply the result to each of the pixel's colors */
            image[i][j].rgbtBlue = result;
            image[i][j].rgbtGreen = result;
            image[i][j].rgbtRed = result;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /* We use a nested loop to calculate each pixel's RGB Value */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;
            /* We use the sepia algorithm to compute sepia red, sepia green and sepia blue values for red, green and blue respectively */
            float sRed = (0.393 * (float)red) + (0.769 * (float)green) + (0.189 * (float)blue);
            float sGreen = (0.349 * (float)red) + (0.686 * (float)green) + (0.168 * (float)blue);
            float sBlue = (0.272 * (float)red) + (0.534 * (float)green) + (0.131 * (float)blue);
            /* We then round off the result for precision */
            int sR = round(sRed);
            int sG = round(sGreen);
            int sB = round(sBlue);
            /* Conditional statements to cap the values at 255 if it exceeds 255 */
            if (sR > 255)
            {
                sR = 255;
            }
            if (sG > 255)
            {
                sG = 255;
            }
            if (sB > 255)
            {
                sB = 255;
            }
            /* Post capping, we apply the sepia values to the individual pixels */
            image[i][j].rgbtBlue = sB;
            image[i][j].rgbtGreen = sG;
            image[i][j].rgbtRed = sR;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /* We use a nested loop to traverse through each pixel and reverse 0 through the width's middle value and swap the first and last pixels */
    /* This results in flip filter */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* First, we make a copy of the original image */
    RGBTRIPLE img[height][width];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            img[x][y] = image[x][y];
        }
    }

    /* then we use a nested loop to traverse through individual pixel */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* We start with checking corner cases */
            if (i == 0)
            {
                /* First corner is the left top corner */
                if (j == 0)
                {
                    /* We find the average of the immediate pixels surrounding the target pixel */

                    float b = ((float)(img[i][j].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j + 1].rgbtBlue) / (float)4);
                    float g = ((float)(img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen) /
                               (float)4);
                    float r = ((float)(img[i][j].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j + 1].rgbtRed) / (float)4);
                    /* Upon finding the average, we round it off and assign it to an int variable */
                    int ib = round(b);
                    int ig = round(g);
                    int ir = round(r);
                    /* Following that, we apply the resultant values to the respective pixel */
                    image[i][j].rgbtBlue = ib;
                    image[i][j].rgbtGreen = ig;
                    image[i][j].rgbtRed = ir;
                }
                else if (j == width - 1) /* Second corner is the top right corner */
                {
                    /* We find the average of the immediate pixels surrounding the target pixel */
                    /* Upon finding the average, we round it off and assign it to an int variable */
                    /* Following that, we apply the resultant values to the respective pixel */
                    float b = ((float)(img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j - 1].rgbtBlue) / (float)4);
                    float g = ((float)(img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen) /
                               (float)4);
                    float r = ((float)(img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j - 1].rgbtRed) / (float)4);
                    int ib = round(b);
                    int ig = round(g);
                    int ir = round(r);
                    image[i][j].rgbtBlue = ib;
                    image[i][j].rgbtGreen = ig;
                    image[i][j].rgbtRed = ir;
                }
                else /* Here else means except top left corner & top right corner; therefore covers top edge */
                {
                    /* We find the average of the immediate pixels surrounding the target pixel */
                    /* Upon finding the average, we round it off and assign it to an int variable */
                    /* Following that, we apply the resultant values to the respective pixel */
                    float b = ((float)(img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j -
                                       1].rgbtBlue + img[i + 1][j + 1].rgbtBlue) / (float)6);
                    float g = ((float)(img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j
                                       - 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen) / (float)6);
                    float r = ((float)(img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j -
                                       1].rgbtRed + img[i + 1][j + 1].rgbtRed) / (float)6);
                    int ib = round(b);
                    int ig = round(g);
                    int ir = round(r);
                    image[i][j].rgbtBlue = ib;
                    image[i][j].rgbtGreen = ig;
                    image[i][j].rgbtRed = ir;
                }
            }
            else if (i == height - 1) /* Bottom row */
            {
                if (j == 0) /* Bottom left corner */
                {
                    /* We find the average of the immediate pixels surrounding the target pixel */
                    /* Upon finding the average, we round it off and assign it to an int variable */
                    /* Following that, we apply the resultant values to the respective pixel */

                    float b = ((float)(img[i][j].rgbtBlue + img[i][j + 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue) / (float)4);
                    float g = ((float)(img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen) /
                               (float)4);
                    float r = ((float)(img[i][j].rgbtRed + img[i][j + 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed) / (float)4);
                    int ib = round(b);
                    int ig = round(g);
                    int ir = round(r);
                    image[i][j].rgbtBlue = ib;
                    image[i][j].rgbtGreen = ig;
                    image[i][j].rgbtRed = ir;
                }
                else if (j == width - 1) /* Bottom right corner */
                {
                    /* We find the average of the immediate pixels surrounding the target pixel */
                    /* Upon finding the average, we round it off and assign it to an int variable */
                    /* Following that, we apply the resultant values to the respective pixel */

                    float b = ((float)(img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j - 1].rgbtBlue) / (float)4);
                    float g = ((float)(img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j - 1].rgbtGreen) /
                               (float)4);
                    float r = ((float)(img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j - 1].rgbtRed) / (float)4);
                    int ib = round(b);
                    int ig = round(g);
                    int ir = round(r);
                    image[i][j].rgbtBlue = ib;
                    image[i][j].rgbtGreen = ig;
                    image[i][j].rgbtRed = ir;
                }
                else /* Bottom edge */
                {
                    /* We find the average of the immediate pixels surrounding the target pixel */
                    /* Upon finding the average, we round it off and assign it to an int variable */
                    /* Following that, we apply the resultant values to the respective pixel */

                    float b = ((float)(img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j + 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j -
                                       1].rgbtBlue + img[i - 1][j + 1].rgbtBlue) / (float)6);
                    float g = ((float)(img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j
                                       - 1].rgbtGreen + img[i - 1][j + 1].rgbtGreen) / (float)6);
                    float r = ((float)(img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i][j + 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j -
                                       1].rgbtRed + img[i - 1][j + 1].rgbtRed) / (float)6);
                    int ib = round(b);
                    int ig = round(g);
                    int ir = round(r);
                    image[i][j].rgbtBlue = ib;
                    image[i][j].rgbtGreen = ig;
                    image[i][j].rgbtRed = ir;
                }
            }
            else if (i != 0 && i != height - 1 && j == 0) /* Left edge */
            {
                /* We find the average of the immediate pixels surrounding the target pixel */
                /* Upon finding the average, we round it off and assign it to an int variable */
                /* Following that, we apply the resultant values to the respective pixel */

                float b = ((float)(img[i][j].rgbtBlue + img[i - 1][j].rgbtBlue + img[i + 1][j].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j +
                                   1].rgbtBlue + img[i - 1][j + 1].rgbtBlue) / (float)6);
                float g = ((float)(img[i][j].rgbtGreen + img[i - 1][j].rgbtGreen + img[i + 1][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j
                                   + 1].rgbtGreen + img[i - 1][j + 1].rgbtGreen) / (float)6);
                float r = ((float)(img[i][j].rgbtRed + img[i - 1][j].rgbtRed + img[i + 1][j].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j +
                                   1].rgbtRed + img[i - 1][j + 1].rgbtRed) / (float)6);
                int ib = round(b);
                int ig = round(g);
                int ir = round(r);
                image[i][j].rgbtBlue = ib;
                image[i][j].rgbtGreen = ig;
                image[i][j].rgbtRed = ir;
            }
            else if (i != 0 && i != height - 1 && j == width - 1) /* Right edge */
            {
                /* We find the average of the immediate pixels surrounding the target pixel */
                /* Upon finding the average, we round it off and assign it to an int variable */
                /* Following that, we apply the resultant values to the respective pixel */

                float b = ((float)(img[i][j].rgbtBlue + img[i - 1][j].rgbtBlue + img[i + 1][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i + 1][j -
                                   1].rgbtBlue + img[i - 1][j - 1].rgbtBlue) / (float)6);
                float g = ((float)(img[i][j].rgbtGreen + img[i - 1][j].rgbtGreen + img[i + 1][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i + 1][j
                                   - 1].rgbtGreen + img[i - 1][j - 1].rgbtGreen) / (float)6);
                float r = ((float)(img[i][j].rgbtRed + img[i - 1][j].rgbtRed + img[i + 1][j].rgbtRed + img[i][j - 1].rgbtRed + img[i + 1][j -
                                   1].rgbtRed + img[i - 1][j - 1].rgbtRed) / (float)6);
                int ib = round(b);
                int ig = round(g);
                int ir = round(r);
                image[i][j].rgbtBlue = ib;
                image[i][j].rgbtGreen = ig;
                image[i][j].rgbtRed = ir;
            }
            else /* All other pixels except edges & corners */
            {
                /* We find the average of the immediate pixels surrounding the target pixel */
                /* Upon finding the average, we round it off and assign it to an int variable */
                /* Following that, we apply the resultant values to the respective pixel */

                float b = ((float)(img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j + 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j -
                                   1].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j - 1].rgbtBlue + img[i + 1][j + 1].rgbtBlue) /
                           (float)9);
                float g = ((float)(img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j
                                   - 1].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i + 1][j +
                                           1].rgbtGreen) / (float)9);
                float r = ((float)(img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i][j + 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j -
                                   1].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j - 1].rgbtRed + img[i + 1][j + 1].rgbtRed) / (float)9);
                int ib = round(b);
                int ig = round(g);
                int ir = round(r);
                image[i][j].rgbtBlue = ib;
                image[i][j].rgbtGreen = ig;
                image[i][j].rgbtRed = ir;
            }
        }
    }

    return;
}
