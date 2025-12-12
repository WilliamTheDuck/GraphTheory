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
void read_software_project_management(Graph* pG, int* n, int* m, int* alpha, int* beta)
{
    freopen("D:\\CODE C\\Library\\Data-ProjectManagement-2.txt", "r", stdin);

    int x, y, u, e;
    
    // Number of tasks
    scanf("%d", n);
    // Create n+2 vertices graph (including alpha & beta)
    init_graph(pG, *n + 2);
    *alpha = *n + 1;
    *beta = *n + 2;
    d[*alpha] = 0;
    // Time of finishing each task
    for (int u = 1; u <= *n; u++)
        scanf("%d", &d[u]);
    // Pairs of related tasks
    scanf("%d", m);
    // List of pairs of tasks
    for (e = 1; e <= *m; e++)
    {
        scanf("%d%d", &x, &y);
        add_edge_Directed(pG, x, y);
    }
    fclose(stdin);
}

void add_source_sink(Graph* pG, int alpha, int beta)
{
    int u, x, v;
    
    // Link alpha to vertices with in-degree = 0
    for (u = 1; u <= pG->n; u++)
    {
        int in_deg = 0;
        for (x = 1; x <= pG->n; x++)
            if (pG->A[x][u] > 0)
                in_deg++;
        if (in_deg == 0)
            add_edge_Directed(pG, alpha, u);
    }
    
    // Link vertices with out-degree = 0 to beta
    for (u = 1; u <= pG->n; u++)
    {
        int out_deg = 0;
        for (v = 1; v <= pG->n; v++)
            if (pG->A[u][v] > 0)
                out_deg++;
        if (out_deg == 0)
            add_edge_Directed(pG, u, beta);
    }
}

void earliest_start(Graph* pG, List* pL, int alpha, int* t)
{
    int j, u, x;
    t[alpha] = 0;
    
    for (j = 2; j <= pL->size; j++)
    {
        u = element_at(pL, j);
        t[u] = -oo;
        for (x = 1; x <= pG->n; x++)
            if (pG->A[x][u] > 0)
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
}

void latest_start(Graph* pG, List* pL, int beta, int* t, int* T)
{
    int j, u, v;
    T[beta] = t[beta];
    
    for (j = pL->size - 1; j >= 1; j--)
    {
        u = element_at(pL, j);
        T[u] = +oo;
        for (v = 1; v <= pG->n; v++)
            if (pG->A[u][v] > 0)
                T[u] = fmin(T[u], T[v] - d[u]);
    }
}

void print_max_time(Graph* pG, int t[], int T[])
{
    int max_time = 0;
    for (int u = 1; u <= pG->n; u++)
        max_time = fmax(max_time, t[u] + d[u]);
    
    printf("%d",max_time);
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    List L;
    int n, m, alpha, beta;
    int t[MAX], T[MAX];
    
    // 1. Read graph
    read_software_project_management(&G, &n, &m, &alpha, &beta);
    
    // 2-3. Add source and sink
    add_source_sink(&G, alpha, beta);
    
    // 4. Topological sort
    topo_sort(&G, &L);
    
    // 5. Calculate earliest start times
    earliest_start(&G, &L, alpha, t);
    
    // 6. Calculate latest start times
    latest_start(&G, &L, beta, t, T);
    
    // 7. Print results
    print_max_time(&G, t, T);
    
    return 0;
}