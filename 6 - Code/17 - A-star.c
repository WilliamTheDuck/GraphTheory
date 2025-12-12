#include <stdio.h>
#include <stdlib.h> // abs(), rand()
#include <time.h> // time(NULL), srand(time(NULL))
#include <DataStructure.h>

#define oo 9999999
int parent[MAX];
int g[MAX];   // Cost from start
int h[MAX];   // Heuristic = Dijkstra from t
int mark[MAX];

/* ================== BUILD HEURISTIC ==================*/
/* Build perfect heuristic: h[u] = shortest_path(u → goal) (Dijkstra)
   This heuristic is admissible & consistent (Perfect heuristic).
   Complexity: O((n+m) log n) with the existing MinHeap.
   Notice that, by using this way, the solution is optimal, however, it is slow since runtime is like
   we run Dijstra twice. 
   ---
   On the other hand, we can build heuristic like this too:
   Build zero heuristic: Reset h[u] = 0 for all u 
   This heuristic is admissible but weak.
   Complexity: O(n)
   Note:
       - A* degenerates into Dijkstra
       - Always gives optimal result
*/
void build_heuristic(Graph* pG, int goal)
{
    for (int u = 1; u <= pG->n; u++)
        h[u] = +oo;

    h[goal] = 0;

    MinHeap H;
    init_minheap(&H);
    Element start = {goal, 0};
    push_minheap(&H, start);

    while (!empty_minheap(&H))
    {
        Element cur = top_minheap(&H);
        pop_minheap(&H);
        int u = cur.vertex;
        int du = cur.dist;

        if (du != h[u]) continue; // Stale entry 

        // Relax neighbours (use adjacency matrix A[u][v] >= 0 in weighted graph) 
        for (int v = 1; v <= pG->n; v++)
        {
            if (pG->A[u][v] >= 0) // There is an edge u-v 
            {
                int w = pG->A[u][v];
                if (h[v] > h[u] + w)
                {
                    h[v] = h[u] + w;
                    Element e = {v, h[v]};
                    push_minheap(&H, e);
                }
            }
        }
    }
}

/* Build heuristic: h[u] = hops(u → goal) × min_edge_weight
   Method:
       - Compute min_edge_weight over all edges
       - BFS (unweighted) from goal → get hops[] (min number of edges)
       - h[u] = hops[u] * min_edge_weight
   Admissible because actual shortest path ≥ (#edges) × (min_edge_weight)
   Complexity:
       BFS: O(n + m)
*/
void build_heuristic_ver2(Graph* pG, int goal)
{
    int min_w = oo;

    // Find global minimum edge weight 
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            if (pG->A[u][v] >= 0 && pG->A[u][v] < min_w)
                min_w = pG->A[u][v];

    // BFS queue 
    Queue Q;
    init_queue(&Q);

    int hops[MAX];
    for (int u = 1; u <= pG->n; u++)
        hops[u] = oo;

    hops[goal] = 0;
    push_queue(&Q, goal);

    while (!empty_queue(&Q))
    {
        int u = front_queue(&Q);
        pop_queue(&Q);

        for (int v = 1; v <= pG->n; v++)
        {
            if (pG->A[u][v] >= 0 && hops[v] == oo)
            {
                hops[v] = hops[u] + 1;
                push_queue(&Q, v);
            }
        }
    }

    // Compute heuristic 
    for (int u = 1; u <= pG->n; u++)
    {
        if (hops[u] == oo) 
            h[u] = oo; // Unreachable 
        else               
            h[u] = hops[u] * min_w;
    }
}
/* Build heuristic (ALT-lite aka Landmark Triangle Inequality): h[u] = |dist(L, goal) - dist(L, u)|
   Method:
       Use a landmark L to estimate the distance from u → goal
       through the triangle inequality:

           h[u] = | dist(L, goal) - dist(L, u) |

       Works because any metric shortest path satisfies:
           dist(u, goal) >= |dist(L, goal) - dist(L, u)|

   Advantages:
       1. Admissible & consistent:
          - Never overestimates → A* remains optimal.
          - Triangle inequality guarantees consistency.

       2. Much stronger than Dijkstra or zero-heuristic or BFS-hop:
          - Provides a directional hint toward goal.
          - Reduces number of expanded nodes significantly.

       3. Easy to implement:
          - Only requires running Dijkstra from L once.
          - Does not require coordinates.

       4. Good scalability:
          - Works well on large weighted graphs.
          - Can use multiple landmarks to increase heuristic power:
                h[u] = max_L | dist(L, goal) - dist(L, u) |

   Disadvantages:
       1. Precomputation cost:
          - Requires 1× Dijkstra per landmark.
          - More expensive than simple heuristics for small graphs or single-query usage.

       2. Selecting a good landmark is non-trivial:
          - Poor landmark → weak heuristic.
          - Ideal: landmarks should be very far apart
            in the graph to maximize |dist(L, goal) - dist(L, u)|.

       3. Not as strong as perfect heuristic (ver1):
          - ver1 computes dist(u → goal) exactly.
          - ALT-lite is only an approximation.

       4. Benefits depend on graph structure:
          - Works best on sparse road-like networks.
          - Less effective on dense or highly connected graphs.

   Complexity:
       Precompute (run Dijkstra from landmark):
           O((n + m) log n)

       Query (one A* call):
           O((n + m) log n) but with significantly fewer node expansions.
*/
void build_heuristic_ver3(Graph* pG, int goal)
{
    // In fact, rand() % pG->n → [0 .. n-1] 
    // Then we + 1 to pick random landmark in range [1 .. pG->n] 
    int L = 1 + rand() % pG->n;

    // Run Dijkstra from landmark L
    int distL[MAX];
    for (int u = 1; u <= pG->n; u++)
        distL[u] = oo;

    distL[L] = 0;

    MinHeap H;
    init_minheap(&H);
    push_minheap(&H, (Element){L, 0});

    while (!empty_minheap(&H))
    {
        Element cur = top_minheap(&H);
        pop_minheap(&H);

        int u = cur.vertex;
        int du = cur.dist;
        if (du != distL[u]) continue;

        for (int v = 1; v <= pG->n; v++)
        {
            if (pG->A[u][v] >= 0)
            {
                int w = pG->A[u][v];
                if (distL[v] > distL[u] + w)
                {
                    distL[v] = distL[u] + w;
                    push_minheap(&H, (Element){v, distL[v]});
                }
            }
        }
    }

    // Compute heuristic 
    for (int u = 1; u <= pG->n; u++)
    {
        if (distL[u] >= oo || distL[goal] >= oo)
            h[u] = 0;   // Fallback safe heuristic 
        else
            h[u] = abs(distL[goal] - distL[u]);
    }
}

