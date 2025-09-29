#include <stdio.h>
#include <string.h>
#include <DataStructureSetUp.h>

/* ================== DEPTH FIRST SEARCH ================== */
List DFS(Graph* pG, int x, int mark[], int parent[])
{
	List L; init_list(&L);
	Stack S; init_stack(&S);
	push_stack(&S, x);
	parent[x] = -1;
	for (int i = 1; i <= pG->n; i++)
		mark[i] = 0;
	
	while(!empty_stack(&S))
	{
		int u = top(&S);
		pop_stack(&S);
		
		if (mark[u] != 0)
			continue;
		append_list(&L, u);
		mark[u] = 1;

		for (int v = 1; v <= pG->n; v++)
		{
			if (adjacent(pG, u, v))
			{
				push_stack(&S, v);
				parent[v] = u;
			}
		}
	}
	return L;
}

/* ================== MAIN ================== */
int main()
{
	Graph G;
	char s[MAX]; 
	fgets(s, MAX, stdin); // Copy path of the data.txt file
	s[strcspn(s, "\n")] ='\0'; // Remove "\n"
	freopen(s, "r", stdin);
	read_graph_edgelist(&G, 0);
	print_graph(&G);
	print_degree(&G, 0);

	int x, mark[MAX], parent[MAX];
	scanf("%d", &x);
	List L = DFS(&G, x, mark, parent);
	fclose(stdin);
	printf("DFS:\n");
	print_list(&L);

	// Paste this to terminal in order to run code
	// gcc DFS.c DataStructureSetUp.c -o DFS.exe 
	// .\DFS.exe
	return 0;
}