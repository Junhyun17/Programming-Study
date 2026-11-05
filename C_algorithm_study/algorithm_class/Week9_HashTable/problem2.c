#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int* H;
int M;

void insertItem(int x);
void findElement(int x);

void insertItem(int x) {
    int index = x % M;

    while (H[index] != 0) {
        printf("C");
        index = (index + 1) % M;
    }

    H[index] = x;
    printf("%d\n", index);
}

void findElement(int x) {
    int index = x % M;

    while (H[index] != 0) {
        if (H[index] == x) {
            printf("%d %d\n", index, x);
            return;
        }

        index = (index + 1) % M;
    }

    printf("-1\n");
}

int main() {
    int M_input, n, x;
    int count = 0;
    char command;

    scanf("%d %d", &M_input, &n);
    M = M_input;

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
        else if (command == 'e') {
            break;
        }
    }

    free(H);

    return 0;
}
