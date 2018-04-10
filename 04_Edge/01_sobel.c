/*
compile: gcc 01_sobel.c -lm -o sobel
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAX_LINE 10
#define WIDTH 640
#define HEIGHT 480

int main(int argc, char const *argv[])
{

    FILE *fp;
    int temp;
    char buf[MAX_LINE];
    int len;
    int count=0;
    int i, j;

    unsigned char pixel[WIDTH*HEIGHT];
    char Gx[WIDTH*HEIGHT];
    char Gy[WIDTH*HEIGHT];
    unsigned char G[WIDTH*HEIGHT];
    float theta[WIDTH*HEIGHT];

    if(argc != 2)
    {
        printf("Usage: %s filename\n",argv[0]);
        exit(0);
    }

    fp = fopen(argv[1], "r");
    while(fgets(buf,MAX_LINE,fp)!=NULL)
    {   
        len=strlen(buf);
        buf[len-1]='\0';
        temp=atoi(buf);

        // Change char to unsigneed char 
        if (temp < 0)
        {
            temp = 256 + temp;
        }

        pixel[i + j*WIDTH]=temp;
        i++;
        if(i==WIDTH)
        {
            i=0;
            j++;
            if(j==HEIGHT)
            {
                printf("Assignment compleated.\n");
            }
        }
        count ++;
    }
    fclose(fp);

    // Save the image.
    stbi_write_png("Original_Image.png", WIDTH, HEIGHT, 1, pixel, 0);

    for(j = 0; j < HEIGHT; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            if( i == 0 || j == 0 || i == WIDTH - 1 || j == HEIGHT - 1)
            {
                Gx[i + j*WIDTH] = 0;
                Gy[i + j*WIDTH] = 0;
                G[i + j*WIDTH] = 0;
            }else
            {
                Gx[i + j*WIDTH] = 
                (-1)*pixel[i-1 + (j-1)*WIDTH]  + pixel[i+1+(j-1)*WIDTH] + (-2)*pixel[i-1+j*WIDTH] + 
                   2*pixel[i+1+j*WIDTH]   + (-1)*pixel[i-1+(j+1)*WIDTH] + pixel[i+1+(j+1)*WIDTH];

                Gy[i + j*WIDTH] = 
                pixel[i-1+(j-1)*WIDTH] + 2*pixel[i+(j-1)*WIDTH] + pixel[i+ 1 + (j-1)*WIDTH] + 
           (-1)*pixel[i-1+(j+1)*WIDTH] + (-2)*pixel[i+(j+1)*WIDTH] + (-1)*pixel[i+1+(j+1)*WIDTH];

                G[i+j*WIDTH] = sqrt((Gx[i+j*WIDTH])*(Gx[i+j*WIDTH]) + (Gy[i+j*WIDTH])*(Gy[i+j*WIDTH]));
            }
        }
    }

    // Save Gx
    stbi_write_png("Gx.png", WIDTH, HEIGHT, 1, Gx, 0);
    stbi_write_png("Gy.png", WIDTH, HEIGHT, 1, Gy, 0);
    stbi_write_png("G.png",  WIDTH, HEIGHT, 1, G,  0);
    return 0;
}