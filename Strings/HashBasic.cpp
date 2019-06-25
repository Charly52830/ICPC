#include<iostream>
#define A (911382323)
#define B (972663749)
#define A1 (48271)
#define B1 (2147483647)
#define N 500010
using namespace std;

typedef long long ll;

char S[N];
ll P[N],H[N];

ll Hash(int i,int j) {
	return ( H[j] - (( H[i-1] * P[j-i+1] ) % B ) + B ) % B;
}

int main() {
	int n,x;
	*P=1;
	for(x=1;x<N;x++)	//X inicia desde 1.
		P[x]=(P[x-1]*A)%B;
	scanf("%d",&n);
	scanf("%s",S);
	*H=*S;
	for(x=1;x<n;x++)	// X inicia desde 1.
		H[x]=(H[x-1]*A+S[x])%B;
	printf("%ld\n",Hash(3,4));
	return 0;
}

/*	Entrada:
*	6
*	charly
*		
*	Salida:
*	
*	795227536	
*/

