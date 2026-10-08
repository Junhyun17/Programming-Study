#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

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

void rBuildHeap(int i) {
    if (i > n) {
        return;
    }

    rBuildHeap(2 * i);
    rBuildHeap(2 * i + 1);
    downHeap(i);
}

void buildHeap() {
    for (int i = n / 2; i >= 1; i--) {
        downHeap(i);
    }
    return;
}

void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
}

int main() {
    int key, value;

    scanf("%d", &key);

    for (int i = 1; i <= key; i++) {
        scanf("%d", &value);
        H[i] = value;
        n++;
    }

    rBuildHeap(1);
    printHeap();

    return 0;
}
