#include <stdio.h>
#define MAX 200

/* ================== GRAPH (Edge List) ================== */
typedef struct
{
    int u, v, w;
} Edge;
typedef struct
{
    int n, m;
    Edge edges[MAX];
} Graph;

void init_graph(Graph* pG, int n)
{
    pG->n = n;
    pG->m = 0;
}
void add_edge(Graph* pG, int u, int v, int w)
{
    pG->m++;
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
}
void read_graph(Graph* pG)
{
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(pG, n);
    for (int e = 1; e <= m; e++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
            add_edge(pG, u, v, w);
    }
}

/* ================== BELLMAN-FORD ================== */
#define oo 9999999
int pi[MAX];
int parent[MAX];
int negative_cycle = 0;

void BellmanFord(Graph* pG, int s) // O(n^2)
{
    int u, v, w;
    for (int i = 1; i <= pG->n; i++)
        pi[i] = oo;
    pi[s] = 0; parent[s] = -1;

    for (int k = 1; k <= pG->n - 1; k++)
        for (int e = 1; e <= pG->m; e++)
        {
            u = pG->edges[e].u;
            v = pG->edges[e].v;
            w = pG->edges[e].w;
            if (pi[u] == oo)
                continue;
            if (pi[v] > pi[u] + w)
            {
                pi[v] = pi[u] + w;
                parent[v] = u;
            }
        }

    // Better remove these below lines
    // // Check for negative cycle
    // for (int e = 1; e <= pG->m; e++)
    // {
    //     int u = pG->edges[e].u;
    //     int v = pG->edges[e].v;
    //     int w = pG->edges[e].w;
    //     if (pi[v] > pi[u] + w)
    //     {
    //         negative_cycle = 1;
    //         break;
    //     }
    // }
}

/* ================== STACK ================== */
typedef struct 
{
    int data[MAX];
    int size;
} Stack;

void init_stack(Stack* pS)
{
    pS->size = 0;
}
int empty_stack(Stack* pS)
{
    return pS->size == 0;
}
int full_stack(Stack* pS)
{
    return pS->size == MAX;
}
void push_stack(Stack* pS, int x)
{
    if (full_stack(pS))
        return;
    pS->size++;
    pS->data[pS->size] = x;
}
void pop_stack(Stack* pS)
{
    if (!empty_stack(pS))
        pS->size--;
}
int top_stack(Stack* pS)
{
    return pS->data[pS->size];
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
    read_graph(&G);
    int s, t; scanf("%d%d", &s, &t);

    BellmanFord(&G, s);
    print_shortestpath(&G, s, t);
    return 0;
}