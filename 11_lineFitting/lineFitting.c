// compile: gcc lineFitting.c -lm -o lineFitting
// run: ./lineFitting

#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct pointT
{
	int x;
	int y;
};


struct lineT
{
	// line: ax + by +c = 0;
	float a;
	float b;
	float c;
};



void draw_line(int x0, int y0, int x1, int y1, unsigned char *image, int width, int height);
void draw_rectangle(int startX, int startY, unsigned int retWidth, unsigned int retHeight, 
					unsigned char *image, int width, int height);

void fill_rectangle(int startX, int startY, unsigned int retWidth, unsigned int retHeight, 
					unsigned char *image, int width, int height, unsigned char color);

int lineFit( struct pointT *points, unsigned int numPoints, struct lineT *line);

int getEndPoints(struct lineT line, unsigned char *image, int width, int height, struct pointT *ends);
void showLine(struct lineT line, unsigned char	*image, int width, int height);


int main(int argc, char const *argv[])
{
	int width = 500;
	int height = 500;
	unsigned char image[width*height];
	// clear the the memory
	memset(image, 0, sizeof(image));


	struct pointT somePoints[]={{39,40},{63,80},{78,117},(93,140)};
	fill_rectangle(39, 40, 5, 5, image, width, height,205);
	fill_rectangle(63, 80, 5, 5, image, width, height,205);
	fill_rectangle(78, 117, 5, 5, image, width, height,205);
	fill_rectangle(93, 140, 5, 5, image, width, height,205);
	stbi_write_png("points.png", width, height, 1, image, 0);


	struct lineT line;
	lineFit( somePoints, 4, &line);
	printf("line:(%f,%f,%f)\n", line.a,line.b,line.c);
	showLine(line, image, width, height);
	stbi_write_png("fitting_line.png", width, height, 1, image, 0);
	
	return 0;
}



void showLine(struct lineT line, unsigned char	*image, int width, int height)
{
	int x=0,y=0;
	for(x=0; x < width; x++)
	{
		y = (int)(-(line.a*x + line.c)/line.b);
		if(y >= 0 && y <= height-1)
		{
			*(image + x*height + y) = 255;
		}
	}
}

int lineFit( struct pointT *points, unsigned int numPoints, struct lineT *line)
{
	int i;

	if(numPoints < 2)
	{
		line->a = 0;
		line->b = 0;
		line->c = 0;
		return -1;
	}

	float x_mean = 0;
	float y_mean = 0;
	
	for(i =0; i < numPoints; i++)
	{
		x_mean += points[i].x;
		y_mean += points[i].y;
	}

	float Dxx = 0, Dxy = 0, Dyy = 0;
	for(i = 0; i < numPoints; i++)
	{
		Dxx += (points[i].x - x_mean) * (points[i].x - x_mean);
		Dxy += (points[i].x - x_mean) * (points[i].y - y_mean);
		Dyy += (points[i].y - y_mean) * (points[i].y - y_mean);
	}
    float lambda = ((Dxx + Dyy) - sqrt((Dxx - Dyy) * (Dxx - Dyy) + 4 * Dxy * Dxy))/2.0;
    float den = sqrt(Dxy * Dxy + (lambda - Dxx) * (lambda - Dxx));
    line->a = Dxy / den;
    line->b = (lambda - Dxx) / den;
    line->c = -(line->a) * x_mean - line->b* y_mean;
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


void fill_rectangle(int startX, int startY, unsigned int retWidth, unsigned int retHeight, 
					unsigned char *image, int width, int height, unsigned char color)
{	

	int DRx = startX + retWidth;
	int DRy = startY + retHeight;
	int i,j;
	for(j = startY; j < DRy; j++)
	{
		for(i = startX; i < DRx; i++)
		{
			*(image + width*j + i) = color;
		}
	}
}

