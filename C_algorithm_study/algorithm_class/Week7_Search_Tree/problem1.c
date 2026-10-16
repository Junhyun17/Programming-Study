#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Node {
    int key;
    struct Node* parent;
    struct Node* lChild;
    struct Node* rChild;
} Node;

Node* root;

Node* getNode() {
    Node* p = (Node*)malloc(sizeof(Node));
    p->key = 0;
    p->parent = NULL;
    p->lChild = NULL;
    p->rChild = NULL;
    return p;
}

int isExternal(Node* w) {
    return w->lChild == NULL && w->rChild == NULL;
}

int isInternal(Node* w) {
    return !isExternal(w);
}

Node* sibling(Node* w) {
    if (w == w->parent->lChild)
        return w->parent->rChild;
    else
        return w->parent->lChild;
}

Node* treeSearch(int k) {
    Node* w = root;

    while (isInternal(w)) {
        if (k == w->key)
            return w;
        else if (k < w->key)
            w = w->lChild;
        else
            w = w->rChild;
    }

    return w;
}

int findElement(int k) {
    Node* w = treeSearch(k);

    if (isExternal(w))
        return -1;

    return w->key;
}

void expandExternal(Node* w) {
    w->lChild = getNode();
    w->rChild = getNode();

    w->lChild->parent = w;
    w->rChild->parent = w;
}

void insertItem(int k) {
    Node* w = treeSearch(k);

    if (isInternal(w))
        return;

    w->key = k;
    expandExternal(w);
}

Node* inOrderSucc(Node* w) {
    w = w->rChild;

    if (isExternal(w))
        return NULL;

    while (isInternal(w->lChild))
        w = w->lChild;

    return w;
}

Node* reduceExternal(Node* z) {
    Node* w = z->parent;
    Node* zs = sibling(z);

    if (w == root) {
        root = zs;
        zs->parent = NULL;
    }
    else {
        Node* g = w->parent;
        zs->parent = g;

        if (w == g->lChild)
            g->lChild = zs;
        else
            g->rChild = zs;
    }

    free(z);
    free(w);

    return zs;
}

int removeElement(int k) {
    Node* w = treeSearch(k);

    if (isExternal(w))
        return -1;

    int e = w->key;
    Node* z = w->lChild;

    if (isInternal(z))
        z = w->rChild;

    if (isExternal(z)) {
        reduceExternal(z);
    }
    else {
        Node* y = inOrderSucc(w);
        w->key = y->key;
        z = y->lChild;
        reduceExternal(z);
    }

    return e;
}

void preOrder(Node* w) {
    if (isExternal(w))
        return;

    printf(" %d", w->key);
    preOrder(w->lChild);
    preOrder(w->rChild);
}

void freeTree(Node* w) {
    if (w == NULL)
        return;

    if (isInternal(w)) {
        freeTree(w->lChild);
        freeTree(w->rChild);
    }

    free(w);
}

int main() {
    char command;
    int k, result;

    root = getNode();

    while (scanf(" %c", &command) == 1) {
        if (command == 'i') {
            scanf("%d", &k);
            insertItem(k);
        }
        else if (command == 's') {
            scanf("%d", &k);
            result = findElement(k);

            if (result == -1)
                printf("X\n");
            else
                printf("%d\n", result);
        }
        else if (command == 'd') {
            scanf("%d", &k);
            result = removeElement(k);

            if (result == -1)
                printf("X\n");
            else
                printf("%d\n", result);
        }
        else if (command == 'p') {
            preOrder(root);
            printf("\n");
        }
        else if (command == 'q') {
            break;
        }
    }

    freeTree(root);
    return 0;
}