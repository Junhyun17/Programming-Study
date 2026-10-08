#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

void downHeap(int i);
void buildHeap();
void inPlaceHeapSort();
void printArray();

int H[100], n;

void downHeap(int i) {
	int left = i * 2;
	int right = i * 2 + 1;
	int large = i;
	int temp;

	if (left <= n && H[left] > H[large]) {
		large = left;
	}

	if (right <= n && H[right] > H[large]) {
		large = right;
	}

	if (large != i) {
		temp = H[i];
		H[i] = H[large];
		H[large] = temp;
		downHeap(large);
	}
}

void buildHeap() {
	int i;

	for (i = n / 2; i >= 1; i--) {
		downHeap(i);
	}
	return;
}

void inPlaceHeapSort() {
	int num, i;

	buildHeap();
	num = n;

	for (i = num; i > 1; i--) {
		int temp = H[1];
		H[1] = H[i];
		H[i] = temp;
		n--;
		downHeap(1);
	}
	n = num;
}

void printArray() {
	int i;

	for (i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

int main() {
	int num, i;
	
	scanf("%d", &num);
	
	n = num;

	for (i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}

	inPlaceHeapSort();
	printArray();

	return 0;
}