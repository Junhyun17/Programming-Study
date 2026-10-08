#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* addList(Node* node, int data);
void printList(Node* node);
Node* mergeSort(Node* L);
Node* rMergeSort(Node* L, int l, int r);
Node* merge(Node* L1, Node* L2);
Node* partition(Node* L, int k);
void freeList(Node* head);

Node* addList(Node* node, int data) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;

    if (node == NULL) {
        return p;
    }
    else {
        Node* q = node;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = p;
    }
    return node;
}

void printList(Node* node) {
    while (node != NULL) {
        printf(" %d", node->data);
        node = node->next;
    }
    printf("\n");
}

Node* mergeSort(Node* L) {
    int n = 0;
    Node* p = L;

    while (p != NULL) {
        n++;
        p = p->next;
    }

    return rMergeSort(L, 0, n - 1);
}

Node* rMergeSort(Node* L, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        int k = m - l + 1;

        Node* L2 = partition(L, k);
        Node* L1 = rMergeSort(L, l, m);
        
        L2 = rMergeSort(L2, m + 1, r);

        return merge(L1, L2);
    }

    return L;
}

Node* merge(Node* L1, Node* L2) {
    Node p;
    Node* k = &p;

    p.next = NULL;

    while (L1 != NULL && L2 != NULL) {
        if (L1->data <= L2->data) {
            k->next = L1;
            L1 = L1->next;
        }
        else {
            k->next = L2;
            L2 = L2->next;
        }

        k = k->next;
    }

    while (L1 != NULL) {
        k->next = L1;
        L1 = L1->next;
        k = k->next;
    }

    while (L2 != NULL) {
        k->next = L2;
        L2 = L2->next;
        k = k->next;
    }

    return p.next;
}

Node* partition(Node* L, int k) {
    Node* p = L;

    for (int i = 0; i < k - 1 && p != NULL; i++) {
        p = p->next;
    }

    if (p) {
        Node* L2 = p->next;
        p->next = NULL;
        return L2;
    }
    else {
        return NULL;
    }
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n, data;

    Node* L = NULL;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        L = addList(L, data);
    }

    L = mergeSort(L);
    printList(L);

    freeList(L);

    return 0;
}