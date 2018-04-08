/*
	Prepare: make sure stb_image.h and stb_image_write.h 
	in the same directory 
	Compile: gcc 01_write.c -lm -o 01_write 
*/ 

#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char const *argv[])
{

	if(argc != 2)
	{
        printf("Usage: %s filename\n",argv[0]);
        exit(0);
	}
	
	/* load single channel image data */
	const char *inputFile = argv[1];
	int width = 0, height = 0, n = 0;
	void *raw = NULL;
	raw = stbi_load(inputFile, &width, &height, &n, 0);
	printf("Channel numbers: %d\n", n);
	stbi_write_png("write_test.png", width, height, n, raw, 0);
	stbi_write_jpg("write_test.jpg", width, height, n, raw, 99);
	stbi_write_bmp("write_test.bmp", width, height, n, raw);
	stbi_image_free(raw);
	
	return 0;

}