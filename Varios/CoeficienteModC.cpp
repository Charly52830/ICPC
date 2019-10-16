#include<iostream>
#define N 100010
using namespace std;

typedef long long ll;

ll fact[N],B[N];

ll funcion(ll a,ll b,ll c) {
    int n=32,k=1,x;
    ll napadas[n];
    napadas[0]=a%c;
    for(x=1;x<n;x++)
        napadas[x]=napadas[x-1]*napadas[x-1]%c;
    for(x=0;x<n;x++)
        if(b&(1<<x))
            k=(k*napadas[x])%c;
    return k;
}

ll coeficiente(ll n,ll k,ll mod) {
	ll k1=funcion(fact[k],mod-2,mod);
	ll n1=fact[n];
	ll n_k1=funcion(fact[n-k],mod-2,mod);
	ll res=(k1*n1)%mod;
	res=(res*n_k1)%mod;
	return res;
}

int main() {
	int x;
	ll mod=998244353;
	fact[0]=1;
	for(x=1;x<N;x++)
		fact[x]=((ll)x*fact[x-1])%mod;
	
	cout<<coeficiente(50,20,998244353)<<endl;
	//99850124
	
	return 0;
}
