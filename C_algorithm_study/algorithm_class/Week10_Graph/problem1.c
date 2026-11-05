#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct vertex {
    int data;
    struct vertex* next;
    struct edge* incidenceList;
} VERTEX;

typedef struct edge {
    int weight;
    VERTEX* start;
    VERTEX* end;
    struct edge* next;
} EDGE;

typedef struct graph {
    int n;
    VERTEX* vertices;
} GraphType;

void initGraph(GraphType* g);
VERTEX* createVertex(int data);
void insertVertex(GraphType* g, int data);
VERTEX* findVertex(GraphType* g, int data);
EDGE* createEdge(VERTEX* start, VERTEX* end, int weight);
void insertEdge(GraphType* g, int startData, int endData, int weight);
void printAdjacent(GraphType* g, int node);
void modifyEdge(GraphType* g, int a, int b, int w);

void initGraph(GraphType* g) {
    g->n = 0;
    g->vertices = NULL;
}

VERTEX* createVertex(int data) {
    VERTEX* newVertex = (VERTEX*)malloc(sizeof(VERTEX));
    newVertex->data = data;
    newVertex->next = NULL;
    newVertex->incidenceList = NULL;
    return newVertex;
}

void insertVertex(GraphType* g, int data) {
    VERTEX* newVertex = createVertex(data);
    VERTEX* temp = g->vertices;

    if (temp == NULL) {
        g->vertices = newVertex;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newVertex;
    }
    g->n++;
}

VERTEX* findVertex(GraphType* g, int data) {
    VERTEX* vertex = g->vertices;
    while (vertex != NULL) {
        if (vertex->data == data) return vertex;
        vertex = vertex->next;
    }
    return NULL;
}

EDGE* createEdge(VERTEX* start, VERTEX* end, int weight) {
    EDGE* newEdge = (EDGE*)malloc(sizeof(EDGE));
    newEdge->weight = weight;
    newEdge->start = start;
    newEdge->end = end;
    newEdge->next = NULL;
    return newEdge;
}

void insertEdge(GraphType* g, int startData, int endData, int weight) {
    VERTEX* start = findVertex(g, startData);
    VERTEX* end = findVertex(g, endData);

    if (start == NULL || end == NULL) {
        printf("-1\n");
        return;
    }

    EDGE* edge = start->incidenceList;
    while (edge != NULL) {
        if (edge->end == end) {
            edge->weight = weight;
            return;
        }
        edge = edge->next;
    }

    EDGE* newEdge = createEdge(start, end, weight);
    newEdge->next = start->incidenceList;
    start->incidenceList = newEdge;

    edge = end->incidenceList;
    while (edge != NULL) {
        if (edge->end == start) {
            edge->weight = weight;
            return;
        }
        edge = edge->next;
    }

    EDGE* reverseEdge = createEdge(end, start, weight);
    reverseEdge->next = end->incidenceList;
    end->incidenceList = reverseEdge;
}



void printAdjacent(GraphType* g, int node) {
    VERTEX* vertex = findVertex(g, node);
    if (vertex == NULL) {
        printf("-1\n");
        return;
    }

    int count = 0;
    EDGE* edge = vertex->incidenceList;

    while (edge != NULL) {
        count++;
        edge = edge->next;
    }

    int* adjData = (int*)malloc(sizeof(int) * count);
    int* weights = (int*)malloc(sizeof(int) * count);

    edge = vertex->incidenceList;
    for (int i = 0; i < count; i++) {
        adjData[i] = edge->end->data;
        weights[i] = edge->weight;
        edge = edge->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
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

    for (int i = 0; i < count; i++) {
        printf(" %d %d", adjData[i], weights[i]);
    }
    printf("\n");

    free(adjData);
    free(weights);
}


void modifyEdge(GraphType* g, int a, int b, int w) {
    VERTEX* start = findVertex(g, a);
    VERTEX* end = findVertex(g, b);

    if (start == NULL || end == NULL) {
        printf("-1\n");
        return;
    }

    EDGE* edge = start->incidenceList;
    EDGE* prevEdge = NULL;

    if (w == 0) {
        while (edge != NULL && edge->end != end) {
            prevEdge = edge;
            edge = edge->next;
        }
        if (edge != NULL) {
            if (prevEdge == NULL) {
                start->incidenceList = edge->next;
            }
            else {
                prevEdge->next = edge->next;
            }
            free(edge);
        }

        edge = end->incidenceList;
        prevEdge = NULL;
        while (edge != NULL && edge->end != start) {
            prevEdge = edge;
            edge = edge->next;
        }
        if (edge != NULL) {
            if (prevEdge == NULL) {
                end->incidenceList = edge->next;
            }
            else {
                prevEdge->next = edge->next;
            }
            free(edge);
        }
        return;
    }

    int edgeUpdated = 0;
    edge = start->incidenceList;
    while (edge != NULL) {
        if (edge->end == end) {
            edge->weight = w;
            edgeUpdated = 1;
            break;
        }
        edge = edge->next;
    }

    edge = end->incidenceList;
    while (edge != NULL) {
        if (edge->end == start) {
            edge->weight = w;
            edgeUpdated = 1;
            break;
        }
        edge = edge->next;
    }

    if (!edgeUpdated) {
        insertEdge(g, a, b, w);
    }
}


int main() {
    GraphType g;
    initGraph(&g);

    insertVertex(&g, 1);
    insertVertex(&g, 2);
    insertVertex(&g, 3);
    insertVertex(&g, 4);
    insertVertex(&g, 5);
    insertVertex(&g, 6);

    insertEdge(&g, 1, 2, 1);
    insertEdge(&g, 1, 3, 1);
    insertEdge(&g, 1, 4, 1);
    insertEdge(&g, 1, 6, 2);

    insertEdge(&g, 2, 3, 1);;

    insertEdge(&g, 3, 5, 4);

    insertEdge(&g, 5, 5, 4);
    insertEdge(&g, 5, 6, 3);


    char command;
    int a, b, w;

    while (1) {
        scanf(" %c", &command);

        if (command == 'a') {
            scanf("%d", &a);
            printAdjacent(&g, a);
        }
        else if (command == 'm') {
            scanf("%d %d %d", &a, &b, &w);
            modifyEdge(&g, a, b, w);
        }
        else if (command == 'q') {
            break;
        }
    }

    return 0;
}