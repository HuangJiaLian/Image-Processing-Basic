// compile: gcc getIntersection.c -lm -o getIntersection
// run: ./getIntersection

#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void draw_line(int x0, int y0, int x1, int y1, unsigned char *image, int width, int height);
void draw_rectangle(int startX, int startY, unsigned int retWidth, unsigned int retHeight, 
					unsigned char *image, int width, int height);
int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
    float p2_x, float p2_y, float p3_x, float p3_y, int *i_x, int *i_y);

int main(int argc, char const *argv[])
{
	int width = 500;
	int height = 500;
	unsigned char image[width*height];
	// clear the the memory
	memset(image, 0, sizeof(image));
	int line00x = 0;
	int line00y = 0;
	int line01x = 400;
	int line01y = 400;

	int line10x = 0;
	int line10y = 400;
	int line11x = 400;
	int line11y = 0;

	draw_line(line00x, line00y, line01x, line01y, image,  width,  height);
	draw_line(line10x, line10y, line11x, line11y, image,  width,  height);
	stbi_write_png("twoLines.png", width, height, 1, image, 0);

	int intersectionX, intersectionY;
	get_line_intersection((float)line00x, (float)line00y, (float)line01x, (float)line01y,
    (float)line10x, (float)line10y, (float)line11x, (float)line11y, &intersectionX, &intersectionY);

	draw_rectangle(intersectionX - 2, intersectionY - 2, 5, 5, image, width, height);
	stbi_write_png("intersection.png", width, height, 1, image, 0);
	return 0;
}


/**
 * brief: get intersection of two lines 
 * param: 
    float p0_x, float p0_y, float p1_x, float p1_y: the endpoints of the 1st line
    float p2_x, float p2_y, float p3_x, float p3_y: the endpoints of the 2nd line
    float *i_x, float *i_y: the intersection of the two lines 
 * return:
    1: intersection found
    0: no intersection found
 */
int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
    float p2_x, float p2_y, float p3_x, float p3_y, int *i_x, int *i_y)
{
    float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
    s10_x = p1_x - p0_x;
    s10_y = p1_y - p0_y;
    s32_x = p3_x - p2_x;
    s32_y = p3_y - p2_y;

    denom = s10_x * s32_y - s32_x * s10_y;
    if (denom == 0)
        return 0; // Collinear
    int denomPositive = denom > 0;

    s02_x = p0_x - p2_x;
    s02_y = p0_y - p2_y;
    s_numer = s10_x * s02_y - s10_y * s02_x;
    if ((s_numer < 0) == denomPositive)
        return 0; // No collision

    t_numer = s32_x * s02_y - s32_y * s02_x;
    if ((t_numer < 0) == denomPositive)
        return 0; // No collision

    if (((s_numer > denom) == denomPositive) || 
        ((t_numer > denom) == denomPositive))
        return 0; // No collision
    // Collision detected
    t = t_numer / denom;
    if (i_x != 0)
        *i_x = p0_x + (t * s10_x);
    if (i_y != 0)
        *i_y = p0_y + (t * s10_y);

    return 1;
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



void draw_rectangle(int startX, int startY, unsigned int retWidth, unsigned int retHeight, 
					unsigned char *image, int width, int height)
{
	int URx = startX + retWidth;
	int URy = startY;
	
	int DLx = startX;
	int DLy = startY + retHeight;

	int DRx = startX + retWidth;
	int DRy = startY + retHeight;

	draw_line(startX, startY, URx, URy, image, width, height);
	draw_line(startX, startY, DLx, DLy, image, width, height);
	draw_line(DLx, DLy, DRx, DRy, image, width, height);
	draw_line(DRx, DRy, URx, URy, image, width, height);
}

