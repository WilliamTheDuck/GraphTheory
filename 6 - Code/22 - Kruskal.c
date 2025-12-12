#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define MAX 200

/* ================== WEIGHTED GRAPH ================== */
typedef struct
{
    int u, v, w;
} Edge;
typedef struct
{
    int n, m;
    Edge edges[MAX];
} Graph;

void init_graph(Graph* pG, int n)
{
    pG->n = n;
    pG->m = 0;  
}
void add_edge(Graph* pG, int u, int v, int w) // Base-1
{
    pG->m++;
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
}
void swap_edge(Edge* x, Edge* y)
{
    Edge tmp = *x;
    *x = *y;
    *y = tmp;
}

/* ================== QUICK SORT HELPER ================== */
int cmpfunc(const void* x, const void* y)
{
    Edge* a = (Edge*)x;
    Edge* b = (Edge*)y;
    if (a->w < b->w) return -1;
    if (a->w > b->w) return 1;
    return 0;
}

/* ================== KRUSKAL ================== */
int parent[MAX];

int find_root(int u)
{
    if (parent[u] != u)
        parent[u] = find_root(parent[u]); // Path compression
    return parent[u];
}

void Kruskal(Graph* pG, Graph* pT, int* sum_w)
{
    // 1. Init parent
    for (int u = 1; u <= pG->n; u++)
        parent[u] = u;

    // 2. BubbleSort edge ascendingly
    // for (int i = 0; i < pG->m-1; i++)
    //     for (int j = pG->m-1; j > i; j--)
    //         if (pG->edges[j].w < pG->edges[j-1].w)
    //             swap_edge(&(pG->edges[j]), &(pG->edges[j-1]));

    // 2. Use qsort in <stdlib.h> to sort ascendingly
    qsort(&(pG->edges[1]), pG->m, sizeof(Edge), cmpfunc);

    // 3. Update disjoint sets to share same parent
    for (int e = 1; e <= pG->m; e++)
    {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int root_u = find_root(u);
        int root_v = find_root(v);

        if (root_u != root_v)
        {
            // Add edge to Graph T
            add_edge(pT, u, v, w);
            // Merge root u & v
            parent[root_v] = root_u;
            *sum_w += w;
        }
    }
}

/* ================== READ & PRINT ================== */
void read_graph(Graph* pG, Graph* pT)
{
    freopen("D:\\CODE C\\Library\\Data-Weighted_EdgeList-2.txt", "r", stdin);
        int n, m;
        scanf("%d%d", &n, &m);
        init_graph(pG, n);
        init_graph(pT, n);
        
        for (int e = 1; e <= m; e++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_edge(pG, u, v ,w);
        }
    fclose(stdin);
}
void print_graph(Graph* pG)
{
    // BubbleSort vertices ascendingly 
    // for (int i = 0; i < pG->m-1; i++)
    //     for (int j = pG->m-1; j > i; j--)
    //         if (pG->edges[j].w < pG->edges[j-1].w)
    //             swap_edge(&(pG->edges[j]), &(pG->edges[j-1]));
    for (int e = 1; e <= pG->m; e++)
    {
        if (pG->edges[e].u > pG->edges[e].v)
        {
            int tmp = pG->edges[e].u;
            pG->edges[e].u = pG->edges[e].v;
            pG->edges[e].v = tmp;
        }
        printf("%d %d %d\n", pG->edges[e].u, pG->edges[e].v, pG->edges[e].w);
    }
}

/* ================== MAIN ================== */
int main()
{
    Graph G, T;
    int sum_w = 0;
    read_graph(&G, &T);

    Kruskal(&G, &T, &sum_w);

    print_graph(&T);

    int sum_w_G = 0;
    for (int e = 1; e <= G.m; e++)
    {
        sum_w_G += G.edges[e].w;
    }
    printf("%d", sum_w_G - sum_w); // Print total weight of removed edges

    return 0;
}