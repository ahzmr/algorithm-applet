#define OVERFLOW -2
#define FALSE     0
#define TRUE      1
#define NULL      0
#define LIST_INIT_SIZE 51200
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Status;
// 顺序表类型
typedef struct
{
	Status elem[LIST_INIT_SIZE];
	int length;
} SqList;

// 初始化顺序表
void InitSqList(SqList *L)
{
	(*L).length=0;
}

// 输出顺序表
void PrintSqList(SqList L)
{
	int i;
	for(i=L.length-1; i>=0; i--)
		printf("%d",L.elem[i]);
}

// 过滤数字串中的逗号
void ChangeStringToNumber(char *p)
{
	char *q=p;
	while(*p=='0') ++p;
	while (*p)
	{
		if (*p>='0' && *p<='9')
		{
			if(q!=p) *q=*p;
			q++;
		}
		p++;
	}
	*q='\0';
}

// 输入数字串并存储于顺序表中
void InputNumber(SqList *L)
{
	char a[LIST_INIT_SIZE];
	int i,n;
	fflush(stdin);
	gets(a);
	ChangeStringToNumber(a);
	n=strlen(a);
	for(i=0; i<n; i++)
		(*L).elem[n-i-1]=a[i]-'0';
	(*L).length=n;
}

// 两个任意长的整数相加
void AddNumber(SqList La,SqList Lb,SqList *Lc)
{
	int n1,n2,i,s,cf;
	n1=La.length;
	n2=Lb.length;
	i=0;
	cf=0;
	while(i<n1 && i<n2)
	{
		s=La.elem[i]+Lb.elem[i]+cf;
		(*Lc).elem[i]=s%10;
		cf=s/10;
		i++;
	}
	(*Lc).length=i;
	while (i<n1)
	{
		if(cf)
		{
			s=La.elem[i]+cf;
			(*Lc).elem[i]=s%10;
			cf=s/10;
		}
		else (*Lc).elem[i]=La.elem[i];
		i++;
		(*Lc).length++;
	}
	while (i<n2)
	{
		if(cf)
		{
			s=Lb.elem[i]+cf;
			(*Lc).elem[i]=s%10;
			cf=s/10;
		}
		else (*Lc).elem[i]=Lb.elem[i];
		i++;
		(*Lc).length++;
	}
	if (cf)
	{
		(*Lc).elem[i]=cf;
		(*Lc).length++;
	}
}


// 两个任意长的整数相乘
int MutNumber(SqList La,SqList Lb,SqList *Lc)
{
	int n1,n2,i,j,c,h;
	n1=La.length;
	n2=Lb.length;
	if(n1+n2>=LIST_INIT_SIZE) return 0;
	for(i=0; i<n1+n2; ++i) Lc->elem[i]=0;
	Lc->length=0;
	for(i=0; i<n1; i++ )
	{
		c=0;
		for(j=0; j<n2; j++)
		{
			h=(*Lc).elem[i+j]+La.elem[i]*Lb.elem[j]+c;
			(*Lc).elem[i+j]=h%10;
			c=h/10;
		}
		(*Lc).length=i+j;
		if (c)
		{
			(*Lc).elem[i+j]+=c;
			(*Lc).length++;
		}
	}
	return 1;
}

// 自减
void Number__(SqList *L)
{
	int i=0;
	while(L->elem[i]==0)
		++i;
	if(i!=0) L->elem[i]--;
	while(--i>=0)
		L->elem[i]=9;
	L->elem[0]--;
	while(L->elem[L->length-1]==0)
		L->length--;
}

// 阶乘
int Factorial(SqList La,SqList *Lc)
{
	Lc->elem[0]=1;
	Lc->length=1;
	while(La.length)
	{
		if(!MutNumber(La,*Lc,Lc))
			return 0;
		Number__(&La);
	}
	return 1;
}


// 主函数
int main()
{
	SqList a,b,c;
	char op;
	do
	{
		printf("请选择(1、两个任意长的整数相乘；other、任意长的整数阶乘) ：");
		fflush(stdin);
		scanf("%c",&op);
		printf("\nInput number1:");
		InitSqList(&a);
		InputNumber(&a);
		InitSqList(&c);
		if(op=='1')
		{
			printf("\nInput number2:");
			InitSqList(&b);
			InputNumber(&b);
			if(MutNumber(a,b,&c))
			{
				printf("\n");
				PrintSqList(a);
				printf(" * ");
				PrintSqList(b);
				printf(" = ");
				PrintSqList(c);
			}
			else
				printf("\n计算结果长度过长，计算失败\n");
		}
		else
		{
			if(Factorial(a,&c))
			{
				printf("\n");
				PrintSqList(a);
				printf(" != ");
				PrintSqList(c);
			}
			else
				printf("\n计算结果长度过长，计算失败\n");
		}
		printf("\n\n输入Q退出，其它断续求解：");
		fflush(stdin);
		scanf("%c",&op);
	}
	while(op!='Q'&&op!='q');
	printf("\n\n");
	system("pause");
}
