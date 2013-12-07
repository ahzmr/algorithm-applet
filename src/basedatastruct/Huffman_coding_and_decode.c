/**
 * Huffman编码与译码
 */
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>

typedef char DataType;
typedef struct hufNode
{
	DataType ch;
	float weight;
	int parents,lchild,rchild;
} hufNode;
typedef struct hufCode
{
	char* hcode;
	float p;
} hufCode;

int N,MAXS;

void Print(hufCode *hufcode,hufNode *huf)
{
	int i=0;
	printf("对应的huffman编码为(序号 字符 概率 编码)：\n");
	for(i=0; i!=N; ++i)
		printf("%3d: %c %-5g %-8s\n",i+1,huf[i].ch,hufcode[i].p,hufcode[i].hcode);
	return;
}

int Min(hufNode huf[])
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

void Huffman(hufNode huf[],hufCode hufcode[])
{
	int lchild,rchild,i=0,j=0;
	char *cc;
	int start=N-1;
	cc=(char *)malloc(N*sizeof(char));
	for(i=N; i!=MAXS; ++i)
	{
		lchild=Min(huf);
		huf[i].lchild=lchild;
		huf[lchild].parents=i;
		rchild=Min(huf);
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

int SearchNode(DataType ch,hufNode *huf)
{
	int i;
	for(i=0; i!=N; ++i)
		if(huf[i].ch==ch) return i;
	return -1;
}

void Coding(hufNode *huf,hufCode *hufcode)
{
	DataType ch;
	int flag=1;
	printf("\n请输入要进行编码的文章：\n");
	fflush(stdin);
	while((ch=getchar())!='\n')
	{
		if(flag)
		{
			printf("\n对应的编码为：\n");
			flag=0;
		}
		if(SearchNode(ch,huf)==-1)
		{
			printf("\n字符集中不存在字符%c，错误！\n\n",ch);
			return;
		}
		printf("%s",hufcode[SearchNode(ch,huf)].hcode);
	}
	printf("\n\n编码结束。\n\n");
}

void Recoding(hufNode *huf)
{
	DataType ch;
	int code=MAXS-1;
	int flag=1;
	printf("请输入要进行译码的文章：\n");
	fflush(stdin);
	while((ch=getchar())!='\n')
	{
		if(flag)
		{
			printf("\n对应的译码为：\n");
			flag=0;
		}
		if(ch=='0')
		{
			if(huf[code].lchild!=-1) code=huf[code].lchild;
			else
			{
				printf("\n编码不存在，错误！\n\n");
				return;
			}
		}
		else if(ch=='1')
		{
			if(huf[code].rchild!=-1) code=huf[code].rchild;
			else
			{
				printf("\n编码不存在，错误！\n\n");
				return;
			}
		}
		else
		{
			printf("\n译码字符集中只有0和1！\n\n");
			return;
		}
		if(huf[code].lchild==-1&&huf[code].rchild==-1)
		{
			printf("%c",huf[code].ch);
			code=MAXS-1;
		}
	}
	printf("\n\n译码结束。\n\n");
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
		fflush(stdin);
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
		fflush(stdin);
		printf("请对应输入信源字符集:");
		for(i=0; i!=N; ++i)
			scanf("%c",&huf[i].ch);
		hufcode=(hufCode *)malloc(N*sizeof(hufCode));
		Huffman(huf,hufcode);
		Print(hufcode,huf);
		Coding(huf,hufcode);
		Recoding(huf);
	}
	printf("\n\n");
exit:
	system("pause");
	return 0;
}
