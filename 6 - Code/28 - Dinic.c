#include <stdio.h>
#include <string.h>

#define MAX 200
#define oo 9999999

/* ================== QUEUE ================== */
typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

void init_queue(Queue* pQ)
{
    pQ->front = pQ->rear = -1;
}
int empty_queue(Queue* pQ)
{
    return pQ->front == -1;
}
int full_queue(Queue* pQ)
{
    return pQ->front == (pQ->rear + 1) % MAX;   
}
void push_queue(Queue* pQ, int x)
{
    if (full_queue(pQ))    
        return;
    if (pQ->front == -1)
    {
        pQ->front = pQ->rear = 0;
        pQ->data[pQ->rear] = x;
        return;
    }
    pQ->rear = (pQ->rear + 1) % MAX;
    pQ->data[pQ->rear] = x;
}
void pop_queue(Queue* pQ)
{
    if (empty_queue(pQ)) return;
    if (pQ->front == pQ->rear)
    {
        init_queue(pQ);
        return;
    }
    pQ->front = (pQ->front + 1) % MAX;
}
int front_queue(Queue* pQ)
{
    return pQ->data[pQ->front];
}

/* ================== NETWORK ================== */
typedef struct {
    int C[MAX][MAX]; // Capacity
    int F[MAX][MAX]; // Flow
    int n, m;
} Graph;

// Level graph & pointer
int level[MAX];
int nextEdge[MAX];

/* ================== INIT ================== */
void init_weightedgraph(Graph* pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            pG->C[u][v] = -1;
}

void init_flow(Graph* pG)
{
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            pG->F[u][v] = 0;
}

/* ================== BFS BUILD LEVEL GRAPH ================== */
/*
    BFS -> Level Graph:
    - If F[u][v] < C[u][v] then edge (u,v) has residual capacity.
    - level[v] = level[u] + 1.
*/
int BFS(Graph* pG, int s, int t)
{
    for (int i = 1; i <= pG->n; i++)
        level[i] = -1;

    Queue Q;
    init_queue(&Q);

    level[s] = 0;
    push_queue(&Q, s);

    while (!empty_queue(&Q))
    {
        int u = front_queue(&Q);
        pop_queue(&Q);

        for (int v = 1; v <= pG->n; v++)
        {
            if (level[v] < 0 && pG->F[u][v] < pG->C[u][v])
            {
                level[v] = level[u] + 1;
                push_queue(&Q, v);
            }
        }
    }
    return (level[t] >= 0);
}

/* ================== DFS SEND FLOW ================== */
/*
    DFS to find augmenting paths (in blocking flow):
    - Follows the level graph (only go to vertices with level + 1).
    - nextEdge[u] helps skip edges that were already checked, improving efficiency.
*/
int DFS(Graph* pG, int u, int t, int pushed)
{
    if (u == t)
        return pushed;

    /* This is NOT an error.
    It is the standard optimization in Dinic:
    nextEdge[u] remembers the next edge to try during DFS
    so you don’t re-scan edges from the beginning every time.
    */
    for (; nextEdge[u] <= pG->n; nextEdge[u]++)
    {
        int v = nextEdge[u];

        if (level[v] == level[u] + 1 && pG->F[u][v] < pG->C[u][v])
        {
            int available = pG->C[u][v] - pG->F[u][v];
            int send = DFS(pG, v, t, pushed < available ? pushed : available);

            if (send > 0)
            {
                pG->F[u][v] += send;
                pG->F[v][u] -= send;
                return send;
            }
        }
    }
    return 0;
}

/* ================== DINIC ================== */
/*
    1. BFS -> Level graph
    2. DFS pushes blocking flow
    3. Repeat until BFS can no longer reach t.
*/
void Dinic(Graph* pG, int s, int t, int* max_flow)
{
    init_flow(pG);
    *max_flow = 0;

    while (BFS(pG, s, t))
    {
        for (int u = 1; u <= pG->n; u++)
            nextEdge[u] = 1;

        while (1)
        {
            int f = DFS(pG, s, t, oo);
            if (f == 0)
                break;
            (*max_flow) += f;
        }
    }
}

/* ================== MAIN ================== */
int main()
{
    Graph G;

    /* ------------------ FIND THE MAXIMUM FLOW IN THE NETWORK ------------------ */
    {
        int n, m, u, v, e, c, max_flow = 0;

        freopen("D:\\CODE C\\Library\\Data-Weighted_EdgeList-1.txt", "r", stdin);
        scanf("%d%d", &n, &m);

        init_weightedgraph(&G, n);

        for (e = 1; e <= m; e++)
        {
            scanf("%d%d%d", &u, &v, &c);
            G.C[u][v] = c;
        }
        fclose(stdin);

        Dinic(&G, 1, n, &max_flow);

        printf("Max flow: %d\n", max_flow);
    }

    return 0;
}
