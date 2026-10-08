#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

void Insert_Sort(int arr[], int n) {
	int i, j, ins;

	for (i = 1;i < n;i++) {
		ins = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > ins) {
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = ins;
	}
}
int main() {
	int n, i;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);

	for (i = 0;i < n;i++) {
		scanf("%d", &arr[i]);
	}

	Insert_Sort(arr, n);

	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);

	return 0;
}