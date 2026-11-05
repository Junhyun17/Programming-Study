
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int* H;
int M, q;

void insertItem(int x);
void findElement(int x);
void printHash();

void insertItem(int x) {
    int index = x % M;
    int step = q - (x % q);

    int count = 0;

    while (H[index] != 0 && count < M) {
        printf("C");
        index = (index + step) % M;
        count++;
    }

    if (count == M) {
        printf("-1\n");
        return;
    }

    H[index] = x;
    printf("%d\n", index);
}

void findElement(int x) {
    int index = x % M;
    int step = q - (x % q);

    for (int i = 0; i < M; i++) {
        if (H[index] == x) {
            printf("%d %d\n", index, x);
            return;
        }

        if (H[index] == 0) {
            break;
        }

        index = (index + step) % M;
    }

    printf("-1\n");
}

void printHash() {
    for (int i = 0; i < M; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
}

int main() {
    char command;
    int n, x;
    int count = 0;

    scanf("%d %d %d", &M, &n, &q);

    H = (int*)calloc(M, sizeof(int));

    while (1) {
        scanf(" %c", &command);

        if (command == 'i') {
            scanf("%d", &x);

            if (count < n) {
                insertItem(x);
                count++;
            }
        }
        else if (command == 's') {
            scanf("%d", &x);
            findElement(x);
        }
        else if (command == 'p') {
            printHash();
        }
        else if (command == 'e') {
            printHash();
            break;
        }
    }

    free(H);

    return 0;
}
