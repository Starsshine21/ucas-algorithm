#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define maxn 250 // count of Node
#define INF 0x3f3f3f3f

// Define the structure to store information about each edge
struct Edge {
  int from, to, cap, flow;
};

// Define the structure for the Dinic algorithm, including functions for initialization and adding edges
struct Dinic {
  int n, m, s, t;
  struct Edge *edges;
  int *G[maxn];
  int *d, *cur, *vis;

};

void init(struct Dinic *dinic, int n) {
  dinic->n = n;
  dinic->m = 0;
  dinic->edges = (struct Edge *)malloc(sizeof(struct Edge) * 2 * maxn);
  for (int i = 0; i < n; i++) dinic->G[i] = NULL;
  dinic->d = (int *)malloc(sizeof(int) * maxn);
  dinic->cur = (int *)malloc(sizeof(int) * maxn);
  dinic->vis = (int *)malloc(sizeof(int) * maxn);
}

void AddEdge(struct Dinic *dinic, int from, int to, int cap) {
  dinic->edges[dinic->m] = (struct Edge){from, to, cap, 0};
  dinic->edges[dinic->m + 1] = (struct Edge){to, from, 0, 0};
  dinic->m += 2;

  // Ensure enough memory for G
  dinic->G[from] = (int *)realloc(dinic->G[from], sizeof(int) * dinic->m);
  dinic->G[to] = (int *)realloc(dinic->G[to], sizeof(int) * dinic->m);

  dinic->G[from][dinic->m - 2] = dinic->m - 2;
  dinic->G[to][dinic->m - 1] = dinic->m - 1;
}



int BFS(struct Dinic *dinic) {
  memset(dinic->vis, 0, sizeof(int) * maxn);
  int queue[maxn];
  int front = 0, rear = 0;
  queue[rear++] = dinic->s;
  dinic->d[dinic->s] = 0;
  dinic->vis[dinic->s] = 1;

  while (front < rear) {
    int x = queue[front++];
    for (int i = 0; i < dinic->m; i++) {
      struct Edge e = dinic->edges[dinic->G[x][i]];
      if (!dinic->vis[e.to] && e.cap > e.flow) {
        dinic->vis[e.to] = 1;
        dinic->d[e.to] = dinic->d[x] + 1;
        queue[rear++] = e.to;
      }
    }
  }
  return dinic->vis[dinic->t];
}


// Function to perform depth-first search
int DFS(struct Dinic *dinic, int x, int a) {
  if (x == dinic->t || a == 0) return a;
  int flow = 0, f;
  for (int *i = &dinic->cur[x]; *i < dinic->m; (*i)++) {
    struct Edge *e = &dinic->edges[dinic->G[x][*i]];
    if (dinic->d[x] + 1 == dinic->d[e->to] && (f = DFS(dinic, e->to, a < e->cap - e->flow ? a : e->cap - e->flow)) > 0) {
      e->flow += f;
      dinic->edges[dinic->G[x][*i] ^ 1].flow -= f;
      flow += f;
      a -= f;
      if (a == 0) break;
    }
  }
  return flow;
}

// Function to find the maximum flow
int Maxflow(struct Dinic *dinic, int s, int t) {
  dinic->s = s;
  dinic->t = t;
  int flow = 0;
  while (BFS(dinic)) {
    memset(dinic->cur, 0, sizeof(int) * maxn);
    flow += DFS(dinic, s, INF);
  }
  return flow;
}

int main() {
  // Example usage:
  struct Dinic dinic;
  int n = 6; // Number of nodes
  init(&dinic, n);

  AddEdge(&dinic, 0, 1, 16);
  AddEdge(&dinic, 0, 2, 13);
  AddEdge(&dinic, 1, 2, 10);
  AddEdge(&dinic, 1, 3, 12);
  AddEdge(&dinic, 2, 1, 4);
  AddEdge(&dinic, 2, 4, 14);
  AddEdge(&dinic, 3, 2, 9);
  AddEdge(&dinic, 3, 5, 20);
  AddEdge(&dinic, 4, 3, 7);
  AddEdge(&dinic, 4, 5, 4);

  int maxFlow = Maxflow(&dinic, 0, 5);
  printf("Max Flow: %d\n", maxFlow);

  free(dinic.edges);
  free(dinic.d);
  free(dinic.cur);
  free(dinic.vis);

  return 0;
}

