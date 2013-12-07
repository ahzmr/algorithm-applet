/**
 * 顺序表实现两个大数相加
 */
#include "stdio.h"
#include "malloc.h"
#define MAXSIZE 256
typedef short DataType;
typedef struct list {
	DataType items[MAXSIZE];
	int length;
} SqList;


void View(SqList L) {
	int i;
	for(i=L.length-1; i>=0; i--)
		printf("%d",L.items[i]);
	printf("\n");
}


int LengthofStr(char *str) {
	int n;
	for(n=0; *str!='\0'; n++) str++;
	return n;
}


int Thangeto(char *str,SqList *L) {
	char *p;
	int i,length;
	length=LengthofStr(str);
	for(p=str,i=length-1; i>=0; i--) {
		if(*p<'0'||*p>'9') {
			printf("\n输入错误，请重新输入!\n");
			return 0;
		}
		L->items[length-1-i]=p[i]-'0';
	}
	L->items[length]=-1;
	L->length=length;
	return 1;
}

void Longadd(SqList L1,SqList L2,SqList *L) {
	int flag=0;	/* 进位 */
	int i,maxlength;
	maxlength=L1.length>L2.length?L1.length:L2.length;
	for(i=0; i<maxlength; i++) {
		if(i<L1.length&&i<L2.length)
			L->items[i]=L1.items[i]+L2.items[i]+flag;
		else if(i<L1.length)
			L->items[i]=L1.items[i]+flag;
		else if(i<L2.length)
			L->items[i]=L2.items[i]+flag;
		if(L->items[i]>9) {
			flag=L->items[i]/10;
			L->items[i]%=10;
		} else
			flag=0;
	}
	if(flag) {
		L->items[i]=flag;
		L->length=maxlength+1;
		L->items[i+1]=-1;
	} else {
		L->length=maxlength;
		L->items[i]=-1;
	}
}


int main() {
	char *str;
	SqList L[3];
	int i;
	for(i=0; i<2; i++) {
		printf("\n请输入第%d个数：",i+1);
		str=(char *)malloc(MAXSIZE*sizeof(char));
		scanf("%s",str);
		if(!Thangeto(str,&L[i])) return 0;
	}
	Longadd(L[0],L[1],&L[2]);
	printf("\n两数相加的结果为：\n   ");
	View(L[0]);
	printf(" + ");
	View(L[1]);
	printf(" = ");
	View(L[2]);
	printf("\n\n\n");
	return 0;
}
