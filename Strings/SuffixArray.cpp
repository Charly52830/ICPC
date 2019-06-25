#include<iostream>
#define alfabeto 5
using namespace std;

string S;
int n,x;

int order[200001],clases[200001],newOrder[200001],newClases[200001];
int count[200002];

int f(char c) {
	string s="$ACGT";
	for(int x=0;;x++)
		if(c==s[x])
			return x;
}

int main() {
	cin>>S;
	n=S.size();
	//Counting Sort
	for(x=0;x<n;x++)
		count[f(S[x])]++;
	for(x=1;x<alfabeto;x++)
		count[x]+=count[x-1];
	for(x=n-1;x>=0;x--) {
		count[f(S[x])]--;
		order[count[f(S[x])]]=x;
	}
	clases[*order]=0;
	for(x=1;x<n;x++) {
		clases[order[x]]=clases[order[x-1]];
		if(S[order[x]]!=S[order[x-1]])
			clases[order[x]]++;
	}
	int l=1;
	while(l<n) {
		//Inicia Napadas
		for(x=0;x<n;x++)
			count[x]=0;
		for(x=0;x<n;x++)
			count[clases[x]+1]++;
		for(x=2;x<=n;x++)
			count[x]+=count[x-1];
		for(x=0;x<n;x++) {
			int cl=(order[x]-l+n)%n;
			newOrder[count[clases[cl]]]=cl;
			count[clases[cl]]++;
		}
		//Termina napadas
		swap(order,newOrder);
		//Inicia napadillas
		newClases[*order]=0;
		for(x=1;x<n;x++) {
			int cl=(order[x]+l)%n;
			int cl2=(order[x-1]+l)%n;
			newClases[order[x]]=newClases[order[x-1]];
			if(clases[order[x]]!=clases[order[x-1]] || clases[cl]!=clases[cl2])
				newClases[order[x]]++;
		}
		//Termina napadillas
		swap(clases,newClases);
		l*=2;
	}
	for(x=0;x<n;x++)
		cout<<order[x]<<" ";
	cout<<endl;
	return 0;
}
