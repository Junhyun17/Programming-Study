#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int iFE(int arr[], int n, int key) {
    int left = 0, right = n - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;

        if (arr[mid] == key) {
            return mid;
        }
        else if (arr[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return left;
}

int main() {
    int n, key, i, result;

    scanf("%d", &n);
    scanf("%d", &key);

    int* arr = (int*)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    result = iFE(arr, n, key);

    printf(" %d\n", result);

    free(arr);
    return 0;
}