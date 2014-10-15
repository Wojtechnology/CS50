#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "/users/wojtekswiderski/documents/cs50/library50-c-5/cs50.c"

int main(void)
{
	printf("Say something: ");
	char* s = GetString();
	if(s == NULL)
	{
		return 1;
	}
	char* t = malloc((strlen(s) + 1));
	
	if(t == NULL){
		return 1;
	}
	
	int n = strlen(s);
	for(int i = 0; i <= n; i++)
	{
		t[i] = s[i];
	}
	
	if(strlen(t) > 0)
	{
		t[0] = toupper(t[0]);
	}
	printf("s is %s\n", s);
	printf("t is %s\n", t);
	free(s);
	free(t);
}