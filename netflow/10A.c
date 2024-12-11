#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// 定义图的结构体
struct Edge {
    int to, cap, rev;
};

struct Graph {
    int V, *level;
    struct Edge *edges[];
};

// 创建图的函数
struct Graph *createGraph(int V, int E) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph) + sizeof(struct Edge *) * V);
    graph->V = V;
    graph->level = (int *)malloc(sizeof(int) * V);
    for (int i = 0; i < V; i++) {
        graph->edges[i] = NULL;
    }
    return graph;
}

// 添加边的函数
void addEdge(struct Graph *graph, int from, int to, int cap) {
    struct Edge *e1 = (struct Edge *)malloc(sizeof(struct Edge));
    struct Edge *e2 = (struct Edge *)malloc(sizeof(struct Edge));
    e1->to = to;
    e1->cap = cap;
    e1->rev = graph->edges[to] ? graph->edges[to]->rev + 1 : 0;
    
    e2->to = from;
    e2->cap = 0;
    e2->rev = e1->rev + 1;  // 逆向边的编号紧随正向边之后


    // 添加边到图中
    e1->rev = e2->rev;
    e2->rev = e1->rev;
    graph->edges[from] = e1;
    graph->edges[to] = e2;
}

// BFS找到层次图
bool bfs(struct Graph *graph, int source, int sink) {
    memset(graph->level, -1, sizeof(int) * graph->V);
    graph->level[source] = 0;

    int queue[graph->V];
    int front = 0, rear = 0;
    queue[rear++] = source;

    while (front < rear) {
        int u = queue[front++];
        struct Edge *e = graph->edges[u];

        while (e != NULL) {
            int v = e->to;

            if (graph->level[v] < 0 && e->cap > 0) {
                graph->level[v] = graph->level[u] + 1;
                queue[rear++] = v;
            }

            e = graph->edges[v];
        }
    }

    return graph->level[sink] >= 0;
}

// DFS找增广路径
int dfs(struct Graph *graph, int u, int minCapacity, int sink) {
    if (u == sink)
        return minCapacity;

    struct Edge *e = graph->edges[u];
    while (e != NULL) {
        int v = e->to;

        if (graph->level[v] == graph->level[u] + 1 && e->cap > 0) {
            int flow = dfs(graph, v, MIN(minCapacity, e->cap), sink);
            if (flow > 0) {
                e->cap -= flow;
                graph->edges[v]->cap += flow;
                return flow;
            }
        }

        e = graph->edges[v];
    }

    return 0;
}

// Dinic算法求最大流
int dinic(struct Graph *graph, int source, int sink) {
    int maxFlow = 0;

    while (bfs(graph, source, sink)) {
        int flow;
        while ((flow = dfs(graph, source, INT_MAX, sink)) > 0) {
            maxFlow += flow;
        }
    }

    return maxFlow;
}

int main() {
    int vertices, edges, source, sink;
    scanf("%d %d %d %d", &vertices, &edges, &source, &sink);
    struct Graph *graph = createGraph(vertices, edges);
    int from, to, capa;
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &from, &to, &capa);
        addEdge(graph, from, to, capa);
    }

    int maxFlow = dinic(graph, source, sink);
    printf("%d", maxFlow);

    // 释放图的内存
    for (int i = 0; i < vertices; i++) {
        struct Edge *e = graph->edges[i];
        while (e != NULL) {
            struct Edge *temp = e;
            e = e->rev % 2 == 0 ? graph->edges[e->rev - 1] : NULL;
            free(temp);
        }
    }

    free(graph->level);
    free(graph);

    return 0;
}

