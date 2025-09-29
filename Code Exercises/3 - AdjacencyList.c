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

/* ================== GRAPH (Adjacency List) ================== */
typedef struct 
{
    int n, m;
    List adjList[MAX];
} Graph;

void init_graph(Graph* pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++)
        init_list(&pG->adjList[u]);
}
int adjacent(Graph* pG, int u, int v)
{
    for (int e = 1; e <= pG->adjList[u].size; e++) 
        if (pG->adjList[u].data[e] == v)  
            return 1;
    return 0;
}    
void add_edge(Graph* pG, int u, int v)
{
    append_list(&(pG->adjList[u]), v);
    append_list(&(pG->adjList[v]), u);
}
void add_edge_Directed(Graph* pG, int u, int v)
{
    append_list(&(pG->adjList[u]), v);
}
int degree(Graph* pG, int x)
{
    int deg = pG->adjList[x].size;
    return deg;
}
int out_degree(Graph* pG, int x)
{
    int deg = pG->adjList[x].size;
    return deg;
}
int in_degree(Graph* pG, int x)
{
    int deg = 0;
    for (int u = 1; u <= pG->n; u++)
        if (x != u)
            for (int v = 1; v <= pG->adjList[u].size; v++)
                if (x == pG->adjList[u].data[v])    
                    deg++;
    return deg;
}
List neighbours(Graph* pG, int x)
{
    return pG->adjList[x];
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
    printf("Adjacency List:\n");
    for (int u = 1; u <= pG->n; u++)
    {
        if (pG->adjList[u].size == 0)
            printf("0\n");
        else
        {
            for (int v = 1; v <= pG->adjList[u].size; v++)
                printf("%d ", pG->adjList[u].data[v]);
            printf("\n");
        }
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
    read_graph_edgelist_Directed(&G);
    print_graph(&G);
    return 0;
}
