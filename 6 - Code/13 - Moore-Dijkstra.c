#include <stdio.h>
#include <DataStructure.h>

/* ================== MOORE-DIJKSTRA ================== */
#define oo 9999999
int mark[MAX];
int pi[MAX];
int parent[MAX];

void MooreDijkstra(Graph* pG, int s) // O(n^2) with n is number of vertices 
{
    int u;
    // Initialize mark[], pi[]
    for (int i = 1; i <= pG->n; i++)
    {
        mark[i] = 0;
        pi[i] = oo;
    }
    pi[s] = 0; parent[s] = -1;

    // Transverse n-1 times
    for (int k = 1; k <= pG->n - 1; k++)
    {
        int min_pi = oo;

        // 1. Find vertex u that has mark[u] == 0 and has smallest pi[u]
        for (int j = 1; j <= pG->n; j++)
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                min_pi = pi[j];
                u = j;
            }

        // 2. Mark u
        mark[u] = 1;

        // 3. Update pi[v] and parent[v] with v's are neighbours of u
        for (int v = 1; v <= pG->n; v++)
            if (pG->A[u][v] != -1 && mark[v] == 0 && (pi[v] > pi[u] + pG->A[u][v]))
            {
                pi[v] = pi[u] + pG->A[u][v];
                parent[v] = u;
            }
    }
}

/* ================== MOORE - DIJKSTRA UPGRADE ================== */
void MooreDijkstra_PriorityQueue(Graph* pG, int s) // O((n+m)logn)
{
    for (int u = 1; u <= pG->n; u++)
    {
        parent[u] = -1;
        mark[u] = 0;
        pi[u] = oo;
    }
    pi[s] = 0;

    MinHeap H;
    init_minheap(&H);
    Element start = {s, 0};
    push_minheap(&H, start);

    // Instead of find smallest pi[u] through out the entire graph
    // Use priority queue for optimization (quite like BFS and DFS)
    while (!empty_minheap(&H))
    {
        Element min = top_minheap(&H);
        pop_minheap(&H);

        int u = min.vertex;
        // Avoid overlap stale entries pushing multiple vertices to heap
        if (min.dist != pi[u])
            continue;
        if (mark[u] != 0)
            continue;
        mark[u] = 1;

        for (int v = 1; v <= pG->n; v++)
            if (pG->A[u][v] >= 0 && mark[v] == 0)
            {
                int w = pG->A[u][v];
                if (pi[v] > pi[u] + w)
                {
                    pi[v] = pi[u] + w;
                    parent[v] = u;

                    Element e = {v, pi[v]};
                    push_minheap(&H, e); // Push neighbours to heap
                }
            }
    }
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
}
void print_shortestpath_ver2(Graph* pG, int s, int t)
{
	int path[pG->n];
	int count = 0; // Number of vertices of the path
    int current = t; 
    // Trace back from t (current) to its ancestors (s -> .. -> t)
	while (current != -1)
    {
        path[count] = current;
        count++;
        current = parent[current]; // Uppdate current to its parent (Trace back & add to path[])
	}
    // Print backwards all vertices in path[], with root/start (s) is the last element & goal (t) is the first element
	for (int i = count-1; i >= 0; i--)
    {
		printf("%d", path[i]);
		if (i > 0) // Stop printing "->" as i reaches vertex t
            printf(" -> ");
	}
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    freopen("D:\\CODE C\\Library\\Data-Weighted_EdgeList-3.txt", "r", stdin);
        read_weightedgraph_edgelist(&G, 0);
        int s, t; scanf("%d%d", &s, &t);
    fclose(stdin);

    MooreDijkstra_PriorityQueue(&G, s);
    
    print_pi_parent(&G);
    print_shortestpath_ver2(&G, s, t);
    return 0;
}