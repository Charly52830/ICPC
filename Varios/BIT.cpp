/**
*	Binary Indexed Tree for range sum and retrieve single values
*/

#include<iostream>
using namespace std;

class BIT {
	
	private :
	int *tree;
	int n;
	
	void add(int k, int x) {
		while(k <= n) {
			tree[k] += x;
			k += k&-k;
		}
	}
	
	public :
	
	BIT(int len) {
		n = len;
		tree = (int*)malloc((n + 1) * sizeof(int));
		for(int x=0;x<n;x++) 
			tree[x] = 0;
	}
	
	void range_sum(int i, int j, int k) {
		add(i, k);
		add(j + 1, -k);
	}
	
	int query(int k) {
		int s = 0;
		while(k >= 1) {
			s += tree[k];
			k -= k&-k;
		}		
		return s;
	}
};

int main() {
	
	return 0;
}
