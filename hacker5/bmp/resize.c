#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Usage: resize f infile outfile\n");
		return 1;
	}
	
	// floating point value (0.0, 100.0] to represent the ratio of the resize
	float f = atof(argv[1]);
	if(f <= 0.0 || f > 100.0)
	{
		printf("f must be a value greater than 0.0 and less than or equal to 100.0\n");
		return 2;
	}
	
	// strings to represent the file names specified in command line arguments
	char *infile = argv[2];
	char *outfile = argv[3];
	
	// attempts to open file of name specified in command line arguments
	FILE *inf = fopen(infile, "r");
	if(inf == NULL)
	{
		printf("Could not open file %s\n", infile);
		return 3;
	}
	
	// attempts to create a new file of name specified in command line arguments
	FILE *outf = fopen(outfile, "w");
	if(outf == NULL)
	{
		fclose(inf);
		printf("Could not create file %s\n", outfile);
		return 4;
	}
	
	// gets bitmapfileheader from inf
	BITMAPFILEHEADER bf;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inf);
	
	// gets bitmapinfoheader from inf
	BITMAPINFOHEADER bi;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inf);
	
    // ensure inf is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
		bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outf);
        fclose(inf);
        printf("Unsupported file format.\n");
        return 5;
    }
	
	int paddingin = (4 - bi.biWidth * sizeof(RGBTRIPLE) % 4) % 4;
	int oldwidth = bi.biWidth;
	int oldheight = bi.biHeight;
	int width = rint(f * (float)bi.biWidth);
	int height = rint(f * (float)bi.biHeight);
	
	printf("Old size: %i, Old width: %i, Old height: %i\n", bf.bfSize,
		bi.biWidth, bi.biHeight);
	
	printf("Paddingin: %i\n", paddingin);
	
	bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) 
		+ abs((width * sizeof(RGBTRIPLE) + paddingin) * height);
	bi.biWidth = width;
	bi.biHeight = height;
	
	printf("New size: %i, New width: %i, New height: %i\n", bf.bfSize,
		bi.biWidth, bi.biHeight);
		
	RGBTRIPLE image[abs(bi.biHeight)][bi.biWidth];
	
	if(f < 1.0)
	{
		printf("%i\n", ftell(inf) - 54);
		int y = 0;
		int a = 0;
		for(float i = (float)oldheight / (float)bi.biHeight; i <= abs(oldheight); i += (float)oldheight / (float)bi.biHeight)
		{
			int x = 0;
			int b = 0;
			for(float j = (float)oldwidth / (float)bi.biWidth; j <= oldwidth; j += (float)oldwidth / (float)bi.biWidth)
			{
				printf("| %f , %f ; index [%i][%i] |\n", i, j, a, b);
				int sumyr = 0; int sumyg = 0; int sumyb = 0;
				for(int k = y; k < i; k++)
				{
					int sumxr = 0; int sumxg = 0; int sumxb = 0;
					for(int l = x; l < j; l++)
					{
						printf("%i, %i\n", k, l);
						int red;
						int green;
						int blue;
						fread(&blue, 1, 1, inf);
						fread(&green, 1, 1, inf);
						fread(&red, 1, 1, inf);
						printf("%i, r%x, g%x, b%x\n", ftell(inf) - 54, red, green, blue);
						sumxr += red;
						sumxg += green;
						sumxb += blue;
					}
					fseek(inf, paddingin + (oldwidth * sizeof(RGBTRIPLE)) - ((j - x) * sizeof(RGBTRIPLE)), SEEK_CUR);
					//printf("%i\n", ftell(inf) - 54);
					sumyr += sumxr / (j - x);
					sumyg += sumxg / (j - x);
					sumyb += sumxb / (j - x);
				}
				fseek(inf, -1 * ((i - y) * (paddingin + oldwidth * sizeof(RGBTRIPLE))) + (j - x) * sizeof(RGBTRIPLE), SEEK_CUR);
				image[a][b].rgbtBlue = (char)(sumyb / (i - y));
				image[a][b].rgbtGreen = (char)(sumyg / (i - y));
				image[a][b].rgbtRed = (char)(sumyr / (i - y));
				b++;
				x = (int)j;
			}
			fseek(inf, (paddingin + oldwidth * sizeof(RGBTRIPLE)) * (i - y - 1), SEEK_CUR);
			a++;
			y = (int)i;
			printf("\n");
		}
	}
	
	// writes bitmapfileheader to outf
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outf);
	
	// writes bitmapinfoheader to outf
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outf);
	
	int paddingout = (4 - bi.biWidth * sizeof(RGBTRIPLE) % 4) % 4;
	
	if(f < 1.0)
	{
		for(int i = 0; i < abs(bi.biHeight); i++)
		{
			for(int j = 0; j < bi.biWidth; j++)
			{
				fwrite(&image[i][j], sizeof(RGBTRIPLE), 1, outf);
			}
			for (int k = 0; k < paddingout; k++)
			{
				fputc(0x00, outf);
			}
		}
	}
	
	fclose(inf);
	fclose(outf);
}