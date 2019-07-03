#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <random>

using namespace std;

int myrandom (int i) { return std::rand()%i;}

int randInt(int i,int j) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(i , j);
	return dis(gen);
}

void randomTree(int n) {
	int i;
	vector<int> v;
	int A[n+1],P[n+1];
	for(i=1;i<=n;i++) 
		v.push_back(i);
	random_shuffle(v.begin(),v.end(),myrandom);
	*A=n;
	for(i=0;i<n;i++) {
		if(A[i] == 1)	// Leaf
			continue;
		int j=i+1,cota=i+A[i]-1;
		while(j<=cota) {
			int k=randInt(1,cota-j+1);
			A[j]=k,P[v[j]]=v[i];
			j+=k;
		}
	}
	int root=v[0];
	printf("%d %d\n",root,randInt(1,n));	// Imprime la raiz del arbol
	for(int x=1;x<=n;x++) if(x!=root)
		printf("%d %d\n",x,P[x]);			// Imprime n-1 lineas (nodo y padre)
}

int main()
{
	int n=randInt(1,1000),x;
	cout<<1<<"\n"<<n<<endl;
	randomTree(n);
	return 0;
}
