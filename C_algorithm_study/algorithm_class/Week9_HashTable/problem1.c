#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node** H;
int M;

void insertItem(int x);
int findElement(int x);
int removeElement(int x);
void printHash();


void insertItem(int x) {
    int index = x % M;

    Node* n = (Node*)malloc(sizeof(Node));
    n->key = x;
    n->next = H[index];
    H[index] = n;
}

int findElement(int x) {
    int index = x % M;
    Node* n = H[index];
    int rank = 1;

    while (n != NULL) {
        if (n->key == x) {
            return rank;
        }
        n = n->next;
        rank++;
    }

    return 0;
}

int removeElement(int x) {
    int index = x % M;
    Node* n = H[index];
    Node* prev = NULL;
    int rank = 1;

    while (n != NULL) {
        if (n->key == x) {
            if (prev == NULL) {
                H[index] = n->next;
            }
            else {
                prev->next = n->next;
            }

            free(n);
            return rank;
        }

        prev = n;
        n = n->next;
        rank++;
    }

    return 0;
}

void printHash() {
    for (int i = 0; i < M; i++) {
        Node* n = H[i];

        while (n != NULL) {
            printf(" %d", n->key);
            n = n->next;
        }
    }
    printf("\n");
}

int main() {
    char command;
    int x, i;

    scanf("%d", &M);

    H = (Node**)calloc(M, sizeof(Node*));

    while (1) {
        scanf(" %c", &command);

        if (command == 'i') {
            scanf("%d", &x);
            insertItem(x);
        }
        else if (command == 's') {
            scanf("%d", &x);
            printf("%d\n", findElement(x));
        }
        else if (command == 'd') {
            scanf("%d", &x);
            printf("%d\n", removeElement(x));
        }
        else if (command == 'p') {
            printHash();
        }
        else if (command == 'e') {
            break;
        }
    }

    for (i = 0; i < M; i++) {
        Node* p = H[i];

        while (p != NULL) {
            Node* temp = p;
            p = p->next;
            free(temp);
        }
    }

    free(H);

    return 0;
}
