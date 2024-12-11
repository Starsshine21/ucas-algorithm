#include<bits/stdc++.h>
using namespace std;

#define INF 10000000000
#define MAX_NODES 1000001

struct Edge {
    long long next, to;
    long long capacity;
} edges[MAX_NODES];

long long head[MAX_NODES], totalEdges;
long long nodes, edgesCount, source, sink;
long long levels[MAX_NODES], currentEdges[MAX_NODES];

void addEdge(long long from, long long to, long long capacity) {
    edges[++totalEdges].next = head[from];
    edges[totalEdges].to = to;
    edges[totalEdges].capacity = capacity;
    head[from] = totalEdges;
}
bool bfs() {
    queue<long long> q;
    fill(&levels[0], &levels[0] + MAX_NODES, INF);
    q.push(source);
    levels[source] = 0;
    currentEdges[source] = head[source];

    while (!q.empty()) {
        long long currentNode = q.front();
        q.pop();
        for (long long i = head[currentNode]; i; i = edges[i].next) {
            long long nextNode = edges[i].to;
            long long capacity = edges[i].capacity;
            if (capacity != 0 && levels[nextNode] == INF) {
                q.push(nextNode);
                currentEdges[nextNode] = head[nextNode];
                levels[nextNode] = levels[currentNode] + 1;
                if (nextNode == sink) {
                    return true;
                }
            }
        }
    }
    return false;
}


long long dfs(long long currentNode, long long flow) {
    if (currentNode == sink) {
        return flow;
    }
    long long remainingFlow = flow;
    for (long long i = currentEdges[currentNode]; i && remainingFlow; i = edges[i].next) {
        currentEdges[currentNode] = i;
        long long nextNode = edges[i].to;
        if (edges[i].capacity != 0 && (levels[nextNode] == levels[currentNode] + 1)) {
            long long  currentFlow = dfs(nextNode, min(remainingFlow, edges[i].capacity));
            if (currentFlow == 0) {
                levels[nextNode] = INF;
            }
            edges[i].capacity -= currentFlow;
            edges[i ^ 1].capacity += currentFlow;
            remainingFlow -= currentFlow;
        }
    }
    return flow - remainingFlow;
}

int  main() {
    scanf("%lld %lld %lld %lld", &nodes, &edgesCount, &source, &sink);
    totalEdges = 1;

    for (long long i = 0; i < edgesCount; i++) {
        long long from, to;
        long long capacity;
        scanf("%lld %lld %lld", &from, &to, &capacity);
        addEdge(from, to, capacity);
        addEdge(to, from, 0);
    }

    long long maxFlow = 0;
    while (bfs()) {
        maxFlow += dfs(source, INF);
    }

    printf("%lld", maxFlow);
    return 0;
}

