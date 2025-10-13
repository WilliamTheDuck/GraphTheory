#include <stdio.h>
#include <string.h>
#include "DataStructure.h"

/* ================== LIST ================== */
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
void concat_list(List* dst, List src)
{
    for (int i = 1; i <= src.size; i++)
    {
        append_list(dst, src.data[i]);
    }
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
    printf("\n");
}

/* ================== STACK ================== */
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

/* ================== QUEUE ================== */
void init_queue(Queue* pQ)
{
    pQ->front = 1;
    pQ->rear = 0;
}
int empty_queue(Queue* pQ)
{
    return pQ->front > pQ->rear;
}
int full_queue(Queue* pQ)
{
    return (pQ->front == 1 && pQ->rear == MAX);
}
void push_queue(Queue* pQ, int x)
{
    if (pQ->rear == MAX)    
        return;
    pQ->rear++;
    pQ->data[pQ->rear] = x;
}
void pop_queue(Queue* pQ)
{
    if (empty_queue(pQ))  
        return;
    pQ->front++;
}
int front_queue(Queue* pQ)
{
    return pQ->data[pQ->front];
}

/* ================== GRAPH (Adjacency Matrix) ================== */
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
    
    for (int u = 1; u <= n; u++) 
    {
        int v;
        scanf("%d", &v);
        if (!directed)
            add_edge(pG, u, v);
        else
            add_edge_Directed(pG, u, v);
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
void read_from_file(Graph* pG, char graph_type[], int directed)
{
    char filename[MAX];
    // Remove trailing newline from filename
    fgets(filename, MAX, stdin);
    filename[strcspn(filename, "\n")] = 0;
    
    FILE* f = freopen(filename, "r", stdin);
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }
    // Compare strings to determine graph type
    if (strcmp(graph_type, "edgelist") == 0) 
        read_graph_edgelist(pG, directed);
    else if (strcmp(graph_type, "adjmatrix") == 0) 
        read_graph_adjmatrix(pG, directed);
    else if (strcmp(graph_type, "adjlist") == 0)
        read_graph_adjlist(pG, directed);
    else if (strcmp(graph_type, "incidmatrix") == 0)
        read_graph_incidmatrix(pG, directed);
    else
        return;
    // Restore standard input to the console
    #ifdef _WIN32
        freopen("CON", "r", stdin); // Windows
    #else
        freopen("/dev/tty", "r", stdin); // Linux, macOS
    #endif
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

/* ================== WEIGHTED GRAPH ================== */
void init_weightedgraph(Graph* pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pG->A[i][j] = -1;
}
void add_edge_weightedgraph(Graph* pG, int u, int v, int w)
{
    pG->A[u][v] = w;
    pG->A[v][u] = w;
    pG->m++;
}
void add_edge_weightedgraph_Directed(Graph* pG, int u, int v, int w)
{
    pG->A[u][v] = w;
    pG->m++;
}
void read_weightedgraph_edgelist(Graph* pG, int directed)
{
    int n, m;
    scanf("%d%d", &n, &m);
    init_weightedgraph(pG, n);
    for (int e = 1; e <= m; e++)
    {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        if (!directed)
            add_edge_weightedgraph(pG, x, y, w);
        else
            add_edge_weightedgraph_Directed(pG, x, y, w);
    }
}