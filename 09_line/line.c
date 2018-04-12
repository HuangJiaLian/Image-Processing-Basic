// compile: gcc line.c -lm -o lines
// run: ./lines

#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void draw_line(int x0, int y0, int x1, int y1, unsigned char *image, int width, int height);


int main(int argc, char const *argv[])
{
	int width = 500;
	int height = 500;
	unsigned char image[width*height];
	// clear the the memory
	memset(image, 0, sizeof(image));

	unsigned int x0 = 250;
	unsigned int y0 = 150;

	unsigned int x1 = 200;
	unsigned int y1 = 300;

	unsigned int x2 = 300;
	unsigned int y2 = 300;


	draw_line(x0, y0, x1, y1, image,  width, height);
	draw_line(x1, y1, x2, y2, image,  width, height);
	draw_line(x2, y2, x0, y0, image,  width, height);
	stbi_write_png("lines.png", width, height, 1, image, 0);
	
	return 0;
}



void draw_line(int x0, int y0, int x1, int y1, unsigned char *image, int width, int height)
{
    int dx, dy, dx2, dy2, x_inc, y_inc, error, index;
    int offset_x=0;
    int offset_y=0;

    dx = x1 - x0;
    dy = y1 - y0;

    if(dx >= 0)
    {
        x_inc = 1;
    }else
    {
        x_inc = -1;
        dx = -dx; // need absolute value
    }

    if(dy >= 0)
    {
        y_inc = 1;
    }else
    {
        y_inc = -1;
        dy = -dy;
    }

    // compute(dx,dy)*2
    dx2 = dx * 2;
    dy2 = dy * 2;

    if(dx > dy)
    {
        // initialize error term
        error = dy2 - dx;
        for(index = 0; index <= dx; index++)
        {
        	// *(image + height*(x0+offset_x) + y0+offset_y) = 100;
        	*(image + (x0+offset_x) + (y0+offset_y)*width) = 200;
            if(error >= 0)
            {
                error -= dx2;
                // move to next line
                offset_y += y_inc;
            }

            // adjust the error term 
            error += dy2;

            // move to next pixel
            offset_x += x_inc;
        }
    }else
    {
        error = dx2 - dy;
        for(index = 0; index <= dy; index++)
        {

            // *(image + height*(x0+offset_x) + y0+offset_y) = 100;
            *(image + (x0+offset_x) + (y0+offset_y)*width) = 200;
            if(error >= 0)
            {
                error -= dy2;
                offset_x += x_inc;
            }

            error += dx2;
            offset_y += y_inc;
        }
    }
}
