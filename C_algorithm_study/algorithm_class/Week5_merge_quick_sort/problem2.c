#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void inPlaceQuickSort(int* L, int l, int r);
void inPlacePartition(int* L, int l, int r, int index, int* a, int* b);
int findPivot(int l, int r);
void swap(int* a, int* b);

void inPlaceQuickSort(int* L, int l, int r) {
    if (l >= r) return;

    int index = findPivot(l, r);
    int a, b;

    inPlacePartition(L, l, r, index, &a, &b);
    inPlaceQuickSort(L, l, a - 1);
    inPlaceQuickSort(L, b + 1, r);
}

void inPlacePartition(int* L, int l, int r, int index, int* a, int* b) {
    int pivot = L[index];
    swap(&L[l], &L[index]);

    int i = l + 1, j = l + 1, k = r;

    while (j <= k) {
        if (L[j] < pivot) {
            swap(&L[i], &L[j]);
            i++;
            j++;
        }
        else if (L[j] > pivot) {
            swap(&L[j], &L[k]);
            k--;
        }
        else {
            j++;
        }
    }

    swap(&L[l], &L[i - 1]);

    *a = i;
    *b = j - 1;
}

int findPivot(int l, int r) {
    return (l + r) / 2;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    scanf("%d", &n);

    int* L = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &L[i]);
    }

    inPlaceQuickSort(L, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf(" %d", L[i]);
    }
    printf("\n");
    free(L);
    return 0;
}