/**
 *给出一个长度为N的字符串，求里面最长的回文子串长度
 */
#include<iostream>

using namespace std;

const int strLength=255;

int maxSubPaliStrLenthOfIndex(char* str, int forward, int back)
{
	int length = forward - back + 1;
	for(; '\0' != str[forward+1] && -1 < back-1 && str[back-1] == str[forward+1]; forward++, back--)
		length+=2;
	return length;
}

int maxSubPalindromeStr(char* str)
{
	int maxLength = 0, tmpLength = 0;
	for(int i=0; '\0' != str[i]; i++)
	{
		if(-1<i-1 && str[i] == str[i-1])
		{
			tmpLength = maxSubPaliStrLenthOfIndex(str, i, i-1);
		}
		else if(-1<i-2 && str[i] == str[i-2])
		{
			tmpLength = maxSubPaliStrLenthOfIndex(str, i, i-2);
		}
		if(tmpLength > maxLength)
		{
			maxLength = tmpLength;
		}
	}
	return maxLength;
}

int main(void)
{
	char* str = new char[strLength];
	cout<<"请输入字符串:";
	cin>>str;
	cout<<"此字符串的最长回文子串的长度为:"<<maxSubPalindromeStr(str);
	cout<<endl;
}
