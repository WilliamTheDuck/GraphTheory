#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

int mark[MAX], d[MAX];

/* ================== TOPO SORT ================== */
void dfs(Graph* pG, int u, List* pL)
{
    mark[u] = 1;
    for (int v = pG->n; v >= 1; v--)
    {
        if (pG->A[u][v] != 0 && mark[v] == 0)
        {
            dfs(pG, v, pL);
        }
    }
    append_list(pL, u);
}
void topo_sort(Graph* pG, List* pL)
{
    init_list(pL);
    for (int u = 1; u <= pG->n; u++)
        mark[u] = 0;
    
    for (int u = pG->n; u >= 1; u--)
    {
        if (mark[u] == 0)
            dfs(pG, u, pL);
    }
    reverse_list(pL);
}

/* ================== READ ================== */
void read_DAG(Graph* pG)
{
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(pG, n);

    for (int e = 1; e <= m; e++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add_edge_Directed(pG, x, y);
    }
}   

/* ================== GRAPH RANKING ================== */
void rank(Graph* pG, int r[])
{
    int d[MAX];
    for (int u = 1; u <= pG->n; u++)
    {
        d[u] = 0;
        for (int v = 1; v <= pG->n; v++)
            if (pG->A[v][u] != 0)
                d[u]++;
    }

    List L1, L2;
    init_list(&L1); 
    // Push root node to L1
    for (int u = 1; u <= pG->n; u++)
        if (d[u] == 0)
            append_list(&L1, u);

    // Rank starts at 0
    int k = 0;
    while (L1.size > 0)
    {
        init_list(&L2);
        for (int i = 1; i<= L1.size; i++)
        {
            int u = element_at(&L1, i);
            r[u] = k;

            // Delete u & reduce in-degree of v (neighbours of u)
            for (int v = 1; v <= pG->n; v++)
                if (pG->A[u][v] != 0)
                {
                    d[v]--;
                    if (d[v] == 0)
                        append_list(&L2, v);
                }
        }
        L1 = L2;
        k++;
    }
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    read_DAG(&G);
    List L; 
    init_list(&L);
    memset(mark, 0, sizeof(mark));

    topo_sort(&G, &L);
    for (int i = 1; i <= L.size; i++)
        printf("%d ", L.data[i]);
    printf("\n");

    return 0;
}

