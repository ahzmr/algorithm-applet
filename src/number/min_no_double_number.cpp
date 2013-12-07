/**
 * 给出任意一个正整数，算出大于它的最小不重复数（即不存在相邻两个数相同的情况）
 */
#include<iostream>

using namespace std;

long minNoDoubleNumber(long x) {
	if(x < 10) {
		return x;
	}

	long y = 1;
	long temp = x;
	while(temp / 10 > 0) {
		y *= 10;
		temp /= 10;
	}
	y /= 10;

	int next;
	while(y > 0) {
		next = (x / y) % 10;
		if((x / 10 / y) % 10 == next) {
			x += y;
			if(9 == next) {
				return minNoDoubleNumber(x);
			}
		} else {
			y /= 10;
		}
	}
	return x;
}

int main(void) {
	long x;
	cout<<"x=";
	cin>>x;
	cout<<"result="<<minNoDoubleNumber(x)<<endl;
}
