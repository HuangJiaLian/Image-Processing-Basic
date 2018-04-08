/*
compile: gcc 01_read_from_data.c -lm -o read_from_data
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
    stbi_write_png("read_from_data.png", WIDTH, HEIGHT, 1, pixel, 0);
    return 0;
}