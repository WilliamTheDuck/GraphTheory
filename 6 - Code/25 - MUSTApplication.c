#include <stdio.h>
#include <DataStructure.h>

/* ================== PRIM ================== */
int mark[MAX], parent[MAX], pi[MAX], sum_w = 0;
#define oo 9999999

void Prim(Graph* pG, Graph* pT, int s)
{
    for (int u = 1; u <= pG->n; u++)
    {
        mark[u] = 0;
        parent[u] = -1;
        pi[u] = oo;
    }
    pi[s] = 0;

    for (int k = 1; k <= pG->n; k++)
    {
        int u = -1;
        int min_pi = oo;
        for (int v = 1; v <= pG->n; v++)
        {
            if (mark[v] == 0 && pi[v] < min_pi)
            {
                min_pi = pi[v];
                u = v;
            }
        }

        mark[u] = 1;

        for (int v = 1; v <= pG->n; v++)
        {
            if (mark[v] == 0 && pG->A[u][v] >= 0 && pi[v] > pG->A[u][v])
            {
                pi[v] = pG->A[u][v];
                parent[v] = u;
            }
        }
    }

    init_weightedgraph(pT, pG->n);
    for (int u = 1; u <= pG->n; u++)
    {
        if (parent[u] != -1)
        {
            int w = pG->A[parent[u]][u];
            add_edge_weightedgraph(pT, parent[u], u, w);
            sum_w += w;
        }
    }
}

/* ================== MAIN ================== */
int main()
{
    Graph G, T;
   
    /* ------------------ NGUU_LANG & CHUC_NU ------------------ */
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    init_weightedgraph(&G, n);

    for (int e = 1; e <= m; e++)
    {
        int u, v, q;
        scanf("%d%d%d", &u, &v, &q);
        add_edge_weightedgraph(&G, u, v, q);
    }

    // Prim
    Prim(&G, &T, 1);

    // Print
    if (sum_w <= k) 
        printf("OK");
    else
        printf("%d", sum_w - k);

    /* ------------------ LY_THUONG_KIET ------------------ */
    int n, m;
    scanf("%d%d%d", &n, &m);
    init_weightedgraph(&G, n);

    for (int e = 1; e <= m; e++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge_weightedgraph(&G, u, v, w);
    }

    // Prim
    Prim(&G, &T, 1);

    // Print
    printf("%d", sum_w);

    /* ------------------ THO_DIEN ------------------ */
    int n, m;
    scanf("%d%d", &n, &m);
    init_weightedgraph(&G, n);

    for (int e = 1; e <= m; e++)
    {
        int u, v, s, d;
        scanf("%d%d%d%d", &u, &v, &s, &d);
        int price = s*d;
        add_edge_weightedgraph(&G, u, v, price);
    }
    
    // Prim
    Prim(&G, &T, 1);

    // Print
    printf("%d", sum_w);

    /* ------------------ BAY_NAI ------------------ */
    int n, m;
    scanf("%d%d%d", &n, &m);
    init_weightedgraph(&G, n);

    for (int e = 1; e <= m; e++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge_weightedgraph(&G, u, v, w);
    }

    // Prim
    Prim(&G, &T, 1);

    // Print
    printf("%d", sum_w);

    return 0;
}