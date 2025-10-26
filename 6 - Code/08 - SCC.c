#include <stdio.h>
#include <math.h>
#include <DataStructure.h>

int co = 0; // Count number of SCC
List maxV[MAX]; // Find SCC having the most vertices

/* ================== TARJAN ================== */
int num[MAX], min_num[MAX];
int k;
Stack S;
int on_stack[MAX];

void Tarjan(Graph* pG, int u)
{
    // Number u, push u to stack
    num[u] = min_num[u] = k; k++;
    push_stack(&S, u);
    on_stack[u] = 1;

    // Consider the adjacent vertices of u
    for (int v = 1; v <= pG->n; v++)
    {
        if (adjacent(pG, u, v))
        {
            if (num[v] < 0) // To check this condition, initialize num[i] = -1
            {
                Tarjan(pG, v);
                min_num[u] = fmin(min_num[u], min_num[v]);
            }
            else if (on_stack[v])
                min_num[u] = fmin(min_num[u], num[v]);
        }
    }

    // Check whether u is a peak vertex
    if (num[u] == min_num[u])
    {
        co++;
        printf("Found SCC, %d is a peak vertex\n", u);
        int w;
        do // Pop vertices in S till get u
        {
            w = top_stack(&S);
            append_list(&maxV[co], w);
            pop_stack(&S);
            on_stack[w] = 0;
        }
        while (w != u);
    }
}

/* ================== PRINT SCC ================== */
void print_SCC(Graph* pG)
{
    for (int i = 1; i <= pG->n; i++)
        init_list(&maxV[i]);

    // Run Tarjan for all unvisited vertices
    for (int u = 1; u <= pG->n; u++)
        if (num[u] == -1)
            Tarjan(pG, u);

    // Print result in order
    for (int u = 1; u <= pG->n; u++)
    {
        printf("%d %d\n", num[u], min_num[u]);
    }

    // Print number of SCC
    printf("%d\n", co);
    if (co == 1) printf("STRONG CONNECTED\n");
    else printf("DISCONNECTED\n");

    // Print SCC that has the most number of vertices
    int maxx = 0;
    for (int i = 1; i <= co; i++)
        if (maxV[i].size >= maxx)
            maxx = maxV[i].size;
    printf("%d\n", maxx);
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    read_graph_edgelist(&G, 1);

    for (int i = 1; i <= G.n; i++)
        num[i] = -1;
    k = 1;
    init_stack(&S);
    
    print_SCC(&G);

    return 0;
}