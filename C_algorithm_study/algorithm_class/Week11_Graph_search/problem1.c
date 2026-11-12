#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct vertex {
    int data;
    struct vertex* next;
    struct edge* incidenceList;
} VERTEX;

typedef struct edge {
    VERTEX* start;
    VERTEX* end;
    struct edge* next;
} EDGE;

typedef struct graph {
    int n;
    VERTEX* vertices;
} GraphType;

VERTEX* findVertex(GraphType* graph, int data);
VERTEX* addVertex(GraphType* graph, int data);
void addEdge(GraphType* graph, int start, int end);
void dfs(VERTEX* v, int* visited);

VERTEX* findVertex(GraphType* graph, int data) {
    VERTEX* temp = graph->vertices;
    while (temp) {
        if (temp->data == data) return temp;
        temp = temp->next;
    }
    return NULL;
}

VERTEX* addVertex(GraphType* graph, int data) {
    VERTEX* newVertex = (VERTEX*)malloc(sizeof(VERTEX));
    newVertex->data = data;
    newVertex->next = graph->vertices;
    newVertex->incidenceList = NULL;
    graph->vertices = newVertex;
    return newVertex;
}

void addEdge(GraphType* graph, int start, int end) {
    VERTEX* startVertex = findVertex(graph, start);
    VERTEX* endVertex = findVertex(graph, end);
    if (!startVertex) startVertex = addVertex(graph, start);
    if (!endVertex) endVertex = addVertex(graph, end);

    EDGE* newEdge = (EDGE*)malloc(sizeof(EDGE));
    newEdge->start = startVertex;
    newEdge->end = endVertex;

    if (!startVertex->incidenceList || endVertex->data < startVertex->incidenceList->end->data) {
        newEdge->next = startVertex->incidenceList;
        startVertex->incidenceList = newEdge;
    }
    else {
        EDGE* current = startVertex->incidenceList;
        while (current->next && current->next->end->data < endVertex->data) {
            current = current->next;
        }
        newEdge->next = current->next;
        current->next = newEdge;
    }

    EDGE* reverseEdge = (EDGE*)malloc(sizeof(EDGE));
    reverseEdge->start = endVertex;
    reverseEdge->end = startVertex;

    if (!endVertex->incidenceList || startVertex->data < endVertex->incidenceList->end->data) {
        reverseEdge->next = endVertex->incidenceList;
        endVertex->incidenceList = reverseEdge;
    }
    else {
        EDGE* current = endVertex->incidenceList;
        while (current->next && current->next->end->data < startVertex->data) {
            current = current->next;
        }
        reverseEdge->next = current->next;
        current->next = reverseEdge;
    }
}

void dfs(VERTEX* v, int* visited) {
    printf("%d\n", v->data);
    visited[v->data] = 1;

    EDGE* edge = v->incidenceList;
    while (edge) {
        VERTEX* adjacent = edge->end;
        if (!visited[adjacent->data]) {
            dfs(adjacent, visited);
        }
        edge = edge->next;
    }
}

int main() {
    GraphType* graph = (GraphType*)malloc(sizeof(GraphType));
    graph->n = 0;
    graph->vertices = NULL;

    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int visited[101] = { 0 };
    VERTEX* startVertex = findVertex(graph, s);
    if (startVertex) {
        dfs(startVertex, visited);
    }

    return 0;
}
