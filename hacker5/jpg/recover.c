#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

typedef unsigned char BYTE;

int main(void)
{
	FILE *raw = fopen("card.raw", "r");
	if(raw == NULL)
	{
		printf("Could not open file\n");
		return 1;
	}
	
	// finding the size of the file
	fseek(raw, 0, SEEK_END);
	int size = ftell(raw);
	
	// moving tracker to past the FAT file
	fseek(raw, BLOCK, SEEK_SET);
	
	// starting at -1 for num because don't want any data before the 
	// first jpeg header
	int num = -1;
	
	// need to declare file here so that it can be written to from
	// outside the conditional statements
	FILE *newfile;
	
	for(int i = 0; i < size; i += BLOCK)
	{
		int oldnum = num;
		BYTE tempdata[BLOCK];
		fread(tempdata, BLOCK, 1, raw);
		
		if(tempdata[0] == 0xff && tempdata[1] == 0xd8 && 
			tempdata[2] == 0xff && (tempdata[3] == 0xe0 || 
				tempdata[3] == 0xe1))
		{
			num++;
		}
		if(num >= 0)
		{
			char *filename = malloc(8);
			sprintf(filename, "%03i.jpg", num);
			filename[7] = '\0';
			if(num - oldnum != 0)
			{
				if(num > 0)
				{
					fclose(newfile);
				}
				newfile = fopen(filename, "w");
				if(newfile == NULL)
				{
					printf("Could not create new file\n");
					return 2;
				}
			}
			fwrite(tempdata, BLOCK, 1, newfile);
			free(filename);
		}
	}
	fclose(newfile);
	fclose(raw);
}