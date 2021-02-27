#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;

/* Número de subpalíndromos en el string s */
ll manacher(vector<ll> s) {
	int n=s.size();
	vector<ll> d1(n);
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d1[l + r - i], ll(r - i + 1));
		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
			k++;
		}
		d1[i] = k--;
		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}
	
	vector<ll> d2(n);
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], ll(r - i + 1));
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
			k++;
		}
		d2[i] = k--;
		if (i + k > r) {
			l = i - k - 1;
			r = i + k ;
		}
	}
	
	ll sum = 0;
	for(int i = 0;i<n;i++){
		sum+=d2[i];
		sum+=d1[i];
	}
	return sum;
}

int main() {
	
	return 0;
}
