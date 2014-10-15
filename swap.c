#include <stdio.h>

void change(int* a, int* b)
{
	int tmp = *b;
	*b = *a;
	*a = tmp;
}

int main(void)
{
	int x = 1;
	int y = 2;
	
	printf("x is %i and y is %i\n", x, y);
	change(&x, &y);
	
	printf("x is %i and y is %i\n", x, y);
}