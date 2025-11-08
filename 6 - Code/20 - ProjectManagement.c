#include <stdio.h>
#include <string.h>
#include <math.h>
#include <DataStructure.h>

#define oo 9999999
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

/* ================== MAIN ================== */
int main()
{
    Graph G;
    int n, u, x, v, j;

    // 1. Read graph
    freopen("D:\\CODE C\\Library\\Data-ProjectManagement-1.txt", "r", stdin);
        scanf("%d", &n);

        // Create n+2 vertices graph (including alpha & beta)
        init_graph(&G, n+2);
        int alpha = n+1, beta = n+2;
        d[alpha] = 0; 

        // Read list of tasks
        for (u = 1; u <= n; u++)
        {
            scanf("%d", &d[u]);
            do {
                scanf("%d", &x);
                if (x > 0);
                    add_edge_Directed(&G, x, u);
            } while (x > 0);
        }
    fclose(stdin);

    // 2. Link vertex alpha to graph
    for (u = 1; u <= n; u++)
    {
        int deg_neg = 0;
        for (x = 1; x <= n; x++)
            if (G.A[x][u] > 0)
                deg_neg++;
        if (deg_neg == 0)
            add_edge_Directed(&G, alpha, u);
    }

    // 3. Add graph to beta
    for (u = 1; u <= n; u++)
    {
        int deg_pos = 0;
        for (v = 1; v <= n; v++)
            if (G.A[u][v] > 0)
                deg_pos++;
        if (deg_pos == 0)
            add_edge_Directed(&G, u, beta);
    }

    // 4. Topo sort
    List L;
    topo_sort(&G, &L);

    // 5. t[u]
    int t[MAX];
    t[alpha] = 0;
    // alpha is at the front of the list, others go from 2 -> L.size
    for (j = 2; j <= L.size; j++)
    {
        int u = element_at(&L, j);
        t[u] = -oo;
        for (x = 1; x <= G.n; x++)
            if (G.A[x][u] > 0) // Examine in-degree (columns)
                t[u] = fmax(t[u], t[x] + d[x]);
    }
    // for (j = 2; j <= L.size; j++)
    // {
    //     int u = element_at(&L, j);
    //     int max_t = -oo;
    //     for (x = 1; x <= G.n; x++)
    //         if (G.A[x][u] > 0)  
    //             if (t[x] + d[x] > max_t)
    //                 max_t = d[x] + t[x];
    //     t[u] = max_t;
    // }

    // 6. T[u]
    int T[MAX];
    T[beta] =  t[beta];
    // beta surely points at the end of the list, go in backward from L.size-1 -> 1
    for (j = L.size-1; j >= 1; j--)
    {
        int u = element_at(&L, j);
        T[u] = +oo;
        for (v = 1; v <= G.n; v++)
            if (G.A[u][v] > 0)
                T[u] = fmin(T[u], T[v] - d[u]);
    }

    // 7. Print answers t[u], T[u]
    for (u = 1; u <= G.n-2; u++)
        printf("%d %d\n", t[u], T[u]);
    
    return 0;
}

