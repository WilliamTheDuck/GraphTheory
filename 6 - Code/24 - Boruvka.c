#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 200
#define oo 99999999

/* ================== WEIGHTED GRAPH (EDGE LIST) ================== */
typedef struct {
    int u, v, w;
} Edge;

typedef struct {
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

/* ================== FIND ROOT & UNION ================== */
int parent[MAX];

int find_root(int u)
{
    // Path compression
    if (parent[u] != u)
        parent[u] = find_root(parent[u]);
    return parent[u];
}

void union_sets(int u, int v)
{
    int ru = find_root(u);
    int rv = find_root(v);
    if (ru != rv)
        parent[rv] = ru; // Merge two components
}

/* ================== BORUVKA ================== */
/*
    Main idea:
    - Each component selects its cheapest edge that connects it to another component.
    - Add all these cheapest edges.
    - Merge the connected components.
    - Repeat until we form a tree with (n - 1) edges.
*/
void Boruvka(Graph* pG, Graph* pT, int* sum_w)
{
    // 1. Initialize every vertex as an independent component
    for (int u = 1; u <= pG->n; u++)
        parent[u] = u;

    int numTrees = pG->n;     // Number of current components
    int cheapest[MAX];         // cheapest[c] stores the cheapest edge of component c

    while (numTrees > 1)
    {
        // Reset cheapest for every component
        for (int i = 1; i <= pG->n; i++)
            cheapest[i] = -1;

        /* 2. Scan all edges and update cheapest edge for each component */
        for (int e = 1; e <= pG->m; e++)
        {
            int u = pG->edges[e].u;
            int v = pG->edges[e].v;
            int w = pG->edges[e].w;

            int ru = find_root(u);
            int rv = find_root(v);

            // Ignore edges inside the same component
            if (ru == rv)
                continue;

            // Update cheapest for root ru
            if (cheapest[ru] == -1 || pG->edges[cheapest[ru]].w > w)
                cheapest[ru] = e;

            // Update cheapest for root rv
            if (cheapest[rv] == -1 || pG->edges[cheapest[rv]].w > w)
                cheapest[rv] = e;
        }

        /* 3. Add the selected cheapest edges to the MST */
        for (int c = 1; c <= pG->n; c++)
        {
            int e = cheapest[c];
            if (e != -1)
            {
                int u = pG->edges[e].u;
                int v = pG->edges[e].v;
                int w = pG->edges[e].w;

                int ru = find_root(u);
                int rv = find_root(v);

                // Only add if they belong to different components
                if (ru != rv)
                {
                    add_edge(pT, u, v, w); // Add edge to MST
                    union_sets(ru, rv);    // Merge components
                    numTrees--;

                    *sum_w += w;
                }
            }
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
        add_edge(pG, u, v, w);
    }
    fclose(stdin);
}

void print_graph(Graph* pG)
{
    for (int e = 1; e <= pG->m; e++)
    {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;

        // Print u < v to keep output aesthetic
        if (u > v) {
            int tmp = u; u = v; v = tmp;
        }
        printf("%d %d %d\n", u, v, w);
    }
}

/* ================== MAIN ================== */
int main()
{
    Graph G, T;
    int sum_w = 0;
    read_graph(&G, &T);

    Boruvka(&G, &T, &sum_w);

    print_graph(&T);
    printf("Total weight = %d\n", sum_w);

    return 0;
}
