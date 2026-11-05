#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define MAX_VERTICES 100

typedef struct graph {
    int n;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void initGraph(GraphType* g, int n);
void insertEdge(GraphType* g, int start, int end, int weight);
void modifyEdge(GraphType* g, int a, int b, int w);
void printAdjacent(GraphType* g, int node);

void initGraph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

void insertEdge(GraphType* g, int start, int end, int weight) {
    g->adjMatrix[start][end] = weight;
    g->adjMatrix[end][start] = weight;
}

void modifyEdge(GraphType* g, int a, int b, int w) {
    if (a < 1 || a >= g->n || b < 1 || b >= g->n) {
        printf("-1\n");
        return;
    }
    if (w == 0) {
        g->adjMatrix[a][b] = 0;
        g->adjMatrix[b][a] = 0;
    }
    else {
        g->adjMatrix[a][b] = w;
        g->adjMatrix[b][a] = w;
    }
}

void printAdjacent(GraphType* g, int node) {
    if (node < 1 || node >= g->n) {
        printf("-1\n");
        return;
    }

    int adjData[MAX_VERTICES];
    int weights[MAX_VERTICES];
    int adjCount = 0;

    for (int i = 1; i < g->n; i++) {
        if (g->adjMatrix[node][i] != 0) {
            adjData[adjCount] = i;
            weights[adjCount] = g->adjMatrix[node][i];
            adjCount++;
        }
    }

    for (int i = 0; i < adjCount - 1; i++) {
        for (int j = 0; j < adjCount - i - 1; j++) {
            if (adjData[j] > adjData[j + 1]) {
                int tempData = adjData[j];
                int tempWeight = weights[j];
                adjData[j] = adjData[j + 1];
                weights[j] = weights[j + 1];
                adjData[j + 1] = tempData;
                weights[j + 1] = tempWeight;
            }
        }
    }

    for (int i = 0; i < adjCount; i++) {
        printf(" %d %d", adjData[i], weights[i]);
    }
    if (adjCount > 0) {
        printf("\n");
    }
}

int main() {
    int n = 7;
    GraphType g;
    initGraph(&g, n);

    insertEdge(&g, 1, 2, 1);
    insertEdge(&g, 1, 3, 1);
    insertEdge(&g, 1, 4, 1);
    insertEdge(&g, 1, 6, 2);

    insertEdge(&g, 2, 3, 1);
    insertEdge(&g, 3, 5, 4);
    insertEdge(&g, 5, 5, 4);
    insertEdge(&g, 5, 6, 3);

    char command;
    int a, b, w;

    while (1) {
        scanf(" %c", &command);

        if (command == 'a') {
            if (scanf("%d", &a) == 1) {
                printAdjacent(&g, a);
            }
        }
        else if (command == 'm') {
            if (scanf("%d %d %d", &a, &b, &w) == 3) {
                modifyEdge(&g, a, b, w);
            }
        }
        else if (command == 'q') {
            break;
        }
    }

    return 0;
}