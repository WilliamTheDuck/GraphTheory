#include <stdio.h>
#include <DataStructure.h>

/* ================== MOORE-DIJKSTRA ================== */
#define oo 9999999
int mark[MAX];
int pi[MAX];
int parent[MAX];

void MooreDijkstra(Graph* pG, int x) // O(n^2)
{
    int u, v;
    // Initialize mark[], pi[]
    for (int i = 1; i <= pG->n; i++)
    {
        mark[i] = 0;
        pi[i] = oo;
    }
    pi[x] = 0; parent[x] = -1;

    // Transverse n-1 times
    for (int k = 1; k <= pG->n - 1; k++)
    {
        int min_pi = oo;

        // 1. Find vertex u that has mark[u] == 0 and has smallest pi[u]
        for (int x = 1; x <= pG->n; x++)
            if (mark[x] == 0 && pi[x] < min_pi)
            {
                min_pi = pi[x];
                u = x;
            }

        // 2. Mark u
        mark[u] = 1;

        // 3. Update pi[x] and parent[x] with x's are neighbours of u
        for (int x = 1; x <= pG->n; x++)
            if (pG->A[u][x] != -1 && mark[x] == 0 && (pi[x] > pi[u] + pG->A[u][x]))
            {
                pi[x] = pi[u] + pG->A[u][x];
                parent[x] = u;
            }
    }
}

/* ================== ROBOT MAZE ================== */
int di[] = {-1, 1, 0, 0}; // Move left, right
int dj[] = {0, 0, -1, 1}; // Move up, down
int N, M;

void read_maze(Graph* pG)
{
    freopen("D:\\CODE C\\Library\\Data-Robot_Maze-1.txt", "r", stdin);
        scanf("%d%d", &N, &M);
        int maze[N][M];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                scanf("%d", &maze[i][j]);
            }

        init_weightedgraph(pG, N*M);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                int ii, jj;
                int u = (i*M + j) + 1;
                int v;
                for (int k = 0; k < 4; k++)
                {
                    ii = i + di[k];
                    jj = j + dj[k];
                    
                    // Check if (ii;jj) is in maze
                    if (ii >= 0 && ii < N && jj >= 0 && jj < M)
                    {
                        v = (ii*M + jj) + 1;
                        add_edge_weightedgraph_Directed(pG, u, v, maze[ii][jj]);
                    }
                }
            }
    fclose(stdin);
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    read_maze(&G);

    MooreDijkstra(&G, 1);

    printf("%d", pi[G.n]);

    return 0;
}