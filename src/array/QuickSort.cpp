/**
 * 快速排序实现
 */
#include <iostream>
using namespace std;

template <class Type>
void print(Type array[], int length);

template <class Type>
int split(Type array[], int start, int end);

template <class Type>
void quickSort(Type array[], int start, int end);

template <class Type>
int split(Type array[], int start, int end) {
	Type tmp = array[start];
	int minIndex = start;
	for(int i = start + 1; i < end; i++) {
		if(array[i] <= tmp) {
			minIndex++;
			if(minIndex != i) {
				swap(array[i], array[minIndex]);
			}
		}
	}
	if(start != minIndex) {
		swap(array[start],array[minIndex]);
	}
	return minIndex;
}

template <class Type>
void quickSort(Type array[], int start, int end) {
	int k;
	if(start < end) {
		k = split(array, start, end);
		quickSort(array, start, k);
		quickSort(array, k+1, end);
	}
}

template <class Type>
void print(Type array[], int length) {
	for(int i = 0; i < length; i++) {
		cout<<array[i]<<"\t";
	}
	cout<<endl;
}

int main() {
	int length;
	int *array;
	cout<<"请输入数组元素个数：";
	do {
		cin>>length;
	} while(0 >= length);
	cout<<"请输入每个元素，用空格分隔："<<endl;
	array = new int[length];
	for(int i = 0; i < length; i++) {
		cin>>array[i];
	}
	cout<<"The arrays are befor sort:";
	print(array, length);
	quickSort(array, 0, length);
	cout<<"The arrays are after sort:";
	print(array, length);
}
