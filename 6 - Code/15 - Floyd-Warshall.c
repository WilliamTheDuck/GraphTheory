#include <stdio.h>
#include <DataStructure.h>

/* ================== FLOYD-WARSHALL ================== */
#define oo 9999999
int pi[MAX][MAX];
int next[MAX][MAX];
int negative_cycle = 0;

void FloydWarshall(Graph* pG) // O(n^3)
{
    int u, v, k;
    for (u = 1; u <= pG->n; u++)
    {
        for (int v = 1; v <= pG->n; v++)
        {
            pi[u][v] = oo;
            next[u][v] = -1;
        }
    }

    // Initialize 
    for (u = 1; u <= pG->n; u++)
        for (v = 1; v <= pG->n; v++)
        {
            if (pG->A[u][v] != -1)
            {
                pi[u][v] = pG->A[u][v];
                next[u][v] = v;
            }
        }

    // Distance form u to itself (Diagonal in matrix)
    for (u = 1; u <= pG->n; u++)
    {
        pi[u][u] = 0;
        next[u][u] = u;
    }
            
    // Floyd-Washall
    for (k = 1; k <= pG->n; k++)
        for (u = 1; u <= pG->n; u++)
            for (v = 1; v <= pG->n; v++)
                if (pi[u][k] != oo && pi[u][v] > pi[u][k] + pi[k][v])
                {
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v]= next[u][k];
                }

    // // Check for negative cycle
    // for (int u = 1; u <= pG->n; u++)
    //     if (pi[u][u] < 0)
    //     {
    //         negative_cycle = 1;
    //         break;
    //     }
}

/* ================== PRINT FUNCTIONS ================== */
void print_shortestpath(Graph* pG)
{
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
        {
            if (next[u][v] == -1)
                printf("%d -> %d: NO PATH\n", u , v);
            else 
                printf("%d -> %d: %d\n", u, v, pi[u][v]);
        }
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    read_weightedgraph_edgelist(&G, 1);

    FloydWarshall(&G);
    print_shortestpath(&G);
    return 0;
}