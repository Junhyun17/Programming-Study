#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define MAX_VERTICES 101

typedef struct graph {
    int n;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void initGraph(GraphType* graph, int n);
void addEdge(GraphType* graph, int u, int v);
void bfs(GraphType* graph, int start);

void initGraph(GraphType* graph, int n) {
    graph->n = n;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(GraphType* graph, int u, int v) {
    graph->adjMatrix[u][v] = 1;
    graph->adjMatrix[v][u] = 1;
}

void bfs(GraphType* graph, int start) {
    int visited[MAX_VERTICES] = { 0 };
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int here = queue[front++];
        printf("%d\n", here);

        for (int i = 1; i <= graph->n; i++) {
            if (graph->adjMatrix[here][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    GraphType graph;
    int n, m, s;

    scanf("%d %d %d", &n, &m, &s);
    initGraph(&graph, n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&graph, u, v);
    }

    bfs(&graph, s);

    return 0;
}
