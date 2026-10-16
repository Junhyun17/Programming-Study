#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Node {
    int key;
    int height;
    struct Node* parent;
    struct Node* lChild;
    struct Node* rChild;
} Node;

Node* root;

Node* getNode();
int isExternal(Node* w);
int isInternal(Node* w);
Node* treeSearch(int k);
int findElement(int k, int* result);
void expandExternal(Node* w);
void insertItem(int k);
int updateHeight(Node* w);
int isBalanced(Node* w);
Node* rotateLeft(Node* z);
Node* rotateRight(Node* z);
Node* restructure(Node* x, Node* y, Node* z);
void searchAndFixAfterInsertion(Node* w);
void preOrder(Node* w);
void freeTree(Node* w);

Node* getNode() {
    Node* p = (Node*)malloc(sizeof(Node));

    if (p == NULL) {
        exit(1);
    }

    p->key = 0;
    p->height = 0;
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

Node* treeSearch(int k) {
    Node* w = root;

    while (isInternal(w)) {
        if (k == w->key) {
            return w;
        }
        else if (k < w->key) {
            w = w->lChild;
        }
        else {
            w = w->rChild;
        }
    }

    return w;
}

int findElement(int k, int* result) {
    Node* w = treeSearch(k);

    if (isExternal(w)) {
        return 0;
    }

    *result = w->key;
    return 1;
}

void expandExternal(Node* w) {
    w->lChild = getNode();
    w->rChild = getNode();

    w->lChild->parent = w;
    w->rChild->parent = w;

    w->height = 1;
}

int updateHeight(Node* w) {
    if (isExternal(w)) {
        return 0;
    }

    int oldHeight = w->height;
    int leftHeight = w->lChild->height;
    int rightHeight = w->rChild->height;

    if (leftHeight > rightHeight) {
        w->height = leftHeight + 1;
    }
    else {
        w->height = rightHeight + 1;
    }

    return oldHeight != w->height;
}

int isBalanced(Node* w) {
    if (isExternal(w)) {
        return 1;
    }

    int leftHeight = w->lChild->height;
    int rightHeight = w->rChild->height;

    int diff = leftHeight - rightHeight;

    return diff >= -1 && diff <= 1;
}

Node* rotateLeft(Node* z) {
    Node* y = z->rChild;
    Node* b = y->lChild;
    Node* g = z->parent;

    y->parent = g;

    if (g == NULL) {
        root = y;
    }
    else if (g->lChild == z) {
        g->lChild = y;
    }
    else {
        g->rChild = y;
    }

    y->lChild = z;
    z->parent = y;

    z->rChild = b;
    b->parent = z;

    updateHeight(z);
    updateHeight(y);

    return y;
}

Node* rotateRight(Node* z) {
    Node* y = z->lChild;
    Node* b = y->rChild;
    Node* g = z->parent;

    y->parent = g;

    if (g == NULL) {
        root = y;
    }
    else if (g->lChild == z) {
        g->lChild = y;
    }
    else {
        g->rChild = y;
    }

    y->rChild = z;
    z->parent = y;

    z->lChild = b;
    b->parent = z;

    updateHeight(z);
    updateHeight(y);

    return y;
}

Node* restructure(Node* x, Node* y, Node* z) {
    if (y == z->lChild) {
        if (x == y->lChild) {
            return rotateRight(z);
        }
        else {
            rotateLeft(y);
            return rotateRight(z);
        }
    }
    else {
        if (x == y->rChild) {
            return rotateLeft(z);
        }
        else {
            rotateRight(y);
            return rotateLeft(z);
        }
    }
}

void searchAndFixAfterInsertion(Node* w) {
    Node* z = w->parent;

    while (z != NULL) {
        updateHeight(z);

        if (!isBalanced(z)) {
            Node* y;
            Node* x;

            if (z->lChild->height > z->rChild->height) {
                y = z->lChild;
            }
            else {
                y = z->rChild;
            }

            if (y->lChild->height > y->rChild->height) {
                x = y->lChild;
            }
            else if (y->lChild->height < y->rChild->height) {
                x = y->rChild;
            }
            else if (y == z->lChild) {
                x = y->lChild;
            }
            else {
                x = y->rChild;
            }

            restructure(x, y, z);
            return;
        }

        z = z->parent;
    }
}

void insertItem(int k) {
    Node* w = treeSearch(k);

    if (isInternal(w)) {
        return;
    }

    w->key = k;
    expandExternal(w);
    searchAndFixAfterInsertion(w);
}

void preOrder(Node* w) {
    if (isExternal(w)) {
        return;
    }

    printf(" %d", w->key);

    preOrder(w->lChild);
    preOrder(w->rChild);
}

void freeTree(Node* w) {
    if (w == NULL) {
        return;
    }

    if (isInternal(w)) {
        freeTree(w->lChild);
        freeTree(w->rChild);
    }

    free(w);
}

int main() {
    char cmd;
    int k, result;

    root = getNode();

    while (scanf(" %c", &cmd) == 1) {
        if (cmd == 'i') {
            scanf("%d", &k);
            insertItem(k);
        }
        else if (cmd == 's') {
            scanf("%d", &k);

            if (findElement(k, &result)) {
                printf("%d\n", result);
            }
            else {
                printf("X\n");
            }
        }
        else if (cmd == 'p') {
            preOrder(root);
            printf("\n");
        }
        else if (cmd == 'q') {
            break;
        }
    }

    freeTree(root);

    return 0;
}