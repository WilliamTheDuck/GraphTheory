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
    
    for (int i = 0; i < pL->size - 1; i++)
    {
        int minindex = i;
        for (int j = i + 1; j < pL->size; j++)
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
        printf("%d ", pL->data[i-1]);
    printf("0\n");
}

/* ================== GRAPH (Edge List) ================== */
typedef struct 
{
    int u, v;
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
int adjacent(Graph* pG, int u, int v)
{
    for (int e = 1; e <= pG->m; e++)
        if ((pG->edges[e].u == u && pG->edges[e].v == v)
            || (pG->edges[e].u == v && pG->edges[e].v == u))
            return 1;
    return 0;
}
int adjacent_Directed(Graph* pG, int u, int v)
{
    for (int e = 1; e <= pG->m; e++)
        if (pG->edges[e].u == u && pG->edges[e].v == v)
            return 1;
    return 0;
}
int check_opposite(Graph* pG, int u, int v) 
{
    if (u == v)
        return 0;
    for (int e = 1; e <= pG->m; e++)
        // True if found an opposite direction graph 
        if (pG->edges[e].u == v && pG->edges[e].v == u) 
            return 1;
    return 0;
}
void add_edge(Graph* pG, int u, int v)
{
    pG->m++;
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
}
void add_edge_Directed(Graph* pG, int u, int v)
{
    pG->m++;
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
}
int degree(Graph* pG, int x)
{
    int deg = 0;
    for (int e = 1; e <= pG->m; e++)
    {
        if (pG->edges[e].u == x || pG->edges[e].v == x)
        {
            if (pG->edges[e].u == pG->edges[e].v)
                deg++;
            deg++;
        }
    }
    return deg;
}
int out_degree(Graph* pG, int x)
{
    int deg = 0;
    for (int e = 1; e <= pG->m; e++)
        if (pG->edges[e].u == x)
            deg++;
    return deg;
}
int in_degree(Graph* pG, int x)
{
    int deg = 0;
    for (int e = 1; e <= pG->m; e++)
        if (pG->edges[e].v == x)
            deg++;
    return deg;
}
List neighbours(Graph* pG, int x)
{
    List L;
    init_list(&L);
    
    // First count how many edges go to each vertex
    int count[MAX] = {0};
    for (int e = 1; e <= pG->m; e++)
    {
        if (pG->edges[e].u == x)
        {
            count[pG->edges[e].v]++;
        } 
    }
    
    // Then add vertices in order, repeating based on edge count
    for (int v = 1; v <= pG->n; v++)
    {
        for (int i = 0; i < count[v]; i++)
        {
            append_list(&L, v);
        }
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
// int check_opposite(Graph* pG, int u, int v) 
// {
//     if (u == v)
//         return 0;
//     for (int e = 1; e <= pG->m; e++)
//         // True if found an opposite direction graph 
//         if (pG->edges[e].u == v && pG->edges[e].v == u) 
//             return 1;
//     return 0;
// }
// void read_graph_adjmatrix(Graph* pG)
// {
//     int n;
//     scanf("%d", &n);
//     init_graph(pG, n);

//     int arr[MAX][MAX];
//     // Initialize matrix
//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= n; j++)
//             arr[i][j] = 0;

//     for (int u = 1; u <= pG->n; u++)
//         for (int v = 1; v <= pG->n; v++)
//         { 
//             scanf("%d", &arr[u][v]);
//             while (arr[u][v] > 0)   
//             {
//                 // Only add if it's not a reverse of an existing edge
//                 if (!check_opposite(pG, u, v))
//                     add_edge(pG, u, v);
//                 arr[u][v]--;
//             }
//         }
// }
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
    printf("Edge List:\n");
    for (int e = 1; e <= pG->m; e++)
        printf("%d %d\n", pG->edges[e].u, pG->edges[e].v);
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
    
    return 0;
}