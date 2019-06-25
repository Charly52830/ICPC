/*
Encontrar SCC con el algoritmo de Korasaju.

Algoritmo que encuentra todos los Componentes Fuertemente Conectados utilizando DFS
O(|V| + |A|)

*/
#include<vector>
#include<iostream>
using namespace std;

int napadas[10001];
vector<int> grafo[10001],grafo_revertido[10001]; //LISTA DE ADYACENCIA
vector<int> napadillas;

void DFS1(int x) {
	napadas[x]=1;
	for(int y=0;y<grafo_revertido[x].size();y++)
		if(napadas[grafo_revertido[x][y]]==0)
			DFS1(grafo_revertido[x][y]);
	napadillas.push_back(x);
}

void DFS2(int x) {
	napadas[x]=0;
	for(int y=0;y<grafo[x].size();y++)
		if(napadas[grafo[x][y]])
			DFS2(grafo[x][y]);
}

int main() {
	int n,m,a,b,c=0,x,y;
	cin>>n>>m; //VÉRTICES, ARISTAS
	for(x=0;x<m;x++) {
		cin>>a>>b; //ARISTA DEL VÉRTICE A AL VÉRTICE B
		grafo[a].push_back(b);
		grafo_revertido[b].push_back(a);
	}
	for(x=1;x<=n;x++)
		if(napadas[x]==0)
			DFS1(x);
	for(x=napadillas.size()-1;x>=0;x--) {
        y=napadillas[x];
        if(napadas[y]) {
            DFS2(y);
            c++;
		}
	}
    cout<<c<<endl; //CANTIDAD DE SCCs
    return 0;
}
