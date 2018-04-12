/*
compile: gcc 01_otsuThreshold.c -lm -o 01_otsuThreshold
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#define WIDTH 640
#define HEIGHT 480


void read_data(const char * filename, unsigned char *image, int w, int h);
int otsuThreshold(unsigned char * image, int width, int height);
// Binarization
void binarize(unsigned char * image, unsigned char * bImage, 
              int width, int height, unsigned char threshold);


int main(int argc, char const *argv[])
{
    
    if(argc != 2)
    {
        printf("Usage: %s filename\n",argv[0]);
        exit(0);
    }

    unsigned char img[WIDTH*HEIGHT];
    unsigned char bimg[WIDTH*HEIGHT];

    // Load data from text file
    read_data(argv[1], img, WIDTH, HEIGHT);

    // Get the global threshold value
    unsigned char threshold = otsuThreshold( img, WIDTH, HEIGHT);
    printf("threshold = %d\n", threshold);

    // Binarization
    unsigned char bImage[WIDTH*HEIGHT];
    binarize(img, bImage, WIDTH, HEIGHT, threshold);
    
    // Save the image.
    stbi_write_png("binarized_pic.png", WIDTH, HEIGHT, 1, bImage, 0);

    return 0;
}




void read_data(const char * filename, unsigned char *image, int w, int h)
{
    FILE *fp;
    int temp;
    char buf[10];
    int len;
    int count=0;
    int i, j;

    fp = fopen(filename, "r");
    while(fgets(buf,10,fp)!=NULL)
    {   
        len=strlen(buf);
        buf[len-1]='\0';
        temp=atoi(buf);

        // Change char to unsigneed char 
        if (temp < 0)
        {
            temp = 256 + temp;
        }

        image[i + j*w]=temp;
        i++;
        if(i==w)
        {
            i=0;
            j++;
            if(j==h)
            {
                printf("Assignment compleated.\n");
            }
        }
        count ++;
    }
    fclose(fp);
}


/*********************/
/**otsu Threshold  ***/
/*********************/
// Get the threshold for binarization
int otsuThreshold(unsigned char * image, int width, int height)
{
    int pixelCount[255];
    float pixelPro[255];
    int i,j,pixelSum = width*height, threshold = 0;

    for(i = 0; i < 255; i++)  
    {  
        pixelCount[i] = 0;  
        pixelPro[i] = 0;  
    }
    // Count the number of specific pixel value  
    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {
            pixelCount[*(image + height*i + j)]++;
        }
    }      

    // Get the probability of every pixel value
    for(i = 0; i < 255; i++)  
    {  
        pixelPro[i] = (float)pixelCount[i] / pixelSum;  
    }      

    // loop for 0 to 255
    float w0, w1, u0tmp, u1tmp, u0, u1, u,   
            deltaTmp, deltaMax = 0;  
    for(i = 0; i < 255; i++)  
    {  
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;  
        for(j = 0; j < 255; j++)  
        {  
            if(j <= i)   // background 
            {  
                w0 += pixelPro[j];  
                u0tmp += j * pixelPro[j];  
            }  
            else   // foreground  
            {  
                w1 += pixelPro[j];  
                u1tmp += j * pixelPro[j];  
            }  
        }  
        u0 = u0tmp / w0;  
        u1 = u1tmp / w1;  
        u = u0tmp + u1tmp;  
        deltaTmp =   
            w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);  
        if(deltaTmp > deltaMax)  
        {  
            deltaMax = deltaTmp;  
            threshold = i;  
        }  
    }  
    return threshold;  
}


// Binarization
void binarize(unsigned char * image, unsigned char * bImage, 
    int width, int height, unsigned char threshold)
{
    int i,j;
    for(j = 0; j < height; j++)
    {
        for(i = 0; i < width; i++)
        {
            if(*(image + height*i + j) < threshold)
            {
                *(bImage + height*i + j) = 0;
            }else
            {
                *(bImage + height*i + j) = 255;
            }
        }
    }
}

