#include<vector>
#include<iostream>
#define forr(i,a,b) for(int i=a;i<b;i++)
#define forn(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef long long ll;
const ll MAXN = 1e7+10, M = 1e9+7;	// M es primo
ll *INV;
ll F[MAXN], FI[MAXN];	// Factorial y factorial inverso

/* Exponenciación binaria modular O(log e) */
ll expmod(ll b, ll e) {
	ll ans = 1;
	while(e) {
		if(e & 1) ans = ans * b % M;
		b = b * b % M; e >>= 1;
	}
	return ans;
}

/* Inverso modular O(log M) */
ll invmod(ll a) { return expmod(a, M - 2); }

/* Precomputo de inverso modular para responder en O(1) */
void precal_invmod() {
	INV = (ll*)malloc(MAXN * sizeof(ll));
	INV[1] = 1; forr(i, 2, MAXN) INV[i] = M - (ll)(M / i) * INV[M % i] % M;
}

/* Precomputo de factoriales y su inverso multiplicativo */
void precal_fact() {
	F[0] = 1; forr(i, 1, MAXN) F[i] = F[i - 1] * i % M;
	if(!INV) precal_invmod();
	FI[0] = 1; forr(i, 1, MAXN) FI[i] = FI[i - 1] * INV[i] % M;
}

/* Coeficientes binomiales con factoriales pre calculados*/
ll Comb(ll n, ll k) {
	if(n < k) return 0;
	return F[n] * FI[k] % M * FI[n - k] % M;
}

/* Precomputo de coeficientes binomiales cuando n * k <= 10^7 */
ll C[MAXN][MAXK];
void precal_comb() {
	forn(i, MAXN) {
		C[i][0] = 1; if(i < MAXK) C[i][i] = 1;
		forr(j, 1, min(i, MAXK))
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % M;
	}
}

/* Precomputo de coeficientes binomiales cuando n * k <= 10^7 sin MAXN y MAXK fijos */
vector<vector<ll> > C;
void precal_comb(ll N, ll K) {
	C.resize(N, vector<ll>(K));
	forn(i, N) {
		C[i][0] = 1; if(i < K) C[i][i] = 1;
		forr(j, 1, min(i, K))
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % M;
	}
}


int main() {
	
	return 0;
}
