#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
const int oo = 1e9 + 7;

/**
 * Find the smallest number greater or equal to a specified number in the range [i, j].
 * No modification queries.
 */

template <typename T, typename I = T>
class SegmentTree {
	
	/**
	 * Segment tree que soporta operaciones de preguntas en rangos y update de un
	 * solo valor.
	 *
	 * Construcción: O(n log n)
	 * Actualización: O(log n)
	 * Pregunta: O(log n)
	 * Memoria: O(4n)
	 * n: tamaño del arreglo
	 *
	 * Funciona para responder fácilmente otro tipo de preguntas en O(log n) 
	 * a partir de un Segment tree básico, por ejemplo:
	 *
	 * - Encontrar el k-ésimo cero en todo el arreglo
	 * - Encontrar el prefijo de todo el arreglo cuya suma es >= x
	 * - Encontrar el primer elemento mayor a x en un rango
	 * - Encontrar el subsegmento de mayor suma en un rango
	 */
	#define L(k) (k << 1)
	#define R(k) (k << 1) + 1
	T (*merge) (T&,T&);
	T (*make) (I);
	T *tree;
	int n;
	
	/**
	 * Operación para construir recursivamente el segment tree.
	 */
	I query(I val, int i, int j, int k, int l, int r) {
		if(i <= l && r <= j) {
			auto it = lower_bound(tree[k].begin(), tree[k].end(), val);
			if(it != tree[k].end())
				return *it;
			return oo;
		}
		int m = l + r >> 1;
		bool left = max(i, l) <= min(j, m);
		bool right = max(i, m + 1) <= min(j, r);
		if(left && right) 
			return min(query(val, i, j, L(k), l, m), query(val, i, j, R(k), m + 1, r));
		else if(left) 
			return query(val, i, j, L(k), l, m);
		else 
			return query(val, i, j, R(k), m + 1, r);
	}
	
	/**
	 * Operación para construir recursivamente el segment tree.
	 */
	void build(vector<I> & v, int i, int l, int r) {
		if(l == r) 
			tree[i] = make(v[l]);
		else {
			int m = l + r >> 1;
			build(v, L(i), l, m);
			build(v, R(i), m + 1, r);
			tree[i] = merge(tree[L(i)], tree[R(i)]);
		}
	}
	
	public:
	
	/**
	 * Constructor que crea un Segment Tree a partir de un vector.
	 *
	 * v: vector del que se construye el segment tree.
	 * custom_function: función con la que trabaja el segment tree.
	 */
	SegmentTree(vector<I> & v, T (*custom_function) (T&,T&), T (*make_data) (I) = [](I val) {return val;}) {
		merge = custom_function;
		make = make_data;
		n = v.size();
		tree = new T[4 * n];
		build(v, 1, 0, n - 1);
	}
	
	/**
	 * Pregunta del arreglo en el rango de i a j evaluando con la función asignada.
	 * Indexado desde 0 y los segmentos son cerrados (la pregunta incluye a los
	 * indices i y j).
	 *
	 * i: indice inferior.
	 * j: indice superior.
	 * val: valor por preguntar en el segmento
	 */
	I query(int i, int j, I val) {
		return query(val, i, j, 1, 0, n - 1);
	}
	
};

vi merge(vi & a, vi & b) {
	vi ans;
	merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(ans));
	return ans;
}

vi make_data(int val) {
	vi v{val};
	return v;
}

int main() {
	vector<int> v {4, 9, 2, 1, 3, 4, 7, 6, 7, 2};
	SegmentTree<vi, int> st(v, merge, make_data);
	
	cout << st.query(0, 9, 2) << endl;	// 2
	cout << st.query(3, 7, 5) << endl;	// 6
	cout << st.query(1, 4, 10) << endl;	// 1000000007
	return 0;
}
