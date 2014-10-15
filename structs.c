#include <stdio.h>
#include <stdlib.h>
#include "/users/wojtekswiderski/documents/cs50/library50-c-5/cs50.c"

#include "student.h"

#define STUDENTS 3

int main(void)
{
	student students[STUDENTS];
	
	for(int i = 0; i < STUDENTS; i++)
	{
		students[i].name = GetString();
		students[i].residence = GetString();
	}
	FILE* file = fopen("students.csv", "w");
	if(file != NULL)
	{
		for(int i = 0; i < STUDENTS; i++)
		{
			fprintf(file, "%s,%s\n", students[i].name, students[i].residence);
		}
		fclose(file);
	}
	for(int i = 0; i < STUDENTS; i++)
	{
		if(students[i].name != NULL)
		{
			free(students[i].name);
		}
		if(students[i].residence != NULL)
		{
			free(students[i].residence);
		}
	}
}