/**
 * 给定一个如下格式的字符串(1,(2,3),(4,(5,6),7))括号内的元素可以是数字，也可以是另一个括号，请实现一个算法消除嵌套的括号，比如把上面的表达式变成：(1,2,3,4,5,6,7)，如果表达式有误请报错。
 */
#include<iostream>

using namespace std;

const int INVALID_INDEX = -1;

char* clean_inner_bracket(char* str) {
	int startLen = 0;
	int replaceIndex = INVALID_INDEX;
	for(int i = 0; '\0' != str[i]; i++) {
		switch(str[i]) {
			case '(':
				startLen++;
				if(1 < startLen && INVALID_INDEX == replaceIndex) {
					replaceIndex = i;
				}
				break;
			case ')':
				if(1 < startLen--) {
					break;
				}
			default:
				if(INVALID_INDEX != replaceIndex) {
					str[replaceIndex++] = str[i];
				}
				break;
		} 
	}
	if(INVALID_INDEX != replaceIndex) {
		str[replaceIndex] = '\0';
	}
	if(0 != startLen) {
		cout<<"括号总数不匹配"<<endl;
	}
	return str;
}

int main(void) {
	cout<<"请输入字符串:";
	char* str = new char[1024];
	cin>>str;
	cout<<"去除掉嵌套括号的结果为:"<<clean_inner_bracket(str);
	cout<<endl;
}
