#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 10000
#define INF INT_MAX

struct Edge {
    int to;
    int weight;
    struct Edge* next;
};

struct DijkstraAlgorithm {
    struct Edge** adjacencyList;
    int* distances;
    bool* visited;
    struct PriorityQueue {
        int* heap;
        int size;
    } minHeap;
};

struct DijkstraAlgorithm* createDijkstraAlgorithm(int n) {
    struct DijkstraAlgorithm* dijkstra = (struct DijkstraAlgorithm*)malloc(sizeof(struct DijkstraAlgorithm));
    dijkstra->adjacencyList = (struct Edge**)malloc(n * sizeof(struct Edge*));
    dijkstra->distances = (int*)malloc(n * sizeof(int));
    dijkstra->visited = (bool*)malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        dijkstra->adjacencyList[i] = NULL;
        dijkstra->distances[i] = INF;
        dijkstra->visited[i] = false;
    }

    dijkstra->minHeap.heap = (int*)malloc(n * sizeof(int));
    dijkstra->minHeap.size = 0;

    return dijkstra;
}

void addEdge(struct DijkstraAlgorithm* dijkstra, int u, int v, int w) {
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->to = v;
    newEdge->weight = w;
    newEdge->next = dijkstra->adjacencyList[u];
    dijkstra->adjacencyList[u] = newEdge;
}

void push(struct DijkstraAlgorithm* dijkstra, int val) {
    dijkstra->minHeap.heap[dijkstra->minHeap.size] = val;
    int index = dijkstra->minHeap.size;
    dijkstra->minHeap.size++;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (dijkstra->distances[dijkstra->minHeap.heap[index]] < dijkstra->distances[dijkstra->minHeap.heap[parent]]) {
            int temp = dijkstra->minHeap.heap[index];
            dijkstra->minHeap.heap[index] = dijkstra->minHeap.heap[parent];
            dijkstra->minHeap.heap[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
}

int pop(struct DijkstraAlgorithm* dijkstra) {
    int top = dijkstra->minHeap.heap[0];
    dijkstra->minHeap.heap[0] = dijkstra->minHeap.heap[dijkstra->minHeap.size - 1];
    dijkstra->minHeap.size--;

    int index = 0;
    while (2 * index + 1 < dijkstra->minHeap.size) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallerChild = leftChild;

        if (rightChild < dijkstra->minHeap.size && dijkstra->distances[dijkstra->minHeap.heap[rightChild]] < dijkstra->distances[dijkstra->minHeap.heap[leftChild]]) {
            smallerChild = rightChild;
        }

        if (dijkstra->distances[dijkstra->minHeap.heap[index]] > dijkstra->distances[dijkstra->minHeap.heap[smallerChild]]) {
            int temp = dijkstra->minHeap.heap[index];
            dijkstra->minHeap.heap[index] = dijkstra->minHeap.heap[smallerChild];
            dijkstra->minHeap.heap[smallerChild] = temp;
            index = smallerChild;
        } else {
            break;
        }
    }

    return top;
}

int shortestPath(struct DijkstraAlgorithm* dijkstra, int start, int end) {
    dijkstra->distances[start] = 0;
    push(dijkstra, start);

    while (dijkstra->minHeap.size > 0) {
        int currentVertex = pop(dijkstra);

        if (dijkstra->visited[currentVertex]) continue;
        dijkstra->visited[currentVertex] = true;

        struct Edge* currentEdge = dijkstra->adjacencyList[currentVertex];
        while (currentEdge != NULL) {
            int newDist = dijkstra->distances[currentVertex] + currentEdge->weight;
            if (newDist < dijkstra->distances[currentEdge->to]) {
                dijkstra->distances[currentEdge->to] = newDist;
                push(dijkstra, currentEdge->to);
            }
            currentEdge = currentEdge->next;
        }
    }

    return dijkstra->distances[end] == INF ? -1 : dijkstra->distances[end];
}

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    s--; t--;

    struct DijkstraAlgorithm* dijkstra = createDijkstraAlgorithm(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;
        addEdge(dijkstra, u, v, w);
    }

    printf("%d", shortestPath(dijkstra, s, t));

    return 0;
}

