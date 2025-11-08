#include <stdio.h>

#define MAX 200
#define oo 9999999

/* ================== GRAPH ================== */
typedef struct 
{
    int u, v, w, link;
} Edge;
typedef struct 
{
    int n, m;
    Edge edges[MAX];
} Graph; // G
typedef struct
{
    int n;
    int parent[MAX], weight[MAX], link[MAX];
} Tree; // H

void init_graph(Graph* pG, int n)
{
    pG->n = n;
    pG->m = 0;
}
void init_tree(Tree* pT, int n)
{
    pT->n = n;
    for (int u = 1; u <= n; u++)
    {
        pT->parent[u] = -1;
        pT->weight[u] = oo;
        pT->link[u] = -1;
    }
}
void add_edge(Graph* pG, int u, int v, int w, int link) // Base-1
{
    pG->m++;
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->edges[pG->m].link = link;
}

/* ================== READ & PRINT ================== */
void read_graph(Graph* pG)
{
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(pG, n);
    for (int e = 1; e <= m; e++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(pG, u, v, w, -1);
    }
}
void print_tree(Tree* T)
{
    for (int u = 1; u <= T->n; u++)
        if (T->parent[u] != -1)
            printf("(%d, %d) %d\n", T->parent[u], u, T->weight[u]);
}

/* ================== BUILD H ================== */
void build_H(Graph* pG, int root, Tree* H)
{
    init_tree(H, pG->n); // Initialize empty tree
    int e;
    for (int e = 1; e <= pG->m; e++)
    {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int link = pG->edges[e].link;

        if (w < H->weight[v])
        {
            H->parent[v] = u;
            H->weight[v] = w;
            H->link[v] = link; // Link to G(t-1) edges
        }
    }
    H->parent[root] = -1; 
    H->weight[root] = 0;
}

/* ================== CYCLE CHECK ================== */
int id[MAX];

int find_cycles(Tree* H, int root)
{
    int u, v;
    int number_of_cycles = 0;
    int color[MAX];

    // Init
    for (u = 1; u <= H->n; u++)
    {
        id[u] = -1;
        color[u] = -1;
    }

    for (u = 1; u <= H->n; u++)
    {
        v = u;
        while (v != root && id[v] == -1 && color[v] != u)
        {
            color[v] = u;
            v = H->parent[v];
        }
        // If meet u again -> Make a cycle
        if (color[v] == u)
        {
            number_of_cycles++;
            int x = H->parent[v];
            while (x != v)
            {
                id[x] = number_of_cycles;
                x = H->parent[x];
            }
            id[v] = number_of_cycles; // v is a vertex in cycle
        }
    }
    
    return number_of_cycles;
}

/* ================== CONTRACT GRAPH ================== */
void contract(Graph* G, Tree* H, int number_of_cycles, Graph* G1)
{
    init_graph(G1, number_of_cycles);
    for (int e = 1; e <= G->m; e++)
    {
        int u = G->edges[e].u;
        int v = G->edges[e].v;
        int w = G->edges[e].w;
        
        if (id[u] != id[v])
            add_edge(G1, id[u], id[v], w - H->weight[v], e);
    }
}

/* ================== EXPAND GRAPH ================== */
void expand(Tree* H, Graph* G1, Tree* H1)
{
    for (int u = 1; u <= H->n; u++)
        if (H->parent[u] != -1)
        {
            // Get corresponding edge in G(t-1)
            Edge pe = G1->edges[H->link[u]];
            // Change parent of pe.v -> pe.u
            H1->parent[pe.v] = pe.u;
            H1->weight[pe.v] += H->weight[u];
            H1->link[pe.v] = pe.link;
        }
}

/* ================== CHU-LIU / EDMONDS ================== */
#define MAXIT 10

void ChuLiuEdmonds(Graph* G0, int s, Tree* T)
{
    Graph G[MAXIT];
    Tree H[MAXIT];
    int t = 0, root = s;
    G[0] = *G0;

    // 1. Contraction phase
    while (1)
    {
        // Build simplified graph
        build_H(&G[t], root, &H[t]);
        int number_of_cycles = find_cycles(&H[t], root);
        if (number_of_cycles == 0)
            break;

        // Rename for vertices excluding cycles
        for (int u = 1; u <= H[t].n; u++)
            if (id[u] == -1)
                id[u] = number_of_cycles++;
        
        // Contraction
        contract(&G[t], &H[t], number_of_cycles, &G[t+1]);
        root = id[root]; // New root
        t++;
    }

    // 2. Expansion phase
    for (int k = t; k > 0; k--)
        expand(&H[k], &G[k-1], &H[k-1]);

    // Solution is H0
    *T = H[0];
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    freopen("D:\\CODE C\\Library\\Data-Weighted_EdgeList-1.txt", "r", stdin);
    read_graph(&G);
    fclose(stdin);

    Tree T;
    ChuLiuEdmonds(&G, 1, &T);
    print_tree(&T);

    return 0;
}