/*
Miller-Rabin
MB(n): regresa 1 si n es primo o 0 si no lo es.
Hasta O(ln(n)^4)
!!! C++11 !!!
*/
#include<unordered_set>
#include<math.h>
#include<iostream>
using namespace std;

typedef long long ll;

ll funcion(ll a,ll b,ll c) {
	ll n=(int)(log(b)/log(2))+1,napadas[n],k=1,x;
	napadas[0]=a%c;
	for(x=1;x<n;x++)
		napadas[x]=napadas[x-1]*napadas[x-1]%c;
	for(x=0;x<n;x++)
		if(b&(1<<x))
			k=(k*napadas[x])%c;
	return k;
}

bool MB(ll n) {
	if(n==2)
		return 1;
	if(!(n&1))
		return 0;
	ll q=n-1,k,m,a=2,b;
	for(k=1;q%2==0;k++,q/=2);
	k--;
	m=n/(1<<k);
	b=funcion(a,m,n);
	q=n-1;
	if(b==q||b==1)
		return 1;
	unordered_set<ll> napadas;
	napadas.insert(b);
	while(b!=1&&b!=q) {
		b=b*b%n;
		if(napadas.count(b))
			b=1;
		napadas.insert(b);
	}
	if(b==q)
		return 1;
	else
		return 0;
}

int main() {
	int n,x;
	for(x=2;x<=1000;x++) {
		if(MB(x))
			cout<<x<<" es primo\n";
		else
			cout<<x<<" no es primo\n";
	}
	return 0;
}
