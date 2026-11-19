#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define MAX 100

typedef struct INCIDENT {
    int idx;
    struct INCIDENT* next;
} INCIDENT;

typedef struct EDGE {
    int src;
    int dest;
} EDGE;

typedef struct VERTEX {
    char name;
    INCIDENT* in;
    INCIDENT* out;
    int inDegree;
} VERTEX;

typedef struct GRAPH {
    VERTEX* vertex;
    EDGE* edge;
}GRAPH;

GRAPH graph;
int n, m;
int topoOrder[MAX], queue[MAX];
int front = 0, rear = 0;

int isEmpty();
void enqueue(int v);
int dequeue();
void initializeGraph();
void addFirst(INCIDENT** H, int i);
int index(char vName);
void insertVertex(char vName, int i);
void insertDirectedEdge(char uName, char wName, int i);
void buildGraph();
void topologicalSort();

int isEmpty() {
    return front == rear;
}

void enqueue(int v) {
    queue[rear] = v;
    rear = (rear + 1) % 100;
}

int dequeue() {
    int v = queue[front];
    front = (front + 1) % 100;
    return v;
}

void initializeGraph() {
    graph.vertex = (VERTEX*)malloc(MAX * sizeof(VERTEX));
    graph.edge = (EDGE*)malloc(1000 * sizeof(EDGE));
}

void addFirst(INCIDENT** H, int i) {
    INCIDENT* node = (INCIDENT*)malloc(sizeof(INCIDENT));
    node->idx = i;
    node->next = *H;
    *H = node;
}

int index(char vName) {
    for (int i = 0; i < n; i++) {
        if (graph.vertex[i].name == vName) {
            return i;
        }
    }
    return -1;
}

void insertVertex(char vName, int i) {
    graph.vertex[i].name = vName;
    graph.vertex[i].out = NULL;
    graph.vertex[i].in = NULL;
    graph.vertex[i].inDegree = 0;
}

void insertDirectedEdge(char uName, char wName, int i) {
    int u = index(uName);
    int w = index(wName);

    if (u == -1 || w == -1) {
        return;
    }

    graph.edge[i].src = u;
    graph.edge[i].dest = w;

    addFirst(&(graph.vertex[u].out), i);
    addFirst(&(graph.vertex[w].in), i);

    graph.vertex[w].inDegree++;
}

void buildGraph() {
    initializeGraph();

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char vName;
        scanf(" %c", &vName);
        insertVertex(vName, i);
    }

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        char uName, wName;
        scanf(" %c %c", &uName, &wName);
        insertDirectedEdge(uName, wName, i);
    }
}

void topologicalSort() {
    int in[MAX];
    int t = 1;

    for (int i = 0; i < n; i++) {
        in[i] = graph.vertex[i].inDegree;
        if (in[i] == 0) {
            enqueue(i);
        }
    }

    while (!isEmpty()) {
        int u = dequeue();
        topoOrder[t++] = u;

        INCIDENT* edge = graph.vertex[u].out;
        while (edge != NULL) {
            int w = graph.edge[edge->idx].dest;
            in[w]--;

            if (in[w] == 0) {
                enqueue(w);
            }

            edge = edge->next;
        }
    }

    if (t <= n) {
        topoOrder[0] = 0;
    }
    else {
        topoOrder[0] = 1;
    }
}

int main() {
    buildGraph();
    topologicalSort();

    if (topoOrder[0] == 0) {
        printf("0\n");
    }
    else {
        for (int i = 1; i <= n; i++) {
            printf("%c ", graph.vertex[topoOrder[i]].name);
        }
        printf("\n");
    }

    return 0;
}
