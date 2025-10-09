#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

/* ================== DEPTH FIRST SEARCH RECURSION HELPER ================== */
void DFS_Recursion_Visit(Graph* pG, int x, int mark[], int parent[], List* pL)
{
    mark[x] = 1;
    append_list(pL, x);

    List N = neighbours(pG, x);
    for (int i = 1; i <= N.size; i++)
    {
        int v = N.data[i];
        if (mark[v] == 0)
        {
            parent[v] = x;
            DFS_Recursion_Visit(pG, v, mark, parent, pL);
        }
    }
}

/* ================== DEPTH FIRST SEARCH RESURSION ================== */
List DFS_Recursion(Graph* pG, int x, int mark[], int parent[])
{
    /* Version 1:
    List L; init_list(&L);
    mark[x] = 1;
    append_list(&L, x);

    List N = neighbours(pG, x);
    for (int i = 1; i <= N.size; i++)
    {
        int v = N.data[i];
        if (mark[v] == 0)
        {
            parent[v] = x;

            // If neighbour (of x) is not visited yet
            List subL = DFS_Recursion(pG, v, mark, parent);
            // Concatenate subL to L after each function call
            for (int j = 1; j <= subL.size; j++)
                append_list(&L, subL.data[j]);
    */
           
    /* Version 2: */   
    List L; 
    init_list(&L);
    DFS_Recursion_Visit(pG, x, mark, parent, &L);
    return L;
}

/* Same result with DFS but check for neighbours in reverse tranversion
List DFS(Graph* pG, int x, int mark[], int parent[])
{
	List L; init_list(&L);
	Stack S; init_stack(&S);
	push_stack(&S, x);
	parent[x] = -1;
	
	while(!empty_stack(&S))
	{
		int u = top_stack(&S);
		pop_stack(&S);
		
		if (mark[u] == 1)
			continue;
		mark[u] = 1;
		append_list(&L, u);

		// Traverse u's neighbours
		List N = neighbours(pG, u);
        for (int i = N.size; i >= 1; i--)
        {
            int v = N.data[i];   
			// Push all neighbours of current vertex
			// Assign u to become parent of v while visiting for the first time u -> v 
			// In that way, we don't need to mention it again since it was visited
			// Notice to use this condition with DFS
			if (mark[v] == 0) 
			{   
				parent[v] = u;
				push_stack(&S, v);
			}
        }
	}
	return L;
}
*/

/* ================== MAIN ================== */
int main()
{
    Graph G;
    printf("Input file name: ");
	char s[MAX]; 
	fgets(s, MAX, stdin); // Copy path of the data.txt file
	s[strcspn(s, "\n")] ='\0'; // Remove "\n"
	freopen(s, "r", stdin);
	read_graph_edgelist(&G, 0);
	print_graph(&G);

	int x, mark[MAX], parent[MAX];
	scanf("%d", &x);
    memset(mark, 0, sizeof(mark));
    memset(parent, -1, sizeof(parent));
	List L = DFS_Recursion(&G, x, mark, parent);
	fclose(stdin);

	printf("DFS_Recursion:\n");
	print_list(&L);
    printf("Parent:\n");
	for (int i = 1; i <= L.size; i++)
	{
		int u = L.data[i];  // Retrieve vertex i-th in L
		printf("%d ", parent[u]);  // Print parent of u
	}
	printf("\n");

    return 0;
}