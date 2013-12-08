/**
 * 杨辉三角之二维数据实现
 */
#include <stdio.h>

void print(int *, int);

int main(void)
{
	int i, n;
	int a[10][10];
	for(n = 0; n < 10; n++)
	{
		for(i = 0; i <= n; i++)
		{
			if(0 == i || i == n)
			{
				a[n][i] = 1;
			}
			else
			{
				a[n][i] = a[n - 1][i] + a[n - 1][i-1];
			}
		}
		printf("%d:\t", n + 1);
		print(a[n], n + 1);
	}
	return 0;
}

void print(int a[], int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("%d\t", a[i]);
	}
	printf("\n");
}
