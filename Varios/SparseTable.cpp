#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class SparseTable {
	/**
	* Range minimum query sin updates.
	*
	* Construcción: O(n log n)
	* Memoria: O(n log n)
	* Query: O(1)
	*/
	
	vector<vector<T>> table;
	int *log;
	
	public:
	
	SparseTable(vector<T> & v) {
		int const n = v.size();
		log = new int[n + 1];
		log[1] = 0;
		for(int i = 2; i <= n; i ++)
			log[i] = log[i >> 1] + 1;
		
		table = vector<vector<T>> (log[n] + 1, vector<T>(n));
		for(int j = 0; j < n; j ++)
			table[0][j] = v[j];
		for(int i = 1; i <= log[n]; i ++) 
			for(int j = 0; j <= n - (1 << i); j ++)
				table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
		
	}
	
	T rmq(int l, int r) {
		int k = log[r - l + 1];
		return min(table[k][l], table[k][r - (1 << k) + 1]);
	}
	
};

int main() {
	vector<int> v{4, 9, 2, 1, 3, 4, 7, 6, 7, 2};
	SparseTable<int> st(v);
	
	cout << st.rmq(0, 9) << endl; // 1
	cout << st.rmq(4, 8) << endl; // 3
	cout << st.rmq(9, 9) << endl; // 2
	return 0;
}
