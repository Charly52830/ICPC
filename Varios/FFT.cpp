#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define FASTIO cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define forn(i, n) for(int i = 0; i < int(n); i ++)
#define forr(i, n) for(int i = int(n); ~i; i --)
#define fore(i, a, b) for(int i = int(a); i < int(b); i ++)
using namespace __gnu_pbds;
using namespace std;
using cd = complex<double>;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> Graph;
typedef tree<int,null_type,less<int>,rb_tree_tag,
	tree_order_statistics_node_update> indexed_tree;

int const oo = 1e9;
int const mod = 1e9 + 7;

const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
	int n = a.size();
	if (n == 1)
		return;

	vector<cd> a0(n / 2), a1(n / 2);
	for (int i = 0; 2 * i < n; i++) {
		a0[i] = a[2*i];
		a1[i] = a[2*i+1];
	}
	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * PI / n * (invert ? -1 : 1);
	cd w(1), wn(cos(ang), sin(ang));
	for (int i = 0; 2 * i < n; i++) {
		a[i] = a0[i] + w * a1[i];
		a[i + n/2] = a0[i] - w * a1[i];
		if (invert) {
			a[i] /= 2;
			a[i + n/2] /= 2;
		}
		w *= wn;
	}
}

/*
 * Multiplicar/sumar 2 polinomios en O(n log(n))
 */
vi multiply(vi const& a, vi const& b) {
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while (n < a.size() + b.size()) 
		n <<= 1;
	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; i++)
		fa[i] *= fb[i];	// Cambiar el operador para sumar polinomios en vez de multiplicar
	fft(fa, true);

	vi result(n);
	for (int i = 0; i < n; i++)
		result[i] = round(fa[i].real());
	while(*result.rbegin() == 0) result.pop_back();
	return result;
}

/* 
 * Obtener coeficientes del polinomio dadas sus raices en O(n log(n)^2)
 */
vi coeffs(int roots[], int n) {
	if(n == 1) {
		vi v{1, roots[0]};
		return v;
	}
	int mitad = n / 2;
	vi izquierda = coeffs(roots, n / 2);
	vi derecha = coeffs(roots + mitad, mitad + (n & 1));
	vi ans = multiply(izquierda, derecha);
	return ans;
}

/* 
 * Multiplicar/sumar 2 números muy grandes dados como strings (hasta 10^1000000) en O(n log n)
 */
string multiply(string const& a, string const& b) {
	vi va, vb;
	for(auto it = a.rbegin(); it != a.rend(); it ++) va.pb((*it) - '0');
	for(auto it = b.rbegin(); it != b.rend(); it ++) vb.pb((*it) - '0');
	vi vc = multiply(va, vb);
	//unsigned long long k = 0;
	__int128 k = 0;
	string ans = "";
	for(int i : vc) {
		k += i;
		ans.pb((k % 10) + '0');
		k /= 10;
	}
	while(k) ans.pb((k % 10) + '0'), k /= 10;
	reverse(ans.begin(), ans.end());
	return ans;
}

/*
 * Devuelve el producto punto del arreglo a con cada rotación del arreglo b en O(n log n).
 * El producto punto es la sumatoria de a_i * b_i para todo 0 <= i < n
 * El resultado en la posición i contiene el producto punto de a con b rotado i posiciones a la izquierda
 */
vi convolution(vi const & a, vi const & b) {
	int n = a.size();
	vi A, B;
	for(auto it = a.rbegin(); it != a.rend(); it ++) A.pb(*it);
	forn(_, n) A.pb(0);
	forn(_, 2) for(int i : b) B.pb(i);
	vi C = multiply(A, B), ans;
	fore(i, n - 1, 2 * n - 1) ans.pb(C[i]);
	return ans;
}

/*
 * Devuelve todas las sumas posibles de a_i + b_i y cuántas veces aparece en O(n log n)
 *
 * a_i, b_i <= 10^5 (recomendable)
 */
vi all_sums(vi const & a, vi const & b) {
	int max_A = 0, max_B = 0, n = a.size(), m = b.size();
	forn(i, n) if(a[i] > a[max_A]) max_A = i;
	forn(i, m) if(b[i] > b[max_B]) max_B = i;
	vi A(a[max_A] + 1, 0), B(b[max_B] + 1, 0);
	for(int i : a) A[i] ++;
	for(int i : b) B[i] ++;
	vi ans = multiply(A, B);
	return ans;
}

int main() {
	vi a{1, 2, 3}, b{2, 4};
	vi c = all_sums(a, b);
	for(int i : c) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}
