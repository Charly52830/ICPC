#include<iostream>
using namespace std;

typedef long long ll;

ll M[1010][1010];

void f(int row,int col) {
	for(int x=0;x<row;x++) {		// O(row*col)
		for(int y=0;y<col;y++) {
			if(x&&y)
				M[x][y]+=M[x-1][y]+M[x][y-1]-M[x-1][y-1];
			else if(x)
				M[x][y]+=M[x-1][y];
			else if(y)
				M[x][y]+=M[x][y-1];
		}
	}
}

/**
*	Esquina superior derecha, (a y b)
*	Esquina inferior izquierda (c y d)
*/
ll rsq(int a,int b,int c,int d) { // O(1)
	ll s=M[c][d];
	if(b)
		s-=M[c][b-1];
	if(a)
		s-=M[a-1][d];
	if(a&&b)
		s+=M[a-1][b-1];
	return s;
}

int main() {
	int n,m,x,y;
	cin>>n>>m;
	for(x=0;x<n;x++)
		for(y=0;y<n;y++)
			cin>>M[x][y];
	f(n,m);
	cout<<rsq(0,3,3,3)<<endl; 	//Esquina superior izquierda, esquina inferior derecha
	return 0;
}
