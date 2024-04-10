#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Vertex{
    int data;
    double x, y;
} Vertex;

typedef struct _Graph {
    double** edges;
} Graph;

Vertex *createVertex(int data, double x, double y) {
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    vertex->data = data;
    vertex->x = x;
    vertex->y = y;
    return vertex;
}

void addEdge(Graph *graph, Vertex *s, Vertex *d, double weight) {
    graph->edges[s->data][d->data] = weight;
    graph->edges[d->data][s->data] = weight;
}

Graph *createGraph(int n) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->edges = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++) {
        graph->edges[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            graph->edges[i][j] = 0.0;
        }
    }

    return graph;
}

// ref: https://www.programiz.com/dsa/dijkstra-algorithm
void dijkstra(Graph *graph, int start, int end, int n) {
    double* distance = (double*)malloc(n * sizeof(double));
    int* visited = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[start] = 0.0;

    for (int count = 0; count < n - 1; count++) {
        double minDistance = INT_MAX;
        int nextNode;
        
        for (int v = 0; v < n; v++) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                nextNode = v;
            }
        }

        visited[nextNode] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph->edges[nextNode][v] &&
                distance[nextNode] != INT_MAX &&
                distance[nextNode] + graph->edges[nextNode][v] < distance[v]) {
                distance[v] = distance[nextNode] + graph->edges[nextNode][v];
            }
        }
    }

    printf("%.2f", distance[end]);

    free(distance);
    free(visited);
}



double weight(Vertex *s, Vertex *d) {
    return sqrtf(pow((d->x - s->x), 2.0) + pow((d->y - s->y),2.0));
}

int main() {
    int n;
    scanf("%d", &n);

    Vertex *vertex[n];
    int edges[n][n];

    for (int i = 0; i < n; i++) {
        double x, y;
        scanf("%lf %lf", &x, &y);

        int j = 0;
        while (getchar() != '\n') {
            scanf("%d", &edges[i][j++]);
            if (j < n) edges[i][j] = 0;
        }

        vertex[i] = createVertex(i, x, y);
    }

    Graph *graph = createGraph(n);

    for (int i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {
        for (int j = 0; j < sizeof(edges[i]) / sizeof(edges[i][0]); j++) {
            if (edges[i][j] == 0) break;
            addEdge(graph, vertex[i], vertex[edges[i][j]-1], weight(vertex[i], vertex[j]));
        }
    }

    int start, end;
    scanf("%d %d", &start, &end);

    dijkstra(graph, start-1, end-1, n);
    
    return 0;
}