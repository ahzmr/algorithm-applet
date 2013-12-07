/**
 * Huffman编码
 */
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>

typedef struct hufNode
{
	float weight;
	int parents,lchild,rchild;
} hufNode;
typedef struct hufCode
{
	char* hcode;
	float p;
} hufCode;

int N,MAXS;

void print(hufCode hufcode[])
{
	int i=0;
	printf("对应的huffman编码为：\n");
	for(i=0; i!=N; ++i)
		printf("%3d: %-5g %-8s\n",i+1,hufcode[i].p,hufcode[i].hcode);
	return;
}

int min(hufNode huf[])
{
	int min=N,i=0;
	for(i=0; i!=MAXS; ++i)
		if(huf[i].parents==-1)
		{
			if(min==N||huf[i].weight<huf[min].weight)
				min=i;
		}
	return min;
}

void hufman(hufNode huf[],hufCode hufcode[])
{
	int lchild,rchild,i=0,j=0;
	char *cc;
	int start=N-1;
	cc=(char *)malloc(N*sizeof(char));
	for(i=N; i!=MAXS; ++i)
	{
		lchild=min(huf);
		huf[i].lchild=lchild;
		huf[lchild].parents=i;
		rchild=min(huf);
		huf[i].rchild=rchild;
		huf[rchild].parents=i;
		huf[i].parents=-1;
		huf[i].weight=huf[lchild].weight+huf[rchild].weight;
	}
	for(i=0; i!=N; ++i)
	{
		hufcode[i].p=huf[i].weight;
		start=N-1;
		cc[start]='\0';
		for(j=i; huf[j].parents!=-1; j=huf[j].parents)
		{
			if(huf[huf[j].parents].lchild==j)
				cc[--start]='0';
			else
				cc[--start]='1';
		}
		hufcode[i].hcode=(char *)malloc((strlen(cc+start)+1)*sizeof(char));
		strcpy(hufcode[i].hcode,cc+start);
	}
	return;
}

int main(void)
{
	int i=0;
	hufNode *huf;
	hufCode *hufcode;
	float sum=0;
	printf("请输入信源元素个数：");
	scanf("%d",&N);
	while(N<=0)
	{
		printf("输入错误，请重新输入!\n");
		scanf("%d",&N);
	}
	if(N==1)
		printf("元素个数为1，不用求解。\n");
	else
	{
		MAXS=N*2-1;
		if( !( huf=(hufNode *)malloc( MAXS*sizeof( hufNode ) ) ) )
		{
			printf("内存错误！\n");
			goto exit;
		}
		printf("请输入相应的概率：\n");
		for(i=0; i!=N; ++i)
		{
			scanf("%f",&huf[i].weight);
			while(huf[i].weight<0&&huf[i].weight>1)
			{
				printf("输入错误，请输入[0,1]之间的数。\n");
				scanf("%f",&huf[i].weight);
			}
			sum+=huf[i].weight;
			huf[i].parents=huf[i].lchild=huf[i].rchild=-1;
		}
		if(sum<0.999999||sum>1.000001)
		{
			printf("总概率不为1，错误！\n");
			goto exit;
		}
		hufcode=(hufCode *)malloc(N*sizeof(hufCode));
		hufman(huf,hufcode);
		print(hufcode);
	}
	printf("\n\n");
exit:
	system("pause");
	return 0;
}