/* ================== A* SEARCH ================== */
/*
    f(u) = g(u) + h(u)
    g(u): real cost from start
    h(u): heuristic (built from Dijkstra on goal)
*/
void A_star(Graph* pG, int s, int t)
{
    for (int u = 1; u <= pG->n; u++)
    {
        g[u] = oo;
        parent[u] = -1;
        mark[u] = 0;
    }

    g[s] = 0;

    MinHeap H;
    init_minheap(&H);
    push_minheap(&H, (Element){s, g[s] + h[s]});

    while (!empty_minheap(&H))
    {
        Element top = top_minheap(&H);
        pop_minheap(&H);

        int u = top.vertex;

        if (mark[u]) continue;
        mark[u] = 1;

        if (u == t) return;

        for (int v = 1; v <= pG->n; v++)
        {
            if (pG->A[u][v] >= 0)
            {
                int w = pG->A[u][v];
                if (g[v] > g[u] + w)
                {
                    g[v] = g[u] + w;
                    parent[v] = u;

                    push_minheap(&H, (Element){v, g[v] + h[v]});
                }
            }
        }
    }
}

/* ================== PRINT PATH ================== */
void print_path(int s, int t)
{
    if (parent[t] == -1)
    {
        printf("No path.\n");
        return;
    }

    int path[MAX], cnt = 0;
    int u = t;

    while (u != -1)
    {
        path[++cnt] = u;
        u = parent[u];
    }

    for (int i = cnt; i >= 1; i--)
    {
        printf("%d", path[i]);
        if (i > 1) printf(" -> ");
    }
    printf("\n");
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    freopen("D:\\CODE C\\Library\\Data-Weighted_EdgeList-5.txt", "r", stdin);
    read_weightedgraph_edgelist(&G, 0);
    fclose(stdin);

    srand(time(NULL));   // Seed random here, use this for picking landmark randomly in build_heuristic_ver3()
    build_heuristic_ver3(&G, G.n);   // Automatic heuristic
    A_star(&G, 1, G.n);

    printf("A* shortest path:\n");
    print_path(1, G.n);
    printf("Cost = %d\n", g[G.n]);

    return 0;
}