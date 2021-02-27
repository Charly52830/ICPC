#include <cassert>
#include <vector>
#include <iostream>
using namespace std;

/**
 * Definición de Segment Tree Lazy para preguntas y actualizaciones en rangos.
 * range sum query + range assign update:
 *  LazySegmentTree<int> st(v, sum_function, lazy_assign_sum);
 *
 * range maximum/minimum query + range assign update:
 *  LazySegmentTree<int> st(v, max_function, lazy_assign_max);
 *
 * range sum query + range sum update:
 *  LazySegmentTree<int> st(v, sum_function, lazy_sum_sum);
 *
 * range maximum/minimum query + range sum update:
 *  LazySegmentTree<int> st(v, max_function, lazy_sum_max);
 *
 * Se puede formar cualquier otro Segment Tree ajustando adecuadamente las
 * funciones.
 *
 * Para range update + single query puede utilizarse cualquier versión del
 * LazySegmentTree, solo se debe considerar si la actualización en rangos es
 * de asignación o de suma, y se puede utilizar st.query(i, i) para responder.
 *
 * Las funciones de range query deben regresar el tipo de dato del que se
 * declaró el Segment Tree, y deben recibir 2 parámetros también del tipo que
 * se declaró el Segment Tree. 
 *
 * Las funciones de propagación deben recibir 6 parámetros y no es necesario
 * utilizarlos todos:
 *  tree: referencia a un nodo del Segment Tree
 *  lazy: referencia al valor de propagación del nodo
 *  marked: si es true entonces el nodo contiene información no propagada en
 *   lazy, si es false entonces el nodo no tiene propagación pendiente
 *  update_val: valor con el que se va a actualizar el nodo
 *  l: índice inferior del segmento del arreglo que abarca el nodo
 *  r: índice superior del segmento del arreglo que abarca el nodo
 */

// Funciones de range query
int min_function(int a,int b) {
	return min(a, b);
}

int max_function(int a,int b) {
	return max(a, b);
}

int sum_function(int a,int b) {
	return a + b;
}

int gcd_function(int a, int b) {
	return !b ? a : gcd_function(b, a % b);
}

// Funciones de propagación
void lazy_assign_sum(int & tree, int & lazy, bool marked, int update_val, int l, int r) {
	tree = update_val * (r - l + 1);
	lazy = update_val;
}

void lazy_assign_max(int & tree, int & lazy, bool marked, int update_val, int l, int r) {
	tree = update_val;
	lazy = update_val;
}

void lazy_sum_sum(int & tree, int & lazy, bool marked, int update_val, int l, int r) {
	tree += update_val * (r - l + 1);
	if(marked)
		lazy += update_val;
	else
		lazy = update_val;
}

void lazy_sum_max(int & tree, int & lazy, bool marked, int update_val, int l, int r) {
	tree += update_val;
	if(marked)
		lazy += update_val;
	else
		lazy = update_val;
}

#define L(k) (k << 1)
#define R(k) (k << 1) + 1
template <typename T>
class LazySegmentTree {
	
	/**
	 * Segment tree que soporta preguntas y actualizaciones en rangos.
	 *
	 * Construcción: O(n log n)
	 * Actualización: O(log n)
	 * Pregunta: O(log n)
	 * Memoria: O(12n)
	 * n: tamaño del arreglo
	 *
	 * Otras preguntas en O(log n):
	 * - Encontrar el k-ésimo cero en todo el arreglo
	 * - Encontrar el prefijo de todo el arreglo cuya suma es >= x
	 * - Encontrar el primer elemento mayor a x en un rango
	 */
	
	T (*func) (T,T);
	void (*lazy_function) (T&,T&,bool,T,int,int);
	T *tree, *lazy;
	bool * marked;
	int n;
	
	/**
	 * Operación para construir recursivamente el segment tree.
	 */
	void build(vector<T> & v, int k, int l, int r) {
		marked[k] = false;
		if(l == r) 
			tree[k] = v[l]; 
		else {
			int m = l + r >> 1;
			build(v, L(k), l, m);
			build(v, R(k), m + 1, r);
			tree[k] = func(tree[L(k)], tree[R(k)]);
		}
	}
	
