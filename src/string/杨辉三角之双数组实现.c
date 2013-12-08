/**
 * 杨辉三角之双数组实现
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 30

void print(long *, int);

int main(void)
{
	int i, n;
	long *array, *tmp, *t;
	array = (long *)malloc(MAXLINE * sizeof(long));
	tmp = (long *)malloc(MAXLINE * sizeof(long));
	for(n = 0; n < MAXLINE; n++)
	{
		for(i = 0; i <= n; i++)
		{
			if(0 == i || i == n)
			{
				tmp[i] = 1;
			}
			else
			{
				tmp[i] = array[i] + array[i - 1];
			}
		}
		t = tmp;
		tmp = array;
		array = t;
		printf("%d:\t", n + 1);
		print(array, n + 1);
	}
	return 0;
}

void print(long *array, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("%ld\t", array[i]);
	}
	printf("\n");
}
