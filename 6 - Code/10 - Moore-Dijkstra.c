#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

/* ================== MOORE-DIJKSTRA ================== */
#define oo 9999999
int mark[MAX];
int pi[MAX];
int parent[MAX];

void MooreDijkstra(Graph* pG, int x) // O(n^2)
{
    int u;
    // Initialize mark[], pi[]
    for (int i = 1; i <= pG->n; i++)
    {
        mark[i] = 0;
        pi[i] = oo;
    }
    pi[x] = 0; parent[x] = -1;

    // Transverse n-1 times
    for (int k = 1; k <= pG->n - 1; k++)
    {
        int min_pi = oo;

        // Find vertex u that has mark[u] == 0 and has smallest pi[u]
        for (int j = 1; j <= pG->n; j++)
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                min_pi = pi[j];
                u = j;
            }

        // Mark u
        mark[u] = 1;

        // Update pi[v] and parent[v] with v's are neighbours of u
        for (int v = 1; v <= pG->n; v++)
            if (pG->A[u][v] != -1 && mark[v] == 0 && (pi[v] > pi[u] + pG->A[u][v]))
            {
                pi[v] = pi[u] + pG->A[u][v];
                parent[v] = u;
            }
    }
}

/* ================== PRINT FUNCTIONS ================== */
void print_pi_parent(Graph* pG)
{
    for (int u = 1; u <= pG->n; u++)
        printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, parent[u]);
}
void print_length_path(Graph* pG, int u)
{
    if (pi[u] == oo) printf("-1");
    else printf("%d", pi[u]);
}
void print_shortestpath(Graph* pG, int s, int t)
{
    if (pi[t] == oo)
    {
        // No path found
        printf("-1\n");
        return;
    }

    // Construct paths reversely using stack
    Stack S;
    init_stack(&S);
    int cur = t; // Assign current = last vertex (s->t)
    while (cur != -1)
    {
        push_stack(&S, cur);
        cur = parent[cur];
    }

    // Print in order (popping stack) s -> ... -> t
    int first = 1;
     while (!empty_stack(&S))
    {
        if (!first)
            printf(" -> ");
        printf("%d", top_stack(&S));
        pop_stack(&S);
        first = 0;
    }
    printf("\n");
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    read_weightedgraph_edgelist(&G, 1);
    int s, t; scanf("%d%d", &s, &t);

    MooreDijkstra(&G, s);
    print_shortestpath(&G, s, t);
    return 0;
}