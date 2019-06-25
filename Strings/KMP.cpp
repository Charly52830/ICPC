//Knuth-Morris-Pratt
#include<iostream>
using namespace std;

int main() {
	string P,T;
	cin>>P>>T;
	P.append("$");
	T.append("$");
	//Tabla de preprocesamiento
	int S[P.size()];
	*S=0;
	int border=0,i;
	for(i=1;i<P.size();i++) {
		while(border>0 && P[i]!=P[border])
			border=S[border-1];
		if(P[i]==P[border])
			border++;
		else
			border=0;
		S[i]=border;
	}
	//KMP
	i=0;
	int tam=0;
	while(i+tam<T.size()) {
		if(T[i+tam]==P[tam]) {
			tam++;
			if(tam==P.size()-1)
				cout<<i<<" ";
		}
		else if(tam>0) {
			i+=tam-S[tam-1];
			tam=S[tam-1];;
		}
		else
			i++;			
	}
	cout<<endl;
	return 0;
}
