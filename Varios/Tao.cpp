//Cálculo de tao(1..n) en O(n)
//tao(n): numero de divisores de un número
//Lo hice yo mero.

#include<vector>
#include<iostream>
#include<bitset>
using namespace std;
#define NMAX 1000000
#define RAIZ 1000
bitset<NMAX> b;
vector<int> primos;

int tao[1000001];
int mapa[1000001];

int k,T;
bool bul;

void criba() {
	b.set();
	primos.push_back(2);
	int x,y;
	for(x=3;x<=RAIZ;x+=2) if(b[x]) {
			primos.push_back(x);
			for(y=x*x;y<=NMAX;y+=x)
				b[y]=0;
	}
	for(;x<NMAX;x+=2) if(b[x]) {
		primos.push_back(x);
		tao[x]=2;
	}
}

bool DFS(int i,int p,int t) {
	if(p*primos[i]>NMAX)
		return 0;
	for(int j=i;j<primos.size();j++) {
		if(p*primos[j]<=NMAX) { //nuevo numero encontrado
			k=p*primos[j]; //numero encontrado
			T=(t/(mapa[primos[j]]+1))*(mapa[primos[j]]+2);
			tao[k]=T;
			mapa[primos[j]]++;
			bul=DFS(j,k,T);
			mapa[primos[j]]--;
			if(!bul) {
				for(j++;j<primos.size() && p*primos[j]<=NMAX;j++) { //nuevo numero encontrado
					k=p*primos[j];
					T=(t/(mapa[primos[j]]+1))*(mapa[primos[j]]+2);
					tao[k]=T;
				}
				break;
			}
		}
		else
			break;
	}
	return 1;
}

int main() {
	criba();
	DFS(0,1,1);
	tao[1]=1;
	int x;
	for(x=2;x<=30;x++)
		cout<<tao[x]<<" ";
	cout<<endl;
	return 0;
}
