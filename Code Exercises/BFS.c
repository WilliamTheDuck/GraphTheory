#include <stdio.h>

#define maxlength 200

typedef struct {
	int A[maxlength][maxlength];
	int n;
}Graph;
typedef struct {
	int A[maxlength];
	int n;
}List;
typedef List Stack;
typedef List Queue;
int mark[maxlength];
int parent[maxlength];
void init_Graph (Graph *G, int n){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			G->A[i][j]=0;
		}
	}
	G->n=n;
}
void add_edge(Graph *G, int x, int y){
	if(x==y) G->A[x][x]=1; 
	else {
		G->A[x][y]+=1;
	    G->A[y][x]+=1;
	}
}
void readFromFile(Graph *G, char tenfile[]){
	freopen(tenfile,"r",stdin);
	int a,b,c,d;
	scanf("%d%d",&a,&b);
	init_Graph(G,a);
	for(int i=0;i<b;i++){
		scanf("%d%d",&c,&d);
		add_edge(G,c,d);
	}
}
void print_Graph (Graph G){
	for(int i=1;i<=G.n;i++){
		for(int j=1;j<=G.n;j++){
			printf("%d ",G.A[i][j]);
		}
		printf("\n");
	}
}
void init_List(List *L){
	L->n=0;
}
void push_List(List *L, int x){
	L->A[L->n]=x;
	L->n++;
}
void print_List(List L){
	for(int i=0;i<L.n;i++){
		printf("%d ",L.A[i]);
	}
}
int degree(Graph G, int x){
	int deg=0;
	for(int i=1;i<=G.n;i++){
		if(G.A[x][i]!=0&&x!=i) deg+=G.A[x][i];
		else if(G.A[x][i]!=0&&x==i) deg+=G.A[x][i]*2;
	}
	return deg;
}
void init_Stack(Stack *S){
	S->n=0;
}
void push_Stack(Stack *S, int x){
	if(S->n<=maxlength){
		S->A[S->n]=x;
		S->n++;
	}
}
int pop_Stack(Stack *S){
	if(S->n!=0){
		int a=S->n-1;
		S->n--;
		return S->A[a];
	}
}
List tim_lang_gieng(Graph G, int x){
	List L;
	init_List(&L);
	for(int i=1;i<=G.n;i++){
		if(G.A[x][i]!=0){
			push_List(&L,i);
		}
	}
	return L;
}
void init_Queue(Queue *Q){
	Q->n=0;
}
void push_Queue(Queue *Q, int x){
	if(Q->n<maxlength){
		Q->A[Q->n]=x;
	    Q->n++;
	}else {
		printf("Hang day");
	}
}
int pop_Queue(Queue *Q){
	int a=Q->A[0];
	for(int i=0;i<Q->n-1;i++){
		Q->A[i]=Q->A[i+1];
	}
	Q->n--;
	return a;
}
List BFS(Graph G, int x){
	List L1, L2;
	init_List(&L1);
	init_List(&L2);
	Queue Q;
	init_Queue(&Q);
	int u;
	push_Queue(&Q,x);
	parent[x]=-1;
	while(Q.n!=0){
		u=pop_Queue(&Q);
		if(mark[u]==1) continue;
		mark[u]=1;
		push_List(&L1,u);
		L2=tim_lang_gieng(G,u);
		for(int i=0;i<L2.n;i++){
			if(mark[L2.A[i]]==0) {
				push_Queue(&Q,L2.A[i]);
				if(parent[L2.A[i]]==0){
					parent[L2.A[i]]=u;
				}
			}
		}
	}
	return L1;
}
void print_bfs(List L){
	for(int i=0;i<L.n;i++){
		printf("Duyet: %d\n",L.A[i]);
	}
}
void printf_Tree(Graph G){
	for(int i=1;i<=G.n;i++){
		printf("%d %d\n",i,parent[i]);
	}
}


int main(){
	Graph G;
	readFromFile(&G,"data.txt");
	for(int i=1;i<=G.n;i++) {
		mark[i]=0;
		parent[i]=0;
	}
	List L2;
	printf("\nDo thi da nhap la:\n");
	print_Graph(G);
	printf("\nThu tu duyet:\n");
	for(int i=1;i<=G.n;i++){
		if(mark[i]==0) {
			L2=BFS(G,i);
			print_bfs(L2);
		}
	}
	printf("\ndung cay\n");
	printf_Tree(G);
	
}
