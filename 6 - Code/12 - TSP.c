#include <stdio.h>
#include <stdlib.h>

#define MAX 200
int parent[MAX], deg[MAX];

/* ================== GRAPH INIT ================== */
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
void add_edge(Graph* pG, int u, int v, int w)
{
    pG->m++;
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
}

/* ================== COMPARE FUNCTION ================== */
int cmpfunc(const void* a, const void* b)
{
    Edge* x = (Edge*)a;
    Edge* y = (Edge*)b;
    if (x->w == y->w) return 0;
    if (x->w < y->w) return -1;
    if (x->w > y->w) return 1;
}

/* ================== DISJOIN SET UNION ================== */
void init_forest(Graph* pG)
{
    for (int u = 1; u <= pG->n; u++)
        parent[u] = u;
}
int find_parent(int u)
{
    if (u == parent[u])
        return u;
    return parent[u] = find_parent(parent[u]);
}
void union_set(int r1, int r2)
{
    parent[r2] = r1;
}

/* ================== DEGREE 3 CHECK ================== */
int will_over_degree(int u, int v)
{
    return (deg[u] + 1 > 2 || deg[v] + 1 > 2);
}

/* ================== TSP ================== */
void TSP(Graph* pG, Graph* pT, int* sum_w)
{   
    // 1. Init forest
    init_forest(pG);
    for (int u = 1; u <= pG->n; u++)
        deg[u] = 0;

    // 2. Sort
    qsort(&(pG->edges[1]), pG->m, sizeof(Edge), cmpfunc);

    // 3. Build partial tour (n-1 edges)
    int k = 0;
    for (int e = 1; e <= pG->m && k < pG->n-1; e++)
    {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int r1 = find_parent(u);
        int r2 = find_parent(v);

        if (r1 != r2 && !will_over_degree(u, v))
        {
            add_edge(pT, u, v, w);
            union_set(r1, r2);
            deg[u]++;
            deg[v]++;
            *sum_w += w;
        }
    }

    // 4. Add last edge that closes the cycle
    for (int e = 1; e <= pG->m; e++) 
    {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int r1 = find_parent(u);
        int r2 = find_parent(v);

        if (r1 == r2 && !will_over_degree(u, v))
        {
            add_edge(pT, u, v, w);
            *sum_w += w;
            break;
        }
    }
}

/* ================== READ & PRINT ================== */
void read_graph(Graph* pG, Graph* pT)
{
    freopen("D:\\CODE C\\Library\\Data-EdgeList-6.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(pG, n);
    init_graph(pT, n);
    for (int e = 1; e <= m; e++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(pG, u, v, w);
    }
    fclose(stdin);
}
void print_graph(Graph* pG)
{
    printf("%d %d\n", pG->n, pG->m);
    for (int e = 1; e <= pG->m; e++)
    {
        printf("%d %d %d\n", pG->edges[e].u, pG->edges[e].v, pG->edges[e].w);
    }    
}
/* ================== MAIN ================== */
int main()
{
    Graph G, T;
    int sum_w = 0;
    read_graph(&G, &T);
    TSP(&G, &T, &sum_w);
    print_graph(&T);
    printf("%d\n", sum_w);

    return 0;
}