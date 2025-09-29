#include <stdio.h>
#define MAX 200

/* ================== LIST ================== */
typedef struct
{
    int data[MAX];
    int size;
} List;

void init_list(List* pL)
{
    pL->size = 0;
}
void append_list(List* pL, int x)
{
    pL->size++;
    pL->data[pL->size] = x;
}
int element_at(List* pL, int i)
{
    return pL->data[i];
}
void swap(int* x, int* y)
{
    int tem = *y;
    *y = *x;
    *x = tem;
}
void selection_sort(List* pL)
{
    if (pL->size == 0)
        return;
    
    for (int i = 1; i <= pL->size - 1; i++)
    {
        int minindex = i;
        for (int j = i + 1; j <= pL->size; j++)
        {
            if (pL->data[j] <= pL->data[minindex])
                minindex = j;
        }
        swap(&(pL->data[i]), &(pL->data[minindex]));
    }
}
void print_list(List* pL)
{
    for (int i = 1; i <= pL->size; i++)
        printf("%d ", pL->data[i]);
    printf("0\n");
}

/* ================== GRAPH (Adjacency Matrix) ================== */
typedef struct 
{
    int n, m;
    int A[MAX][MAX];
} Graph;

void init_graph(Graph* pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int i = 1; i <= pG->n; i++)
        for (int j = 1; j <= pG->n; j++)
            pG->A[i][j] = 0;
}
int adjacent(Graph* pG, int u, int v)
{
    return (pG->A[u][v] != 0);
}    
void add_edge(Graph* pG, int u, int v)
{
    // Count loop
    if (u == v)
        pG->A[u][v]++;
    else
    {
        pG->A[u][v]++;
        pG->A[v][u]++;
    }
    pG->m++;
}
void add_edge_Directed(Graph* pG, int u, int v)
{
    // Add u->v
    pG->A[u][v]++;
    pG->m++;
}
int degree(Graph* pG, int x)
{
    int deg = 0;
    for (int u = 1; u <= pG->n; u++)
    {
        if (x == u) // In case that edge is a loop -> a loop has deg = 2
            deg += (pG->A[x][u])*2;
        else
            deg += pG->A[x][u]; 
            // If the graph is directed, the line above is calculated as
            // deg += pG->A[x][u] + pG->A[u][x];
    }
    return deg;
}
int out_degree(Graph* pG, int x)
{
    int deg = 0;
    // Transverse through columns, x is row
    for (int v = 1; v <= pG->n; v++)
        deg += pG->A[x][v];
    return deg;
}
int in_degree(Graph* pG, int x)
{
    int deg = 0;
    // Transverse through rows, x is column
    for (int u = 1; u <= pG->n; u++)
        deg += pG->A[u][x];
    return deg;
}
List neighbours(Graph* pG, int x)
{
    List L;
    init_list(&L);
    for (int u = 1; u <= pG->n; u++)
    {
        if (adjacent(pG, x, u)) 
            append_list(&L, u);
    }
    return L;
}

/* ================== READ GRAPH ================== */
void read_graph_edgelist(Graph* pG, int directed)
{
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(pG, n);

    for (int e = 1; e <= m; e++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        {
            if (!directed)
                add_edge(pG, u, v);
            else
                add_edge_Directed(pG, u, v);
        }
    }
}
void read_graph_adjmatrix(Graph* pG, int directed)
{
    int n;
    scanf("%d", &n);
    init_graph(pG, n);
    
    for (int u = 1; u <= n; u++)    
        for (int v = 1; v <= n; v++)
        {
            int entryData;
            scanf("%d", &entryData);
            for (int k = 1; k <= entryData; k++) // Read multiedge -> input duplicate vertex
            {
                if (!directed)
                    add_edge(pG, u, v);
                else
                    add_edge_Directed(pG, u, v);
            }
        }
}
void read_graph_adjlist(Graph* pG, int directed)
{
    int n;
    scanf("%d", &n);
    init_graph(pG, n);
    // Insert adjacency list
    for (int u = 1; u <= n; u++) 
        while (1) 
        {
            int v;
            scanf("%d", &v);
            if (v == 0) break;
            {
                if (!directed)
                    add_edge(pG, u, v);
                else
                    add_edge_Directed(pG, u, v);
            }
        }
}
void read_graph_incidmatrix(Graph* pG, int directed) 
{
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(pG, n);

    int matrix[MAX][MAX];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &matrix[i][j]);

    for (int e = 1; e <= m; e++) 
    {
        int u = -1, v = -1;
        for (int i = 1; i <= n; i++) 
        {
            if (matrix[i][e] == 2) // Loop
            { 
                u = v = i; 
                break; 
            }        
            else if (matrix[i][e] == 1) // Out edge
            { 
                if (u == -1) u = i; 
                else v = i; 
            } 
            else if (matrix[i][e] == -1) // In vertex
                v = i;
        }
        if (u != -1)  
        {
            if (!directed)  
                add_edge(pG, u, v);
            else 
                add_edge_Directed(pG, u, v);
        }
    }
}

/* ================== PRINT GRAPH ================== */
void print_graph(Graph* pG)
{
    printf("Adjacency Matrix:\n");
    for (int i = 1; i <= pG->n; i++)
    {    
        for (int j = 1; j <= pG->n; j++)
            printf("%d ", pG->A[i][j]);
        printf("\n");
    }
}
void print_degree(Graph* pG, int directed) 
{
    if (!directed)
        for (int u = 1; u <= pG->n; u++)
            printf("deg(%d) = %d\n", u, degree(pG, u));
    else
        for (int u = 1; u <= pG->n; u++)
            printf("indeg(%d) = %d, outdeg(%d) = %d, deg(%d)  =%d\n",
                    u, in_degree(pG, u), u, out_degree(pG, u), 
                    u, in_degree(pG, u) + out_degree(pG, u));
}
void print_max_degree(Graph* pG)
{
    int maxdeg = 0, maxindex = 0;
    for (int u = 1; u <= pG->n; u++)
    {
        int deg = degree(pG, u);
        if (maxdeg < deg)  
        {
            maxdeg = deg;
            maxindex = u;
        }
    }
    printf("%d %d\n", maxindex, maxdeg);
}
void print_neighbours(Graph* pG) 
{
    for (int u = 1; u <= pG->n; u++)
    {
        printf("neighbours(%d) = ", u);
        
        List L = neighbours(pG, u);
        selection_sort(&L);
        print_list(&L);
    }
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    read_graph_edgelist(&G, 0);
    print_graph(&G);
    return 0;
}
