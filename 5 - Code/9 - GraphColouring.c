#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
int mark[MAX]; 
int parent[MAX];
int has_circle; 

#define BLUE 1
#define RED 2
int conflict;

/* ================== 3 COLOURS ================== */
void three_colorize(Graph* pG, int u, int* has_circle, int parent) 
{
    mark[u] = GRAY;
    for (int v = 1; v <= pG->n; v++)
        if (adjacent(pG, u, v)) 
        {
            if (v == parent)
                continue;
            else if (mark[v] == WHITE) // If not painted yet -> Recursively paint it
                three_colorize(pG, v, has_circle, u); 
            else if (mark[v] == GRAY) // If meet a GRAY node -> Found a circle
            {
                *(has_circle) = 1; 
                return;
            }
        }
    mark[u] = BLACK;
}

/* ================== BIPARTITE GRAPH ================== */
void bipartite_colorize(Graph *pG, int u, int color) 
{
    mark[u] = color;
    for (int v = 1; v <= pG->n; v++)
        if (adjacent(pG, u, v)) 
        {
            if (mark[v] == WHITE) // Paint white node (v) with inverted colour of its neighbour (u)
                bipartite_colorize(pG, v, 3 - color); 
            else if (mark[v] == mark[u]) // If same color nodes meet as neighbours -> Conflict
                conflict = 1; 
        }
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    read_graph_edgelist(&G, 0);
    memset(mark, 0, sizeof(mark));
    memset(parent, -1, sizeof(parent));

    for (int u = 1; u <= G.n; u++)
        if (mark[u] == WHITE)
        {
            three_colorize(&G, u, has_circle, parent);
            if (has_circle)
                break;
        }

    if (has_circle) printf("NO");
    else printf("YES");
    
    return 0;
}