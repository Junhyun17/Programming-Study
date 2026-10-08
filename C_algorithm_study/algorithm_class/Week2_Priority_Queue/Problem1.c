#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

void Selection_Sort(int arr[], int n) {
    int i, j, max, temp;

    for (i = 0; i < n - 1; i++) {
        max = 0;

        for (j = 1; j < n - i; j++) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }

        temp = arr[n - 1 - i];
        arr[n - 1 - i] = arr[max];
        arr[max] = temp;
    }
}

int main() {
	int n, i;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);

	for (i = 0;i < n;i++) {
		scanf("%d", &arr[i]);
	}

    Selection_Sort(arr, n);

	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);

	return 0;
}