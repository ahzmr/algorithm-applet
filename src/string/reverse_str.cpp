/**
 * 实现字符串反转，要求不使用任何系统函数，且时间复杂度最小，函数原型：char* reverse_str(char* str)。
 */
#include<iostream>

using namespace std;

char* reverse_str(char* str) {
	int i = 0;
	while('\0' != str[i]) {
		i++;
	}
	char ch;
	int other;
	for(int mid = i / 2, len = --i; i >= mid; i--) {
		other = len - i;
		if(i == other) {
			break;
		}
		ch = str[i];
		str[i] = str[other];
		str[other] = ch;
	}
	return str;
}

int main(void) {
	cout<<"请输入字符串:";
	char* str = new char[1024];
	cin>>str;
	cout<<"反转后的结果为:"<<reverse_str(str);
	cout<<endl;
}
