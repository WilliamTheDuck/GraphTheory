#ifndef DATA_STRUCTURE_SETUP_H
#define DATA_STRUCTURE_SETUP_H

#define MAX 200

/* ================== LIST ================== */
typedef struct
{
    int data[MAX];
    int size;
} List;

void init_list(List* pL); 
void append_list(List* pL, int x);
int element_at(List* pL, int i);
void concat_list(List* dst, List src);
void swap(int* x, int* y);
void selection_sort(List* pL);
void print_list(List* pL);
void reverse_list(List* pL);

/* ================== STACK ================== */
typedef struct 
{
    int data[MAX];
    int size;
} Stack;

void init_stack(Stack* pS); 
int empty_stack(Stack* pS);
int full_stack(Stack* pS);
void push_stack(Stack* pS, int x);
void pop_stack(Stack* pS);
int top_stack(Stack* pS);

/* ================== QUEUE ================== */
typedef struct
{
    int data[MAX];
    int front, rear;
} Queue;

void init_queue(Queue* pQ); 
int empty_queue(Queue* pQ);
int full_queue(Queue* pQ);
void push_queue(Queue* pQ, int x);
void pop_queue(Queue* pQ);
int front_queue(Queue* pQ);

/* ================== PRIORITY QUEUE ================== */
typedef struct
{
    int vertex, dist;
} Element; // Node containing vertex u & distance pi[u]
typedef struct
{
    Element data[MAX];
    int size;
} MinHeap; // Use Heap to build priority queue

void init_minheap(MinHeap* pH);
int empty_minheap(MinHeap* pH);
void swap_vertices(Element* x, Element* y);
void PushDown(MinHeap* pH, int i);
void push_minheap(MinHeap* pH, Element x);
void pop_minheap(MinHeap* pH);
Element top_minheap(MinHeap* pH);

/* ================== GRAPH (Adjacency Matrix) ================== */
typedef struct 
{
    int n, m;
    int A[MAX][MAX];
} Graph;

// Graph initialization and basic operations
void init_graph(Graph* pG, int n);
int adjacent(Graph* pG, int u, int v);
void add_edge(Graph* pG, int u, int v);
void add_edge_Directed(Graph* pG, int u, int v);

// Degree calculations
int degree(Graph* pG, int x);
int out_degree(Graph* pG, int x);
int in_degree(Graph* pG, int x);
List neighbours(Graph* pG, int x);

// Graph reading functions
void read_graph_edgelist(Graph* pG, int directed);
void read_graph_adjmatrix(Graph* pG, int directed);
void read_graph_adjlist(Graph* pG, int directed);
void read_graph_incidmatrix(Graph* pG, int directed);
void read_from_file(Graph* pG, char graph_type[], int directed);

// Graph printing functions
void print_graph(Graph* pG);
void print_degree(Graph* pG, int directed);
void print_max_degree(Graph* pG);
void print_neighbours(Graph* pG);

// Weighted graph functions
void init_weightedgraph(Graph* pG, int n);
void add_edge_weightedgraph(Graph* pG, int u, int v, int w);
void add_edge_weightedgraph_Directed(Graph* pG, int u, int v, int w);
void read_weightedgraph_edgelist(Graph* pG, int directed);

#endif /* DATA_STRUCTURE_SETUP_H */