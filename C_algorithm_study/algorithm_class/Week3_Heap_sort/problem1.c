#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

int H[100], n;

void upHeap(int i) {
	if (i == 1) {
		return;
	}

	if (H[i] <= H[i / 2]) {
		return;
	}

	int temp = H[i];
	H[i] = H[i / 2];
	H[i / 2] = temp;

	upHeap(i / 2);
}

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

void insertItem(int key) {
	n = n + 1;
	H[n] = key;
	upHeap(n);
}

int removeMax() {
	int key = H[1];
	H[1] = H[n];
	n = n - 1;
	downHeap(1);
	return key;
}

void printHeap() {
	for (int i = 1; i < n + 1; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

int main() {
	char command;
	int key;

	while (1) {
		scanf("%c", &command);

		if (command == 'i') {
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
		}
		else if (command == 'd') {
			int remove = removeMax();
			printf("%d\n", remove);
		}
		else if (command == 'p') {
			printHeap();
		}

		else if (command == 'q') {
			break;
		}
	}
}