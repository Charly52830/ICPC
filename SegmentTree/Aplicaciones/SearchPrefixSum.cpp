#include <vector>
#include <iostream>
using namespace std;

/**
 * Aplicar búsqueda binaria dentro del segment tree.
 * Devuelve el índice del prefijo que suma >= val
 */

int sum_function(int a,int b) {
	return a + b;
}

template <typename T>
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
	 */
	#define L(k) (k << 1)
	#define R(k) (k << 1) + 1
	T (*merge) (T,T), (*make) (T);
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
	void update(int i, T val, bool add, int k, int l, int r) {
		if(l == r) {
			if(add) tree[k] += make(val);
			else tree[k] = make(val);
		}
		else {
			int m = l + r >> 1;
			if(i <= m) update(i, val, add, L(k), l, m);
			else update(i, val, add, R(k), m + 1, r);
			tree[k] = merge(tree[L(k)], tree[R(k)]);
		}
	}
	
	/**
	 * Operación para construir recursivamente el segment tree.
	 */
	void build(vector<T> & v, int i, int l, int r) {
		if(l == r) 
			tree[i] = make(v[l]); 
		else {
			int m = l + r >> 1;
			build(v, L(i), l, m);
			build(v, R(i), m + 1, r);
			tree[i] = merge(tree[L(i)], tree[R(i)]);
		}
	}
	
	/**
	 * Operación para encontrar recursivamente el prefijo que sume >= val
	 */
	int binary_search(T val, int k, int l, int r) {
		if(tree[k] < val) return -1;
		if(l == r) return l;
		int m = l + r >> 1;
		if(tree[L(k)] < val) return binary_search(val - tree[L(k)], R(k), m + 1, r);
		else return binary_search(val, L(k), l, m);
	}
	
	public:
	
	/**
	 * Constructor que crea un Segment Tree a partir de un vector.
	 *
	 * v: vector del que se construye el segment tree.
	 * custom_function: función con la que trabaja el segment tree.
	 */
	SegmentTree(vector<T> & v, T (*custom_function) (T,T), T (*make_data) (T) = [](T val) {return val;}) {
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
	 * add: si add es false, el arreglo en la posición i se sustituirá con el nuevo
	 *	valor, si es true, en arreglo en la posición i será sumado al valor actual.
	 */
	void update(int i, T val, bool add = false) {
		update(i, val, add, 1, 0, n - 1);
	}
	
	/**
	 * Función para aplicar búsquda binaria dentro del segment tree.
	 * val: valor a buscar en el prefijo
	 */
	int binary_search(T val) {
		return binary_search(val, 1, 0, n - 1);
	}
	
};

int main() {
	vector<int> v {5, 2, 8, 3, 7};
	SegmentTree<int> st(v, sum_function);
	cout << st.binary_search(17) << endl;	// 3
	cout << st.binary_search(15) << endl;	// 2
	cout << st.binary_search(25) << endl;	// 4
	return 0;
}
