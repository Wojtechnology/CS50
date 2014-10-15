#include <stdio.h>
#include <string.h>
#include "/users/wojtekswiderski/documents/cs50/library50-c-5/cs50.c"

int main(void)
{
	printf("Say something: ");
	char* s = GetString();
	printf("Say something: ");
	char* t = GetString();
	
	if(s != NULL && t != NULL)
	{
		if(strcmp(s, t) == 0)
		{
			printf("You typed the same thing!\n");
		}
		else
		{
			printf("You typed different things!\n");
		}
		free(s);
		free(t);
	}
}