#include <vector>
#include <iostream>
#define pb push_back
using namespace std;

typedef vector<vector<int>> Graph;
typedef pair<int, int> pii;

template <typename T>
class SparseTable {
	
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

class LCA {
	/**
	* Lowest Common Ancestor
	*
	* Construcción: O(n log n)
	* Memoria: O(n log n)
	* lca: O(1)
	*/

	vector<pii> etta;
	int * index;
	SparseTable<pii> *st;
	
	void dfs(int n, Graph & g, vector<pii> & etta, int depth = 0) {
		etta.pb({depth, n});
		for(int v : g[n]) {
			dfs(v, g, etta, depth + 1);
			etta.pb({depth, n});
		}
	}
	
	public:
	
	LCA(Graph & g, int root = 0) {
		int n = g.size();
		dfs(root, g, etta);
		index = new int[n];
		for(int i = 0; i < etta.size(); i ++) 
			index[etta[i].second] = i;
		st = new SparseTable<pii>(etta);
	}
	
	int lca(int u, int v) {
		pii ans = st -> rmq(index[u], index[v]);
		return ans.second;
	}
	
	int depth(int u) {
		return etta[index[u]].first;
	}

};

int main() {
	int n;
	cin >> n;
	Graph g = Graph(n);
	for(int i = 0; i < n - 1; i ++) {
		int a, b;
		cin >> a >> b;
		g[a].pb(b);
	}
	
	LCA lca(g);
	return 0;
}
