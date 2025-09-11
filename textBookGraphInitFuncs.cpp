#include <bits/stdc++.h>

#define MaxLength 1000

typedef struct 
{
    int u, v;
} Edge;
typedef struct 
{
    int n, m; // n:vertex, m:edge
    Edge edges[MaxLength]; // edge list
} Graph; 
// struture Graph is set up in Edge List 

void initGraph(Graph* pG, int n)
{
    // Initialize a new graph with n vertexes, 0 edge (m)
    pG->n = n;
    pG->m = 0;
}

void addEdge(Graph* pG, int u, int v)
{
    // Add new edges to the existed nodes
    if (u < 1 || u > pG->n || v < 1 || v > pG->n)
        return;
    else
    {
        for (int i = 0; i <= pG->m - 1; i++)
        {
            if ((pG->edges[i].u == u && pG->edges[i].v == v)
            || (pG->edges[i].u == v && pG->edges[i].v == u))
            {
                return;
            }
        }
        // Check for buffer overflow
        if (pG->m >= MaxLength)
            return;
        // Add edge (u, v) to edge
        pG->edges[pG->m].u = u;
        pG->edges[pG->m].v = v;
        // Increase number of edges
        pG->m++;
    }
}

// Check if two vertices are adjacent
int adjacent(Graph* pG, int u, int v)
{
    for (int i = 0; i < pG->m; i++)
    {
        if ((pG->edges[i].u == u && pG->edges[i].v == v) 
            || (pG->edges[i].u == v && pG->edges[i].v == u))
        {
            return 1;
        }
    }
    return 0;
}