	/**
	 * Operación que realiza la propagación perezosa
	 */
	void push(int k, int l, int r, int m) {
		if(marked[k]) {
			lazy_function(tree[L(k)], lazy[L(k)], marked[L(k)], lazy[k], l, m);
			lazy_function(tree[R(k)], lazy[R(k)], marked[R(k)], lazy[k], m + 1, r);
			marked[L(k)] = true;
			marked[R(k)] = true;
			marked[k] = false;
		}
	}

	/**
	 * Operación recursiva para responder la pregunta básica del segment tree
	 */
	T query(int i, int j, int k, int l, int r) {
		if(i <= l && r <= j) return tree[k];
		int m = l + r >> 1;
		push(k, l, r, m);
		bool left = max(i, l) <= min(j, m);
		bool right = max(i, m + 1) <= min(j, r);
		if(left && right)
			return func(query(i, j, L(k), l, m), query(i, j, R(k), m + 1, r));
		else if(left)
			return query(i, j, L(k), l, m);
		else
			return query(i, j, R(k), m + 1, r);
	}
	
	/**
	 * Operación recursiva para actualizar el segment tree en rangos
	 */
	void update(int i, int j, int k, int l, int r, T val) {
		if(i <= l && r <= j)
			lazy_function(tree[k], lazy[k], marked[k], val, l, r), marked[k] = true;
		else {
			int m = l + r >> 1;
			push(k, l, r, m);
			if(max(i, l) <= min(j, m))
				update(i, j, L(k), l, m, val);
			if(max(i, m + 1) <= min(j, r))
				update(i, j, R(k), m + 1, r, val);
			tree[k] = func(tree[L(k)], tree[R(k)]);
		}
	}
	
	public:
	
	/**
	 * Constructor que crea un Segment Tree Lazy a partir de un vector.
	 *
	 * v: arreglo del que se construye el segment tree.
	 * custom_function: función que define el tipo de pregunta en rangos a responder.
	 * lazy_function: función de propagación que define cómo se lleva a cabo la 
	 *  actualización en rangos de forma perezosa.
	 */
	LazySegmentTree(vector<T> & v, T (*custom_function) (T,T), void (*lazy_function) (T&,T&,bool,T,int,int)) {
		func = custom_function;
		this -> lazy_function = lazy_function;
		n = v.size();
		tree = new T[4 * n];
		lazy = new T[4 * n];
		marked = new bool[4 * n];
		build(v, 1, 0, n - 1);
	}
	
	/**
	 * Constructor que crea un Segment Tree Lazy vacío, es decir, trabaja sobre un 
	 * arreglo inexistente cuyos valores son puestos por default.
	 *
	 * size: tamaño del arreglo.
	 * custom_function: función que define el tipo de pregunta en rangos a responder.
	 * lazy_function: función de propagación que define cómo se lleva a cabo la 
	 *  actualización en rangos de forma perezosa.
	 */
	LazySegmentTree(int size, T (*custom_function) (T,T), void (*lazy_function) (T&,T&,bool,T,int,int), T default_value = 0) {
		vector<T> v(size, default_value);
		this(v, custom_function, lazy_function);
	}
	
	/**
	 * Pregunta del arreglo en el rango de i a j evaluando con la función asignada.
	 * Indexado desde 0 con rangos inclusivos.
	 *
	 * i: indice inferior
	 * j: indice superior
	 */
	T query(int i, int j) {
		assert(0 <= i && i < n && 0 <= j && j < n);
		return query(i, j, 1, 0, n - 1);
	}
	
	/**
	 * Función para actualizar un segmento del arreglo.
	 * Indexado desde 0 con rangos inclusivos.
	 *
	 * i: indice inferior del segmento
	 * j: indice superior del segmento
	 * val: valor con el que se va a actualizar el segmento
	 */
	void update(int i, int j, T val) {
		assert(0 <= i && i < n && 0 <= j && j < n);
		update(i, j, 1, 0, n - 1, val);
	}
	
};

int main() {

	return 0;
}
