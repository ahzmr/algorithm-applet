/**
 * 汉诺塔的解法
 */
#include<stdio.h>
#include<stdlib.h>

int hanoiLength = 3;
int *conf; /* Element conf[d] gives the current position of disk d. */

void init(void) {
	int i = 0;
	for(i = 0; i < hanoiLength; i++) {
		conf[i] = 0;
	}
}

void printResult(void) {
	int i = 0;
	int peg = 0;
	static int stepCount = 1;
	printf("\n= - = - === %d === - = - =", stepCount);
	for(peg = 0; peg < 3; peg++) {
		printf("\n%d:\t", peg + 1);
		for(i = 0; i < hanoiLength; i++) {
			if(peg == conf[i]) {
				printf("%d\t", i + 1);
			} else {
				printf("\t");
			}
		}
	}
	stepCount++;
}

void move(int d, int t) {
	/* move disk d to peg t */
	conf[d] = t;
}

void hanoi(int h, int t) {
	int f = 0;
	int r = 0;
	if (h > 0) {
		f = conf[h-1];
		if (f != t) {
			r = 3 - f - t ;
			hanoi(h-1, r);
			move(h-1, t);
			printResult();
		}
		hanoi(h-1, t);
	}
}

int main(void) {
	printf("= - = - = 汉诺塔求解 = - = - =\n请输入汉诺塔的盘子数：");
	scanf("%d", &hanoiLength);
	while(0 >= hanoiLength) {
		printf("盘子数不能为负值，请重新输入：");
		scanf("%d", &hanoiLength);
	}
	conf = malloc(hanoiLength * sizeof(int));
	init();
	printf("%d汉诺塔的解为：", hanoiLength);
	hanoi(hanoiLength, 2);
	printf("\n");
	system("pause");
	return 0;
}
