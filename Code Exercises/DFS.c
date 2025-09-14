#include <stdio.h>

#define MAX_VERTICES 20
#define MAX_LENGTH 20
#define MAX_ELEMENT_STACK 40

// Create an adjacency matrix presenting an undirected graph
typedef struct 
{
    int A[MAX_VERTICES][MAX_VERTICES]; // Adjacency matrix
    int n; // Number of vertices
} Graph; 

// Initialize a graph containing n vertices
void initGraph(Graph* pG, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            pG->A[i][j] = 0; // Mark all cells to become 0
        }
    }
}

// Insert edges to Graph
void addEdge(Graph* pG, int x, int y)
{
    // Mark both xy & yx positions 
    pG->A[x][y] = 1;
    pG->A[y][x] = 1;
}

// Check if a vertex is adjacent to another
int adjacent(Graph* pG, int x, int y)
{
    return pG->A[x][y] != 0;
}

// Compute degree of a vertex
int degree(Graph* pG, int x)
{
    int deg = 0, i;
    for (i = 1; i <= pG->n; i++)
    {
        if (adjacent(pG, i, x))
            deg++;
    }
    return deg;
}

// Construct an adjacency list
typedef struct
{
    int data[MAX_LENGTH];
    int size;
} List;

// Initialize an empty List
void makeNullList(List* pL)
{
    pL->size = 0;
}

// Push back an element (a vertex) to the list
void appendList(List* pL, int x)
{
    pL->data[pL->size] = x;
    pL->size++;
}

// Retrieve a vertex in list at position i
int elementAt(List* pL, int i)
{
    return pL->data[i-1]; 
}

// Enumerate adjacent vertices of a vertex and append to the adjacency list
List neighbors(Graph* pG, int x)
{
    List L;
    makeNullList(&L);
    for (int i = 1; i <= pG->n; i++)
    {
        if (pG->A[x][i] == 1)
            // Push back neighbors of x
            appendList(&L, i); 
    }
    return L;
}

// Stack declaration
typedef struct 
{
    int data[MAX_LENGTH];
    int size;
} Stack;

// Initialize an empty Stack
void makeNullStack(Stack* pS)
{
    pS->size = 0;
}

// Check if a Stack is empty or not
int emptyStack(Stack* pS)
{
    return pS->size == 0;
}

// Push a vertex to Stack
void pushStack(Stack* pS, int x)
{
    pS->data[pS->size] = x;
    pS->size++;
}

// Retrieve a vertex in Stack
int top(Stack* pS)
{
    return pS->data[pS->size-1];
}

// Delete a vertex in Stack
void pop(Stack* pS)
{
    pS->size--;
}

// DFS a Graph, start at vertex x
List depthFirstSearch(Graph* pG, int x, int parent[])
{
    Stack S;
    makeNullStack(&S);
    pushStack(&S, x);

    parent[x] = 0;

    List DFS_L;
    makeNullList(&DFS_L);
    // Array that marks whether if a vertex is marked or not
    int mark[MAX_VERTICES]; 
    // Initialize all unmarked vertices
    for (int i = 1; i <= pG->n; i++) // Let vertex i loops thru vertices list
        mark[i] = 0;

    while (!emptyStack(&S))
    {
        int u = top(&S);
        pop(&S);
        if (mark[u] == 1)
            continue;
        // printf("Checked: %d\n", u);
        appendList(&DFS_L, u);
        mark[u] = 1;

        // Retieve neighbors vertices in L
        List L = neighbors(pG, u);
        for (int i = 1; i <= L.size; i++)
        {
            int v = elementAt(&L, i);
            // Push unchecked vertices to Stack
            if (mark[v] == 0)
            {
                pushStack(&S, v);
                parent[v] = u;
            }
        }
    }
    return DFS_L;
}

int main()
{
    Graph G;
    //freopen("DFS.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    initGraph(&G, n);

    int u, v, e;
    for (e = 1; e <= m; e++)
    {
        scanf("%d%d", &u, &v);
        addEdge(&G, u, v);
    }

    int parent[MAX_VERTICES];
    for (int i = 1; i <= G.n; i++)
    {
        parent[i] = -1;
    }

    int mark_dfs[MAX_VERTICES];
    for (int i = 1; i <= G.n; i++)
        mark_dfs[i] = 0;

    for (int i = 1; i <= G.n; i++)
    {
        // Only transverse if unmarked
        if (mark_dfs[i] == 0)
        {
            List dfs = depthFirstSearch(&G, i, parent);
            for (int j = 1; j <= dfs.size; j++)
            {
                int vertex = elementAt(&dfs, j);
                printf("%d", vertex);
                mark_dfs[vertex] = 1;
            }
        }
    }

    for (int u = 1; u <= G.n; u++)
    {
        printf("%d %d\n", u, parent[u]);
    }
    return 0;
}