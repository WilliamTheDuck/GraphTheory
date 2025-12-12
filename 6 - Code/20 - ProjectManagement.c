#include <stdio.h>
#include <string.h>
#include <stdlib.h> // atoi(), strtol(),...
#include <math.h> // fmax(), fmin(),...
#include <DataStructure.h>

#define oo 9999999
int mark[MAX], d[MAX];

/* ================== TOPO SORT ================== */
void dfs(Graph* pG, int u, List* pL)
{
    mark[u] = 1;
    // Forward and backward tranversing still gets the same logic topo list but different element order
    // In this forward iteration, we check potential neighbors from v=1 to v=n
    // E.g. Graph:
    //     1 -> 2 -> 4 -> 5
    //     1 -> 3 -> 5
    //     1 -> 5
    // dfs(1)
    //     dfs(2)
    //         dfs(4)
    //             dfs(5)
    //             append(5) [5]
    //         append(4) [5,4]
    //     append(2) [5,4,2]
    //     dfs(3)
    //         dfs(5) (skip)
    //     append(3) [5,4,2,3]
    //     dfs(5) (skip)
    // append(1) [5,4,2,3,1]
    // topo_list = [5,4,2,3,1]
    // => reverse(topo_list) = [1,3,2,4,5] 
    for (int v = 1; v <= pG->n; v++) 
        if (pG->A[u][v] != 0 && mark[v] == 0)
            dfs(pG, v, pL);
    
    append_list(pL, u);
}
void topo_sort(Graph* pG, List* pL)
{
    init_list(pL);
    for (int u = 1; u <= pG->n; u++)
        mark[u] = 0;
    
    for (int u = 1; u <= pG->n; u++)
        if (mark[u] == 0)
            dfs(pG, u, pL);

    reverse_list(pL);
}

/* ================== PROJECT MANAGEMENT ================== */
void read_project_management(Graph* pG, int* n, int* alpha, int* beta)
{
    freopen("D:\\CODE C\\Library\\Data-ProjectManagement-1.txt", "r", stdin);
    
    scanf("%d", n);
    // Create n+2 vertices graph (including alpha & beta)
    init_graph(pG, *n + 2);
    *alpha = *n + 1;
    *beta = *n + 2;
    d[*alpha] = 0;
    
    // Read list of tasks
    for (int u = 1; u <= *n; u++)
    {
        scanf("%d", &d[u]);
        int x;
        do {
            // Read vertices that are linked with u (x -> u)
            scanf("%d", &x);
            if (x > 0)
                add_edge_Directed(pG, x, u);
        } while (x > 0);
    }
    
    fclose(stdin);
}
void read_project_management_ver2(Graph* pG, int* n, int* alpha, int* beta)
{
    freopen("D:\\CODE C\\Library\\Data-ProjectManagement-1.txt", "r", stdin);
    
    // Be careful with scanf() and fgets() combination!
    // 1. Option 1: %*c to read \n in the buffer (skip \n in buffer -> fgets() won't read \n that makes errors)
        scanf("%d%*c", n);
    // 2. Option 2: Read each line using fgets() -> Synchronize with lines below
        // char line[MAX];
        // fgets(line, sizeof(line), stdin);
        // *n = atoi(line);

    // Create n+2 vertices graph (including alpha & beta)
    init_graph(pG, *n + 2);
    *alpha = *n + 1;
    *beta = *n + 2;
    d[*alpha] = 0;

    // Read list of tasks (A more universal approach)
    for (int u = 1; u <= *n; u++)
    {
        char line[MAX];
        fgets(line, sizeof(line), stdin); // Read each line

        char* token = strtok(line, " \t\n"); // Delimiters are " ", "\t", "\n"
        d[u] = atoi(token); // Duration of task u is the first token

        // Tokenize each number in each line
        token = strtok(NULL, " \t\n");
        while (token != NULL) 
        {
            // strtol() is the same as atoi(), use this in case the IDE warns 
            int x = (int) strtol(token, NULL, 10); 
            // Stop when reach 0 at the end of each line, if there's no zeros at the end just remove this line
            if (x == 0) break;
            add_edge_Directed(pG, x, u);
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(stdin);
}

void add_source_sink(Graph* pG, int alpha, int beta)
{
    int u, x, v;
    
    // Link alpha to vertices with in-degree = 0
    for (u = 1; u <= pG->n; u++)
    {
        int in_deg = 0;
        for (x = 1; x <= pG->n; x++)
            if (pG->A[x][u] > 0)
                in_deg++;
        if (in_deg == 0)
            add_edge_Directed(pG, alpha, u);
    }
    
    // Link vertices with out-degree = 0 to beta
    for (u = 1; u <= pG->n; u++)
    {
        int out_deg = 0;
        for (v = 1; v <= pG->n; v++)
            if (pG->A[u][v] > 0)
                out_deg++;
        if (out_deg == 0)
            add_edge_Directed(pG, u, beta);
    }
}

void earliest_start(Graph* pG, List* pL, int alpha, int* t)
{
    int j, u, x;
    t[alpha] = 0;
    
    for (j = 2; j <= pL->size; j++)
    {
        u = element_at(pL, j);
        t[u] = -oo;
        for (x = 1; x <= pG->n; x++)
            if (pG->A[x][u] > 0)
                t[u] = fmax(t[u], t[x] + d[x]);
    }
    // for (j = 2; j <= L.size; j++)
    // {
    //     int u = element_at(&L, j);
    //     int max_t = -oo;
    //     for (x = 1; x <= G.n; x++)
    //         if (G.A[x][u] > 0)  
    //             if (t[x] + d[x] > max_t)
    //                 max_t = d[x] + t[x];
    //     t[u] = max_t;
    // }
}

void latest_start(Graph* pG, List* pL, int beta, int* t, int* T)
{
    int j, u, v;
    T[beta] = t[beta];
    
    for (j = pL->size - 1; j >= 1; j--)
    {
        u = element_at(pL, j);
        T[u] = +oo;
        for (v = 1; v <= pG->n; v++)
            if (pG->A[u][v] > 0)
                T[u] = fmin(T[u], T[v] - d[u]);
    }
}

void print_t_T(int n, int* t, int* T)
{
    for (int u = 1; u <= n; u++)
        printf("%d %d\n", t[u], T[u]);
}

/* ================== MAIN ================== */
int main()
{
    Graph G;
    List L;
    int n, alpha, beta;
    int t[MAX], T[MAX];
    
    // 1. Read graph
    read_project_management_ver2(&G, &n, &alpha, &beta);
    
    // 2-3. Add source and sink
    add_source_sink(&G, alpha, beta);
    
    // 4. Topological sort
    topo_sort(&G, &L);
    
    // 5. Calculate earliest start times
    earliest_start(&G, &L, alpha, t);
    
    // 6. Calculate latest start times
    latest_start(&G, &L, beta, t, T);
    
    // 7. Print results
    print_t_T(n, t, T);
    
    return 0;
}