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
List DFS(Graph G, int x,int p){
	List L1, L2;
	init_List(&L1);
	init_List(&L2);
	Stack S;
	init_Stack(&S);
	push_Stack(&S,x);
	int u;
	int pa=p;
	while(S.n!=0){
		u=pop_Stack(&S);
		if(mark[u]==1) continue;
		mark[u]=1;
		parent[u]=pa;
		push_List(&L1,u);
		L2=tim_lang_gieng(G,u);
		for(int i=0;i<L2.n;i++){
			if(mark[L2.A[i]]==0) {
				push_Stack(&S,L2.A[i]);
				pa=u;
			}
		}
	}
	return L1;
}
void DFS_recursion(Graph G, int u){
	if(mark[u]==1) return;
	mark[u]=1;
	parent[u]=-1;
	printf("%d \n",u);
	List L;
	L=tim_lang_gieng(G,u);
	for(int i=L.n-1;i>=0;i--){
		if(mark[L.A[i]]==0) {
			DFS_recursion(G,L.A[i]);
			parent[L.A[i]]=u;
		}
	}
}
void print_DFS(List L){
	for(int i=0;i<L.n;i++){
		printf("Duyet: %d\n",L.A[i]);
	}
}
void print_Tree(Graph G){
	for(int i=1;i<=G.n;i++){
		printf("%d %d\n",i,parent[i]);
	}
}


int main(){
	Graph G;
	readFromFile(&G,"data.txt");
	printf("Duyet DFS\n\n");
	DFS_recursion(G,1);
	printf("Dung cay\n");
	for(int i=1;i<=G.n;i++){
		printf("%d %d\n",i,parent[i]);
	}
}
