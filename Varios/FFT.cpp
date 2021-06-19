#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define FASTIO cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define forn(i, n) for(int i = 0; i < int(n); i ++)
#define fore(i, a, b) for(int i = int(a); i < int(b); i ++)
using namespace __gnu_pbds;
using namespace std;
using cd = complex<double>;

typedef vector<int> vi;

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
 * Multiplicar 2 polinomios en O(n log(n))
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
        fa[i] *= fb[i];
    fft(fa, true);

    vi result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
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


int main() {
	int A[] = {-1, -2, -3};
	vi coeficientes = coeffs(A, 3);
	for(int c : coeficientes) 
		cout << c << " ";
	cout << endl;
	/* 1 -6 11 -6 0 0 0 0 */	
	return 0;
}
