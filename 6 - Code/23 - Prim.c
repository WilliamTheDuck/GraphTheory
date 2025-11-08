#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

/* ================== PRIM ================== */
int pi[MAX], parent[MAX], mark[MAX], sum_w = 0;
#define oo 999999

void Prim(Graph* pG, Graph* pT, int s)
{
    // 1. Init
    for (int u = 1; u <= pG->n; u++)
    {
        mark[u] = 0;
        parent[u] = -1;
        pi[u] = oo;
    }
    pi[s] = 0;

    // 2. Loop n-1 times
    for (int k = 1; k <= pG->n; k++)
    {
        // 2.1. Find u which is close to component s the most (smallest pi[u])
        int min_pi = oo;
        int u = -1;
        for (int v = 1; v <= pG->n; v++)
            if (mark[v] == 0 && pi[v] < min_pi)
            {
                min_pi = pi[v];
                u = v;
            }
        if (u == -1) // No vertex found
            break;
            
        // 2.2. Mark
        mark[u] = 1;
        // printf("%d\n", u);

        // 2.3. Check neighbours vertices
        for (int v = 1; v <= pG->n; v++)
            // If unmarked neighbour v has shorter distance than pi[u] (old) -> Update pi of neighbours
            if (pG->A[u][v] >= 0 && mark[v] == 0 && pi[v] > pG->A[u][v]) 
            {
                pi[v] = pG->A[u][v];
                parent[v] = u;
            }
    } 

    // 3. Construct tree & compute total weight
    init_weightedgraph(pT, pG->n);
    for (int u = 1; u <= pG->n; u++)
        if (parent[u] != -1) // parent[s] == -1 -> Check internal vertices that has parent[] != -1
        {
            // After constructing MST using Prim, there will be paths connecting u and its only parent p[u] 
            // That's why we add_edge(p[u], u) to build up a Tree
            int w = pG->A[parent[u]][u];
            add_edge_weightedgraph(pT, parent[u], u, w);
            sum_w += w;
        }
}

/* ================== MAIN ================== */
int main()
{
    Graph G, T;
    freopen("D:\\CODE C\\Library\\Data-Weighted_EdgeList-2.txt", "r", stdin);
    read_weightedgraph_edgelist(&G, 0);
    fclose(stdin);

    Prim(&G, &T, 1);
    printf("%d", sum_w);

    return 0;
}