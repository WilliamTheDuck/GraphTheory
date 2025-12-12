#include <stdio.h>
#include <math.h>

#define MAX 200

/* ================== QUEUE ================== */
typedef struct
{
    int data[MAX];
    int front, rear;
} Queue;

void init_queue(Queue* pQ)
{
    pQ->front = -1;
    pQ->rear = -1;
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
        pQ->front = 0;
        pQ->rear = 0;
        pQ->data[pQ->rear] = x;
        return;
    }
    pQ->rear = (pQ->rear + 1) % MAX;
    pQ->data[pQ->rear] = x;
}
void pop_queue(Queue* pQ)
{
    if (empty_queue(pQ))
        return;
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
typedef struct 
{
    int C[MAX][MAX];
    int F[MAX][MAX];
    int n;
} Graph;
typedef struct 
{
    int dir; // +1: +, -1: -, 0: no label
    int p; // Predecessor 
    int sigma; // Augmenting flow
} Label;
Label labels[MAX]; // Labels of vertices

/* ================== INIT ================== */
void init_flow(Graph* pG)
{
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            pG->F[u][v] = 0;
}
void init_weightedgraph(Graph* pG, int n)
{
    pG->n = n;
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            pG->C[u][v] = -1;
}

/* ================== FORD - FULKERSON ================== */
#define oo 9999999

void FordFulkerson(Graph* pG, int s, int t, int* max_flow)
{
    // Init flow
    init_flow(pG);

    // Loop
    Queue Q;
    do {
    // I. Delete label & label vertex s
        // 1.1. Delete all old label
        for (int u = 1; u <= pG->n; u++)
            labels[u].dir = 0;
        // 1.2. Label s: (+, s, oo)
        labels[s].dir = +1;
        labels[s].p = s;
        labels[s].sigma = oo;
        // 1.3. Init empty Q & push s to Q
        init_queue(&Q);
        push_queue(&Q, s);

    // II. Repeat labelling vertices -> Find augmenting path
        int found = 0;
        while (!empty_queue(&Q))
        {
            // 2.1. Pop & take a vertex u in Q
            int u = front_queue(&Q); 
            pop_queue(&Q);
           
            for (int v = 1; v <= pG->n; v++)
            {
                 // 2.2. Consider assigning labels to neighbours of u: directed edge (u -> v)
                if (pG->C[u][v] != 0 && labels[v].dir == 0 && pG->F[u][v] < pG->C[u][v])
                {
                    labels[v].dir = +1; // Directed edge
                    labels[v].p = u;
                    labels[v].sigma = fmin(labels[u].sigma, pG->C[u][v] - pG->F[u][v]);

                    push_queue(&Q, v);
                }
                // 2.3. Consider assigning labels for vertices neighbouring u: incoming edge (v -> u)
                if (pG->C[v][u] != 0 && labels[v].dir == 0 && pG->F[v][u] > 0)
                {
                    labels[v].dir = -1; // Incoming edge
                    labels[v].p = u;
                    labels[v].sigma = fmin(labels[u].sigma, pG->F[v][u]);

                    push_queue(&Q, v);
                }
            }
                
            // 2.4. If t is labelled -> Find augmenting path
            if (labels[t].dir != 0)
            {
                found = 1;
                break;
            }
        }
    // III. Augment flow
        if (found == 1)
        {
            int sigma = labels[t].sigma; // Residual capacity
            // 3.1. Update flow of edges on augmenting path
            int u = t;
            while (u != s)
            {
                int p = labels[u].p;
                if (labels[u].dir > 0) // Increase path
                    pG->F[p][u] += sigma;
                else // Decrease path
                    pG->F[u][p] -= sigma;
                u = p;
            }
            // 3.2. Augment flow
            *max_flow += sigma;
        }
        else
            break; 
    } while (1);
}

/* ================== VALID STREAM ================== */
int sum_in_u(Graph* pG, int x)
{
    int sum_in = 0;
    for (int u = 1; u <= pG->n; u++)
        sum_in += pG->F[u][x];
    return sum_in;
}
int sum_out_u(Graph* pG, int x)
{
    int sum_out = 0;
    for (int u = 1; u <= pG->n; u++)
        sum_out += pG->F[x][u];
    return sum_out;
}
int valid_stream(Graph* pG)
{
    // 1. 0 <= F[u][v] <= C[u][v], for all edges (u,v)
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            if (pG->F[u][v] != 0 && pG->C[u][v] != -1)
                if (pG->F[u][v] < 0 || pG->F[u][v] > pG->C[u][v])
                    return 0;
                
    // 2. Total flow out of vertex s = Total flow into vertex t
    int sum_s = 0, sum_t = 0;
    for (int v = 1; v <= pG->n; v++)
        sum_s += pG->F[1][v]; 
    for (int u = 1; u <= pG->n; u++)
        sum_t += pG->F[u][pG->n]; 
    if (sum_s != sum_t)
        return 0;

    // 3. Total flow into vertex u = Total flow out of u (u ≤ s and u ≤ t)
    for (int u = 2; u <= pG->n-1; u++)
    {
        int sum_in = sum_in_u(pG, u);
        int sum_out = sum_out_u(pG, u);
        if (sum_in != sum_out)
            return 0;
    }
    
    return 1;
}

/* ================== MAIN ================== */
int main()
{
    Graph G;

    /* ------------------ FIND THE MAXIMUM FLOW IN THE NETWORK ------------------ */
 {   int n, m, u, v, e, c, max_flow = 0;
    freopen("D:\\CODE C\\Library\\Data-Weighted_EdgeList-1.txt", "r", stdin);
        scanf("%d%d", &n, &m);
        init_weightedgraph(&G, n);
        for (e = 1; e <= m; e++)
        {
            scanf("%d%d%d", &u, &v, &c);
            G.C[u][v] = c;
        }
    fclose(stdin);

    FordFulkerson(&G, 1, n, &max_flow);

    printf("Max flow: %d\n", max_flow);
    printf("S: ");
    for (u = 1; u <= n; u++)
        if (labels[u].dir != 0)
            printf("%d ", u);
    printf("\n");
    printf("T: ");
    for (u = 1; u <= n; u++)
        if (labels[u].dir == 0)
            printf("%d ", u);
    printf("\n");
}

    /* ------------------ CHECKING FOR VALID STREAMS ------------------ */
 {   int n, m, u, v, e, c, f;
    freopen("D:\\CODE C\\Library\\Data-Flow_Weighted_EdgeList-1.txt", "r", stdin);
        scanf("%d%d", &n, &m);
        init_weightedgraph(&G, n);
        for (e = 1; e <= m; e++)
        {
            scanf("%d%d%d%d", &u, &v, &c, &f);
            G.C[u][v] = c;
            G.F[u][v] = f;
        }
    fclose(stdin);

    if (valid_stream(&G))
        printf("YES");
    else
        printf("NO");
}

    return 0;
}