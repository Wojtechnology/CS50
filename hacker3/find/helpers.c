/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
      
#include "helpers.h"
#include <stdio.h>

bool binsearch(int value, int values[], int min, int max)
{
	int mid = (max + min) / 2;
	if(max < min)
	{
		return false;
	}
	else if(value == values[mid])
	{
		return true;
	}
	else if(value > values[mid])
	{
		return binsearch(value, values, mid + 1, max);
	}
	else if(value < values[mid])
	{
		return binsearch(value, values, min, mid - 1);
	}
	else
	{
		return false;
	}
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
	if(n < 1)
	{
		return false;
	}
	else
	{
		return binsearch(value, values, 0, n - 1);
	}
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
	/*int sorted = 0;
	do
	{
		sorted = 0;
		for(int i = 0; i < n - 1; i++)
		{
			if(values[i] > values[i + 1])
			{
				int tmp = values[i];
				values[i] = values[i + 1];
				values[i + 1] = tmp;
				sorted++;
			}
		}
	}
	while(sorted != 0);*/
	
	
	int limit = 65536;
	int places[limit];
	for(int i = 0; i < limit; i++)
	{
		places[i] = 0;
	}
	for(int i = 0; i < n; i++)
	{
		places[values[i] % limit]++;
	}
	int c = 0;
	for(int i = 0; i < limit; i++)
	{
		if(places[i] > 0)
		{
			for(int j = 0; j < places[i]; j++)
			{
				values[c] = i;
				c++;
			}
		}
	}
    return;
}
