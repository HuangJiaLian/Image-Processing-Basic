/*
	Prepare: make sure stb_image.h in the same directory 
	Compile: gcc 02_read_from_pic.c -lm -o read_from_pic 
*/ 

#include <stdio.h>
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
	return 0;
}