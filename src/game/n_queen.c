/**
 * n后问题
 */
#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<time.h>

typedef long count;
count allCount = 0;

int place(int x[], int k)
{
    int i;
    for(i=1; i<k; ++i)
        if((x[i]==x[k])||(abs(x[i]-x[k])==abs(i-k)))
            return 0;
    return 1;
}

void print(int n, int x[])
{
    static count count = 0;
    if(0 == count)
    {
        printf("问题的解为：\n");
    }
    int i=0;
    printf("%3d: ", ++count);
    for(i=1; i!=n+1; i++)
        printf("%3d",x[i]);
    printf("\n");
}

void n_queens(int n,int x[])
{
    int k=1;
    x[1]=0;
    while(k>0)
    {
        x[k]=x[k]+1;
        while((x[k]<=n)&&(!place(x,k)))
            x[k]+=1;
        if(x[k]<=n)
        {
            if(k==n)
            {
                print(n,x);
                allCount++;
                continue;
            }
            else
            {
                ++k;
                x[k]=0;
            }
        }
        else
        {
            x[k]=0;
            --k;
        }
    }
}

int main()
{
    int *x=NULL,n=0;
    clock_t startCT, endCT;
    double usedSec;
    printf("请输入n后问题的数值n：");
    scanf("%d",&n);
    while(n<1)
    {
        printf("输入负数，错误，请重新输入：");
        scanf("%d",&n);
    }
    x=(int*)malloc((n+1)*sizeof(int));

    startCT = clock();
    n_queens(n,x);
    endCT = clock();
    usedSec = difftime(endCT, startCT) / 1000;

    printf("解的总个数为：%d。用时%.3f秒。\n", allCount, usedSec);
    printf("\n");
	system("pause");
    return 0;
}
