#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: whodunit infile outfile\n");
		return 1;
	}
	
	// strings to represent the file names specified in command line arguments
	char *infile = argv[1];
	char *outfile = argv[2];
	
	// attempts to open file of name specified in command line arguments
	FILE *inf = fopen(infile, "r");
	if(inf == NULL)
	{
		printf("Could not open file %s\n", infile);
		return 2;
	}
	
	// attempts to create a new file of name specified in command line arguments
	FILE *outf = fopen(outfile, "w");
	if(outf == NULL)
	{
		fclose(inf);
		printf("Could not create file %s\n", outfile);
		return 3;
	}
	
	// gets bitmapfileheader from inf
	BITMAPFILEHEADER bf;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inf);
	
	// gets bitmapinfoheader from inf
	BITMAPINFOHEADER bi;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inf);
	
    // ensure inf is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outf);
        fclose(inf);
        printf("Unsupported file format.\n");
        return 4;
    }
	
	// writes bitmapfileheader to outf
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outf);
	
	// writes bitmapinfoheader to outf
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outf);
	
	// calculates the padding for 24-bit uncompressed BMP 4.0
	int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE) % 4)) % 4;
	
	// copies the pixels in BGR from inf to outf, taking out red
	for(int i = 0; i < abs(bi.biHeight); i++)
	{
		for(int j = 0; j < bi.biWidth; j++)
		{
			RGBTRIPLE triple;
			fread(&triple, sizeof(RGBTRIPLE), 1, inf);
			triple.rgbtGreen -= 255;
			triple.rgbtBlue -= 255;
			triple.rgbtRed -= 255;
			fwrite(&triple, sizeof(RGBTRIPLE), 1, outf);
		}
		
		// skips over padding in original inf file
		fseek(inf, padding, SEEK_CUR);
		
		for(int i = 0; i < padding; i++)
		{
			fputs(0x00, outf);
		}
	}
	fclose(inf);
	fclose(outf);
}