#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX], queue[MAX];
int front = -1, rear = -1;

void bfs(int start, int n) {
    visited[start] = 1;
    queue[++rear] = start;

    while (front != rear) {
        int node = queue[++front];
        printf("%d ", node);

        for (int i = 0; i < n; i++) {
            if (adj[node][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

int main() {
    int n, edges, u, v, start;
    scanf("%d%d", &n, &edges);
    
    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    scanf("%d", &start);
    bfs(start, n);
    return 0;
}



#include <stdio.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX];

void dfs(int node, int n) {
    visited[node] = 1;
    printf("%d ", node);

    for (int i = 0; i < n; i++) {
        if (adj[node][i] == 1 && !visited[i]) {
            dfs(i, n);
        }
    }
}

int main() {
    int n, edges, u, v, start;
    scanf("%d%d", &n, &edges);

    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    scanf("%d", &start);
    dfs(start, n);
    return 0;
}


#include <stdio.h>
#include <limits.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX];

int findMinVertex(int cost[], int visited[], int n) {
    int min = INT_MAX, minIndex;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && cost[i] < min) {
            min = cost[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void prim(int n) {
    int parent[MAX], cost[MAX];
    for (int i = 0; i < n; i++) {
        cost[i] = INT_MAX;
        visited[i] = 0;
    }

    cost[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++) {
        int u = findMinVertex(cost, visited, n);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] && !visited[v] && adj[u][v] < cost[v]) {
                cost[v] = adj[u][v];
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < n; i++)
        printf("%d - %d\n", parent[i], i);
}

int main() {
    int n, edges, u, v, w;
    scanf("%d%d", &n, &edges);

    for (int i = 0; i < edges; i++) {
        scanf("%d%d%d", &u, &v, &w);
        adj[u][v] = adj[v][u] = w;
    }

    prim(n);
    return 0;
}



#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

Edge edges[MAX];
int parent[MAX];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSets(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);
    parent[rootI] = rootJ;
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(int n, int e) {
    for (int i = 0; i < n; i++) parent[i] = i;
    qsort(edges, e, sizeof(edges[0]), compare);

    for (int i = 0; i < e; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (find(u) != find(v)) {
            printf("%d - %d\n", u, v);
            unionSets(u, v);
        }
    }
}

int main() {
    int n, e;
    scanf("%d%d", &n, &e);

    for (int i = 0; i < e; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskal(n, e);
    return 0;
}




#include <stdio.h>
#include <limits.h>

#define MAX 100

int adj[MAX][MAX], dist[MAX], visited[MAX];

int findMinVertex(int n) {
    int min = INT_MAX, minIndex;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int n, int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = findMinVertex(n);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && adj[u][v] && dist[u] != INT_MAX && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("Distance to %d = %d\n", i, dist[i]);
    }
}

int main() {
    int n, edges, u, v, w, start;
    scanf("%d%d", &n, &edges);

    for (int i = 0; i < edges; i++) {
        scanf("%d%d%d", &u, &v, &w);
        adj[u][v] = adj[v][u] = w;
    }

    scanf("%d", &start);
    dijkstra(n, start);
    return 0;
}


#include <stdio.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX];

int dfs(int node, int parent, int n) {
    visited[node] = 1;

    for (int i = 0; i < n; i++) {
        if (adj[node][i]) {
            if (!visited[i]) {
                if (dfs(i, node, n)) return 1;
            } else if (i != parent) {
                return 1;
            }
        }
    }
    return 0;
}

int hasCycle(int n) {
    for (int i = 0; i < n; i++)
        if (!visited[i])
            if (dfs(i, -1, n)) return 1;
    return 0;
}

int main() {
    int n, edges, u, v;
    scanf("%d%d", &n, &edges);

    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    if (hasCycle(n)) printf("Cycle detected\n");
    else printf("No cycle detected\n");

    return 0;
}



#include <stdio.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX], recStack[MAX];

int dfs(int node, int n) {
    if (!visited[node]) {
        visited[node] = 1;
        recStack[node] = 1;

        for (int i = 0; i < n; i++) {
            if (adj[node][i]) {
                if (!visited[i] && dfs(i, n)) return 1;
                else if (recStack[i]) return 1;
            }
        }
    }
    recStack[node] = 0;
    return 0;
}

int hasCycle(int n) {
    for (int i = 0; i < n; i++)
        if (!visited[i])
            if (dfs(i, n)) return 1;
    return 0;
}

int main() {
    int n, edges, u, v;
    scanf("%d%d", &n, &edges);

    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = 1;  // Only one direction for directed graph
    }

    if (hasCycle(n)) printf("Cycle detected\n");
    else printf("No cycle detected\n");

    return 0;
}


#include <stdio.h>
#include <limits.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX];

int findMinVertex(int cost[], int visited[], int n) {
    int min = INT_MAX, minIndex;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && cost[i] < min) {
            min = cost[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void prim(int n) {
    int parent[MAX], cost[MAX];
    for (int i = 0; i < n; i++) {
        cost[i] = INT_MAX;
        visited[i] = 0;
    }

    cost[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++) {
        int u = findMinVertex(cost, visited, n);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] && !visited[v] && adj[u][v] < cost[v]) {
                cost[v] = adj[u][v];
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < n; i++)
        printf("Edge: %d - %d, Weight: %d\n", parent[i], i, adj[i][parent[i]]);
}

int main() {
    int n, edges, u, v, w;
    scanf("%d%d", &n, &edges);

    for (int i = 0; i < edges; i++) {
        scanf("%d%d%d", &u, &v, &w);
        adj[u][v] = adj[v][u] = w;
    }

    prim(n);
    return 0;
}



#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

Edge edges[MAX];
int parent[MAX];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSets(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);
    parent[rootI] = rootJ;
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(int n, int e) {
    for (int i = 0; i < n; i++) parent[i] = i;
    qsort(edges, e, sizeof(edges[0]), compare);

    for (int i = 0; i < e; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (find(u) != find(v)) {
            printf("Edge: %d - %d, Weight: %d\n", u, v, w);
            unionSets(u, v);
        }
    }
}

int main() {
    int n, e;
    scanf("%d%d", &n, &e);

    for (int i = 0; i < e; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskal(n, e);
    return 0;
}



#include <stdio.h>
#include <limits.h>

#define MAX 100

int adj[MAX][MAX], dist[MAX], visited[MAX];

int findMinVertex(int n) {
    int min = INT_MAX, minIndex;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int n, int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = findMinVertex(n);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && adj[u][v] && dist[u] != INT_MAX && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("Distance to %d = %d\n", i, dist[i]);
    }
}

int main() {
    int n, edges, u, v, w, start;
    scanf("%d%d", &n, &edges);

    for (int i = 0; i < edges; i++) {
        scanf("%d%d%d", &u, &v, &w);
        adj[u][v] = w;  // Directed graph, so only one direction
    }

    scanf("%d", &start);
    dijkstra(n, start);
    return 0;
}

