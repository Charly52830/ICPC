#include <math.h>
#include <string.h>
#include <algorithm>
#include <cassert>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#define FASTIO cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define forn(i, n) for(int i = 0; i < int(n); i ++)
#define forr(i, n) for(int i = int(n); ~i; i --)
#define fore(i, a, b) for(int i = int(a); i < int(b); i ++)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int const oo = 1e9;
int const mod = 1e9 + 7;

typedef vector<double> vd;

class Matrix {

	public :
	vector<vd> M;
	int n;
	
	Matrix(int n) {
		M = vector<vd> (n, vd(n, 0.0));
		this -> n = n;
	}
	
	void insert(int i, int j, double k) {
		M[i][j] = k;
	}
	
	void imprimir() {
		forn(i, n) {
			forn(j, n) {
				cout << M[i][j] << " ";
			}
			cout << endl;
		}
	}

};

Matrix * multiplicar(Matrix * a, Matrix * b) {
	int n = a-> n;
	Matrix * ans = new Matrix(n);
	
	forn(i, n) 
        forn(j, n)
            forn(k, n) 
                ans -> M[i][j] += a -> M[i][k] * b -> M[k][j];
    
	return ans;
}

Matrix * binpow(Matrix * Ma, long long p) {
    int n = Ma -> n;
    Matrix * id = new Matrix(n);
    forn(i, n) id -> insert(i, i, 1.0);

    while (p > 0) {
        if (p & 1) 
            id = multiplicar(id, Ma);
        Ma = multiplicar(Ma, Ma);
        p >>= 1;
    }
    return id;
}

int main() {
	FASTIO
	return 0;
}
