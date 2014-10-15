#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE
#include "/users/wojtekswiderski/documents/cs50/library50-c-5/cs50.c"

int decrypt(char* pass, char* word)
{
	char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
	char salt[2];
	for(int i = 0; i < 64; i++)
	{
		for(int j = 0; j < 64; j++)
		{
			salt[0] = charset[i];
			salt[1] = charset[j];
			if(strcmp(pass, crypt(word, salt)) == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

int main(int argc, string argv[])
{
	if(argc != 2)
	{
		printf("Wrong number of arguments\n");
		return 1;
	}
	FILE* fp;
	fp = fopen("/usr/share/dict/web2", "r");
	
	if(fp == NULL)
	{
		printf("File did not open\n");
		return 1;
	}
	
	char letters[256];
	
	while(fgets(letters, sizeof(letters), fp))
	{
		int i = 0;
		while(letters[i] != '\n')
		{
			i++;
		}
		letters[i] = '\0';
		if(decrypt(argv[1], letters) == 0)
		{
			printf("%s\n", letters);
			return 0;
		}
	}
	
	printf("Password not found\n");

	fclose(fp);
}