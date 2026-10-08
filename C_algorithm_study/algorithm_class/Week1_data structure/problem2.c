#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int elem;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* makeTree() {
    int x, y, z;

    scanf("%d %d %d", &x, &y, &z);

    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    node->elem = x;
    node->left = NULL;
    node->right = NULL;

    if (y != 0)
        node->left = makeTree();

    if (z != 0)
        node->right = makeTree();

    return node;
}

void search(TreeNode* root, char* path) {
    TreeNode* p = root;

    printf(" %d", p->elem);

    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] == 'L')
            p = p->left;
        else if (path[i] == 'R')
            p = p->right;

        printf(" %d", p->elem);
    }

    printf("\n");
}

void freeTree(TreeNode* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

int main() {
    int n, s;
    char path[101];

    scanf("%d", &n);

    TreeNode* root = makeTree();

    scanf("%d", &s);

    for (int i = 0; i < s; i++) {
        scanf("%s", path);
        search(root, path);
    }

    freeTree(root);

    return 0;
}