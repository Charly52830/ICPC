#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

struct Data {
	ll size, sum, ans;
};

Data merge(Data l, Data r) {
	Data res;
	res.size = l.size + r.size;
	res.sum = l.sum + r.sum;
	res.ans = l.ans + r.ans + l.size * r.sum;
	return res;
}

Data make_data(int val) {
	return {1, val, val};
}

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
	T (*merge) (T,T);
	T (*make) (I);
	T *tree;
	int n;
	
	/**
	 * Operación para construir recursivamente el segment tree.
	 */
	T query(int i, int j, int k, int l, int r) {
		if(i <= l && r <= j) return tree[k];
		int m = l + r >> 1;
		bool left = max(i, l) <= min(j, m);
		bool right = max(i, m + 1) <= min(j, r);
		if(left && right) return merge(query(i, j, L(k), l, m), query(i, j, R(k), m + 1, r));
		else if(left) return query(i, j, L(k), l, m);
		else return query(i, j, R(k), m + 1, r);
	}
	
	/**
	 * Operación recursiva para responder la pregunta básica del segment tree.
	 */
	void update(int i, I val, int k, int l, int r) {
		if(l == r) 
			tree[k] = make(val);
		else {
			int m = l + r >> 1;
			if(i <= m) update(i, val, L(k), l, m);
			else update(i, val, R(k), m + 1, r);
			tree[k] = merge(tree[L(k)], tree[R(k)]);
		}
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
	SegmentTree(vector<I> & v, T (*custom_function) (T,T), T (*make_data) (I) = [](I val) {return val;}) {
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
	 */
	T query(int i, int j) {
		return query(i, j, 1, 0, n - 1);
	}
	
	/**
	 * Función para actualizar un solo elemento del arreglo.
	 * Indexado desde 0.
	 *
	 * i: indice del arreglo a actualizar
	 * val: valor con el que se va a actualizar el arreglo en la posición i
	 */
	void update(int i, I val) {
		update(i, val, 1, 0, n - 1);
	}
	
};

int main() {
	vector<int> v{4, 9, 2, 1, 3, 4, 7, 6, 7, 2};
	SegmentTree<Data, int> st(v, merge, make_data);
	
	Data query = st.query(0, 3);
	cout << query.ans << endl;	// 32
	Data query2 = st.query(6, 9);
	cout << query2.ans << endl;	// 48
	Data query3 = merge(query, query2);
	cout << query3.ans << endl;	// 168
	return 0;
}
