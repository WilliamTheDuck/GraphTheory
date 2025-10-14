#include <stdio.h>
#include <string.h>
#include <DataStructure.h>

/* ================== BREADTH FIRST SEARCH ================== */
List BFS(Graph* pG, int x, int mark[], int parent[])
{
	List L; init_list(&L);
	Queue Q; init_queue(&Q);
	push_queue(&Q, x);
	parent[x] = -1;
	
	while(!empty_queue(&Q))
	{
		int u = front_queue(&Q);
		pop_queue(&Q);
		
		if (mark[u] == 1) 
			continue;
		mark[u] = 1;
		append_list(&L, u);
		
		// Traverse u's neighbours
        List N = neighbours(pG, u);
        for (int i = 1; i <= N.size; i++)
        {
            int v = N.data[i];   
			// Push all neighbours of current vertex
			// Assign u to become parent of v while visiting for the first time u -> v 
			// In that way, we don't need to mention it again since it was visited
			// Notice to use this condition with BFS (Still can use mark == 0 but use parent == -1 is more optimized)
			if (parent[v] == -1 && v != x) 
			{   
				parent[v] = u;
				push_queue(&Q, v);
			}
        }
	}
	return L;
}

/* ================== MAIN ================== */
int main()
{
	Graph G;
	printf("Input file name: ");
	char s[MAX]; 
	fgets(s, MAX, stdin); // Copy path of the data.txt file
	s[strcspn(s, "\n")] = '\0'; // Remove "\n"
	freopen(s, "r", stdin);
	read_graph_edgelist(&G, 0);
	print_graph(&G);

	int x, mark[MAX], parent[MAX];
	scanf("%d", &x);
	memset(mark, 0, sizeof(mark));
	memset(parent, -1, sizeof(parent));
	List L = BFS(&G, x, mark, parent);
	fclose(stdin);

	printf("BFS:\n");
	print_list(&L);
	
	printf("Parent:\n");
	for (int i = 1; i <= L.size; i++)
	{
		int u = L.data[i];  // Retrieve vertex i-th in L
		printf("%d ", parent[u]);  // Print parent of u
	}
	printf("\n");

	// Paste this to terminal in order to run code
	// gcc BFS.c DataStructure.c -o BFS.exe 
	// .\BFS.exe
	return 0;
}