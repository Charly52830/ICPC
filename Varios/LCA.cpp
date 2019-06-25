/**
*	Lowest Common Ancestor in O(n logn)
*	Entrada: un DAG en una lista de adyacencia v.
*	Salida: estructura preprocesada para resolver distintas preguntas.
*	Indexado desde 1.
*	MAXLOG: potencia de 2 más grande posible de un camino.
*
*	Author: Carlos Daniel Ruvalcaba Serrano.
*/

#include<vector>
#include<iostream>
#define MAXLOG 18
using namespace std;

vector<vector<int> > v;

int dept[100010];
int M[MAXLOG][100010];

void dfs(int n,int p,int d) {
	dept[n]=d;
	M[0][n]=p;
	for(int i:v[n])
		if(i!=p)
			dfs(i,n,d+1);
}

int F(int n,int k) { //k Ancestor	O(log n)
	for(int i=0;i<MAXLOG;i++)
		if(k&(1<<i))
			n=M[i][n];
	return n;
}

int LCA(int a,int b){ //Lowest Common Ancestor.	O(log n)
	if(dept[a]<dept[b])
		b=F(b,dept[b]-dept[a]);
	if(dept[b]<dept[a])
		a=F(a,dept[a]-dept[b]);
	for(int i=MAXLOG-1;i>=0;i--) if(M[i][a]!=M[i][b]) {
		a=M[i][a];
		b=M[i][b];
	}
	return M[0][a];
}

bool f(int a,int b) { //Wheter a is ancestor of b O(log n)
	if(dept[b]<dept[a])
		return 0;
	return F(b,dept[b]-dept[a])==a;
}

int main() {
	int n,q,x,a,b,r,y;
	cin>>n>>q>>r;	//number of nodes, queries, root.
	v.resize(n+1);
	for(x=1;x<n;x++) {
		cin>>a>>b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs(r,r,0);
	M[0][r]=0;
	for(x=1;x<MAXLOG;x++)
		for(y=1;y<=n;y++)
			M[x][y]=M[x-1][M[x-1][y]];
	while(q--) {
		cin>>a>>b;
		if(f(a,b))
			cout<<a<<" es ancestro de "<<b<<endl;
		else
			cout<<b<<" no es ancestro de "<<b<<endl;			
	}
	return 0;
}
