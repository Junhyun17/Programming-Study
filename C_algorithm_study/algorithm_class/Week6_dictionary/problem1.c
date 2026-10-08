#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int rFE(int arr[], int left, int right, int key) {
    if (left > right) {
        return right;
    }

    int mid = (left + right) / 2;

    if (arr[mid] == key) {
        return mid;
    }
    else if (arr[mid] > key) {
        return rFE(arr, left, mid - 1, key);
    }
    else {
        return rFE(arr, mid + 1, right, key);
    }
}

int main() {
    int n, key, i, result;

    scanf("%d", &n);
    scanf("%d", &key);

    int* arr = (int*)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    result = rFE(arr, 0, n - 1, key);

    printf(" %d\n", result);

    free(arr);
    return 0;
}
