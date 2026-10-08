#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char elem;
    struct Node* prev;
    struct Node* next;
} Node;

void initList(Node* header, Node* trailer) {
    header->prev = NULL;
    header->next = trailer;

    trailer->prev = header;
    trailer->next = NULL;
}

void add(Node* list, int r, char e) {
    if (r <= 0) {
        printf("invalid position\n");
        return;
    }

    for (int i = 1; i < r; i++) {
        list = list->next;

        if (list->next == NULL) {
            printf("invalid position\n");
            return;
        }
    }

    Node* newnode = (Node*)malloc(sizeof(Node));

    newnode->elem = e;
    newnode->prev = list;
    newnode->next = list->next;

    list->next->prev = newnode;
    list->next = newnode;
}

void delete(Node* list, int r) {
    if (r <= 0) {
        printf("invalid position\n");
        return;
    }

    for (int i = 0; i < r; i++) {
        list = list->next;

        if (list->next == NULL) {
            printf("invalid position\n");
            return;
        }
    }

    Node* delnode = list;

    delnode->prev->next = delnode->next;
    delnode->next->prev = delnode->prev;

    free(delnode);
}

void get(Node* list, int r) {
    if (r <= 0) {
        printf("invalid position\n");
        return;
    }

    for (int i = 0; i < r; i++) {
        list = list->next;

        if (list->next == NULL) {
            printf("invalid position\n");
            return;
        }
    }

    printf("%c\n", list->elem);
}

void print(Node* list) {
    list = list->next;

    while (list->next != NULL) {
        printf("%c", list->elem);
        list = list->next;
    }

    printf("\n");
}

void freeList(Node* header) {
    Node* current = header;

    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* header = (Node*)malloc(sizeof(Node));
    Node* trailer = (Node*)malloc(sizeof(Node));

    int count, pos;
    char element, command;

    initList(header, trailer);

    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        scanf(" %c", &command);

        if (command == 'A') {
            scanf("%d %c", &pos, &element);
            add(header, pos, element);
        }

        else if (command == 'D') {
            scanf("%d", &pos);
            delete(header, pos);
        }

        else if (command == 'G') {
            scanf("%d", &pos);
            get(header, pos);
        }

        else if (command == 'P') {
            print(header);
        }
    }

    freeList(header);

    return 0;
}