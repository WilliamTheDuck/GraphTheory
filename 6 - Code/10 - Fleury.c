#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

/* ================== DFS ================== */
int mark[MAX];

void DFS(Graph* pG, int u)
{
    mark[u] = 1;
    for (int v = 1; v <= pG->n; v++)
        if (pG->A[u][v] > 0 && !mark[v])
            DFS(pG, v);
}

/* ================== CHECK IF EDGE IS BRIDGE ================== */
/*  Explanation:
    - Remove edge (u, v)
    - Run DFS from u
    - If v is not reachable -> the edge was a bridge
    - Restore edge
*/
int is_bridge(Graph* pG, int u, int v)
{
    // If this is the only edge from u -> must take it
    if (degree(pG, u) == 1)
        return 0; // not a bridge (must use it)

    // Remove edge temporarily
    pG->A[u][v]--;
    pG->A[v][u]--;

    // DFS from u
    for (int i = 1; i <= pG->n; i++)
        mark[i] = 0;
    DFS(pG, u);

    int result = !mark[v];  // if v cannot be reached -> it's a bridge

    // Restore edge
    pG->A[u][v]++;
    pG->A[v][u]++;

    return result;
}

/* ================== THEORY BLOCK ================== */
   /* -------------------------------------------------------------
      Eulerian Graph Conditions (Undirected)
      
      1. Eulerian Circuit exists iff:
            - Graph is connected (ignoring isolated vertices)
            - Every vertex has even degree

      2. Eulerian Path (semi-Eulerian) exists iff:
            - Graph is connected
            - Exactly 2 vertices have odd degree
              (These 2 vertices will be start and end of the path)

      3. Otherwise: no Eulerian path/circuit exists

      Mathematical reasoning:
      ------------------------------------------------------------
      The classical theorem states that in an Eulerian traversal,
      each time we enter a vertex, we must leave it using another
      unused edge. Therefore the number of times edges incident
      to that vertex are used must be even → deg(v) must be even.
      
      Exception: an Euler *path* (not a cycle) may start and end
      at vertices of odd degree because these two vertices do not
      require the symmetric enter/leave pairing.

      Thus:
           (#odd vertices == 0) → Eulerian circuit
           (#odd vertices == 2) → Eulerian path
           (#odd vertices > 2)  → impossible
   ------------------------------------------------------------- */

/* ================== CLASSIFY GRAPH AND CHOOSE START VERTEX ================== */

int classify_euler(Graph* pG, int s)
{
    if (!is_connected(pG))
        return 0;  // Not Eulerian

    int odd = 0;
    int odd1 = -1, odd2 = -1;

    for (int u = 1; u <= pG->n; u++)
    {
        if (degree(pG, u) % 2 == 1)
        {
            odd++;
            if (odd1 == -1) odd1 = u;
            else odd2 = u;
        }
    }

    if (odd == 0)
    {
        s = 1;  // any vertex with degree > 0 works
        for (int u = 1; u <= pG->n; u++)
            if (degree(pG, u) > 0)
            {
                s = u;
                break;
            }
        return 2; // Eulerian Circuit
    }
    else if (odd == 2)
    {
        s = odd1;  // start at one odd-degree vertex
        return 1;        // Eulerian Path
    }
    else
        return 0; // Not Eulerian
}

/* ================== FLEURY ================== */
void Fleury(Graph* pG, int s)
{
    int u = s;

    while (1)
    {
        // Find next valid edge
        int found = 0;
        for (int v = 1; v <= pG->n; v++)
        {
            if (pG->A[u][v] > 0)
            {
                // Check bridge
                if (!is_bridge(pG, u, v))
                {
                    printf("%d -> %d\n", u, v);

                    // Use edge
                    pG->A[u][v]--;
                    pG->A[v][u]--;

                    u = v;
                    found = 1;
                    break;
                }
            }
        }

        // If cannot find non-bridge, take ANY edge (final step)
        if (!found)
        {
            for (int v = 1; v <= pG->n; v++)
                if (pG->A[u][v] > 0)
                {
                    printf("%d -> %d\n", u, v);
                    pG->A[u][v]--;
                    pG->A[v][u]--;
                    u = v;
                    found = 1;
                    break;
                }
        }

        if (!found) break; // no more edges
    }
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    freopen("D:\\CODE C\\Library\\Data-EdgeList-3.txt","r",stdin);
    read_graph_edgelist(&G, 0);
    fclose(stdin);

    int start = 1; // or find an odd-degree vertex for Euler path
    Fleury(&G, start);

    return 0;
}
