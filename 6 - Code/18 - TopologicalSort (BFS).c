#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

/* ================== TOPO SORT ================== */
void topo_sort(Graph* pG, List* pL)
{
    int d[MAX]; 
    // Calculate in-degree of vertices
    for (int u = 1; u <= pG->n; u++)
    {
        d[u] = 0;
        for (int v = 1; v <= pG->n; v++)
            if (pG->A[v][u] != 0)
                d[u]++;
    }

    Queue Q; init_queue(&Q);
    // Push vertices that has d[u] = 0 into queue
    for (int u = 1; u <= pG->n; u++)
        if (d[u] == 0)
            push_queue(&Q, u);
    
    init_list(pL);
    while (!empty_queue(&Q))
    {
        int u = front_queue(&Q);
        pop_queue(&Q);
        append_list(pL, u); // List saving graph transversal

        // Delete u & reduce in-degree of v (neighbours of u)
        for (int v = 1; v <= pG->n; v++)
            if (pG->A[u][v] != 0)
            {
                d[v]--;
                if (d[v] == 0)
                    push_queue(&Q, v);
            }
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

/* ================== READ ================== */
void read_DAG(Graph* pG)
{
    FILE* f = fopen("D:\\CODE C\\Library\\Data-EdgeList-3.txt", "r");
    int n, m;
    fscanf(f, "%d%d", &n, &m);
    init_graph(pG, n);

    for (int e = 1; e <= m; e++)
    {
        int x, y;
        fscanf(f, "%d%d", &x, &y);
        add_edge_Directed(pG, x, y);
    }
    fclose(f);
}   

/* ================== MAIN ================== */
int main()
{
    Graph G;
    read_DAG(&G);
    List L; 
    init_list(&L);
    
    print_graph(&G);

    topo_sort(&G, &L);
    printf("Topo Sort:\n");
    for (int i = 1; i <= L.size; i++)
        printf("%d ", L.data[i]);
    printf("\n");

    int r[MAX];
    memset(r, 0, sizeof(r));
    rank(&G, r);
    printf("Rank:\n");
    for (int u = 1; u <= G.n; u++)
        printf("rank[%d] = %d\n", u, r[u]);
    
    return 0;
}

