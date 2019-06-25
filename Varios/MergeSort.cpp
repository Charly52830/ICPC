/*
Algoritmo de mezcla.
Sirve para ordenar un vector de menor a mayor
Pueden resolverse distintos problemas con las modificaciones correctas en el código.
Modifica en donde dice MODIFICA AQUI para ordenar de mayor a menor.
*/

#include<vector>
#include<iostream>
#define oo (1<<30)-1
using namespace std;

typedef vector<int> vi;

void mezcla(int i,int m,int f,vi::iterator it1,vi::iterator it2) {
	int x,l,r;
	int n1=m-i+1;
	int n2=f-m;
	int L[n1+1],R[n2+1];
	vi::iterator it3=it1+i;
	for(x=0;x<n1;x++)
		L[x]=*it3++;
	for(x=0;x<n2;x++)
		R[x]=*it3++;
	L[n1]=R[n2]=oo;       //MODIFICA AQUI
	l=r=0;
	vi::iterator it4=it1+i,it5=it1+f;
    while(it4<=it5) {
		if(L[l]<R[r])            //MODIFICA AQUI
			*it4=L[l++];
		else
			*it4=R[r++];
		it4++;
	}
}

void ordena(int i,int f,vi::iterator it1,vi::iterator it2) {
	if(i>=f)
    	return;
	int m=(i+f)>>1;
	ordena(i,m,it1,it2);
	ordena(m+1,f,it1,it2);
	mezcla(i,m,f,it1,it2);
}

int main() {
	int a[]={5,2,8,3,0},x;
	vi A(a,a+5);
	ordena(0,A.size()-1,A.begin(),A.end());
	for(int x=0;x<A.size();x++)
		cout<<A[x]<<" ";
	cout<<endl;
    return 0;
}
