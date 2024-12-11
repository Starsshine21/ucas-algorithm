#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 6 // 节点数

// 辅助函数：找到最小值
int min(int a, int b) {
    return (a < b) ? a : b;
}

// 广度优先搜索（BFS）来查找增广路径
bool bfs(int rGraph[V][V], int s, int t, int parent[V]) {
    bool visited[V];
    int i;
    for (i = 0; i < V; i++) {
        visited[i] = false;
    }

    visited[s] = true;
    parent[s] = -1;

    int queue[V];
    int front = 0, rear = 0;
    queue[rear++] = s;

    while (front != rear) {
        int u = queue[front++];
        int v;
		for (v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

// Ford-Fulkerson算法计算最大流
int fordFulkerson(int graph[V][V], int s, int t) {
    int rGraph[V][V];
    int u,v;
    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[V];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int graph[V][V] = {
        {0, 8, 12, 0, 0, 0},
        {0, 0, 4, 6, 10, 0},
        {0, 2, 0, 10, 2, 0},
        {0, 0, 0, 0, 0, 8},
        {0, 0, 0, 2, 0, 10},
        {0, 0, 0, 0, 0, 0}
    };

    int source = 0, sink = 5;
    int max_flow = fordFulkerson(graph, source, sink);

    printf("最大流是：%d\n", max_flow);

    return 0;
}

