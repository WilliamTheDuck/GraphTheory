#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

int circuit[MAX], csize = 0;

/* ================== HIERHOLZER ================== */
void Hierholzer(Graph* pG, Stack* pS, int s)
{
    push_stack(pS, s);

    while (!empty_stack(pS))
    {
        int u = top_stack(pS);

        // If u has unused edges, follow one
        int found = 0;
        for (int v = 1; v <= pG->n; v++)
        {
            if (pG->A[u][v] > 0)
            {
                pG->A[u][v]--;
                pG->A[v][u]--;
                push_stack(pS, v);
                found = 1;
                break;
            }
        }

        // If no unused edges, add to circuit
        if (!found)
        {
            circuit[++csize] = u;
            pop_stack(pS);
        }
    }

    // Print circuit in reverse order
    for (int i = csize; i >= 1; i--)
    {
        printf("%d", circuit[i]);
        if (i > 1) printf(" -> ");
    }
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    freopen("D:\\CODE C\\Library\\Data-EdgeList-3.txt","r",stdin);
    read_graph_edgelist(&G, 0);
    fclose(stdin);

    Stack S;
    init_stack(&S);
    int start = 1;
    Hierholzer(&G, &S, start);

    return 0;
}
