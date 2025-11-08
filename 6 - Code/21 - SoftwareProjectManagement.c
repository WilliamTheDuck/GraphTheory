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

/* ================== SOFTWARE PROJECT MANAGEMENT ================== */
int software_project_management(Graph* pG)
{
    int n, m, x, y, u, v, i;

    // 1. Read file
    freopen("D:\\CODE C\\Library\\Data-ProjectManagement-2.txt", "r", stdin);
        // Number of tasks
        scanf("%d", &n);
        init_graph(pG, n);
        int alpha = n+1, beta = n+2;
        // Time of finishing each task
        for (int u = 1; u <= n; u++)
            scanf("%d", &d[u]);
        // Pairs of related tasks
        scanf("%d", &m);
        // List of pairs of tasks
        for (int e = 1; e <= m; e++)
        {
            scanf("%d%d", &x, &y);
            add_edge_Directed(pG, x, y);
        }
    fclose(stdin);

    // 2. Link vertex alpha to graph
    for (u = 1; u <= n; u++)
    {
        int deg_neg = 0;
        for (x = 1; x <= n; x++)
            if (pG->A[x][u] > 0)
                deg_neg++;
        if (deg_neg == 0)
            add_edge_Directed(pG, alpha, u);
    }

    // 3. Add graph to beta
    for (u = 1; u <= n; u++)
    {
        int deg_pos = 0;
        for (v = 1; v <= n; v++)
            if (pG->A[u][v] > 0)
                deg_pos++;
        if (deg_pos == 0)
            add_edge_Directed(pG, u, beta);
    }

    // 4. Topo sort
    List L;
    topo_sort(pG, &L);

    // 5. t[u]
    int t[MAX];
    t[alpha] = 0;
    // alpha is at the front of the list, others go from 2 -> L.size
    for (i = 2; i <= L.size; i++)
    {
        int u = element_at(&L, i);
        t[u] = -oo;
        for (x = 1; x <= pG->n; x++)
            if (pG->A[x][u] > 0)
                t[u] = fmax(t[u], t[x] + d[x]);
    }

    // 6. T[u]
    int T[MAX];
    T[beta] =  t[beta];
    // beta surely points at the end of the list, go in backward from L.size-1 -> 1
    for (i = L.size-1; i >= 1; i--)
    {
        int u = element_at(&L, i);
        T[u] = +oo;
        for (v = 1; v <= pG->n; v++)
            if (pG->A[u][v] > 0)
                T[u] = fmin(T[u], T[v] - d[u]);
    }

    // 7. Print minimum total time to complete the project
    printf("%d", t[pG->n]);
}   

/* ================== MAIN ================== */
int main()
{
    Graph G;
    software_project_management(&G);
    
    return 0;
}

