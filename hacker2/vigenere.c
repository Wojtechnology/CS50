#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE
#include "/users/wojtekswiderski/documents/cs50/library50-c-5/cs50.c"

int main(int argc, string argv[])
{
	if(argc != 2)
	{
		printf("Wrong number of command line arguments\n");
		return 1;
	}
	char key[strlen(argv[1])];
	for(int i = 0; i < strlen(argv[1]); i++)
	{
		if(isupper(argv[1][i]))
		{
			key[i] = argv[1][i] - 65;
		}
		else if(islower(argv[1][i]))
		{
			key[i] = argv[1][i] - 97;
		}
		else
		{
			printf("Unacceptable symbol(s)\n");
			return 1;
		}
	}
	char* pass = GetString();
	char encrypted[strlen(pass)];
	for(int i = 0, j = 0; i < strlen(pass); i++)
	{
		if(j == strlen(argv[1]))
		{
			j = 0;
		}
		if(isupper(pass[i]))
		{
			encrypted[i] = (pass[i] - 65 + key[j]) % 26 + 65;
			j++;
		}
		else if(islower(pass[i]))
		{
			encrypted[i] = (pass[i] - 97 + key[j]) % 26 + 97;
			j++;
		}
		else
		{
			encrypted[i] = pass[i];
		}
		printf("%c", encrypted[i]);
	}
	printf("\n");
	if(pass != NULL)
	{
		free(pass);
	}
}