#include <string.h>
#include <vector>
#include <iostream>
#define L(k) (k << 1)
#define R(k) (k << 1) + 1
using namespace std;

/**
 * Definición de Segment Tree para distintas preguntas comunes.
 * range minimum query: 
 *  SegmentTree<int> st(v, min_function);
 *
 * range maximum query:
 *  SegmentTree<int> st(v, max_function);
 *
 * range sum query:
 *  SegmentTree<int> st(v, sum_function);
 *
 * range gcd/lcm query:
 *  SegmentTree<int> st(v, gcd_function);
 *
 * range sum query con n elementos iniciados en 0:
 *  SegmentTree<int> st(n, sum_function, 0);
 * 
 * actualizar arreglo sustituyendo el valor del índice i con el valor:
 *  st.update(i, val, false);
 *
 * actualizar arreglo sumando el valor del índice i con el valor val:
 *  st.update(i, val, true);
 *
 * Se puede formar cualquier otro Segment Tree con funciones específicas.
 *
 * Las funciones deben regresar el tipo de dato del que se declaró el Segment Tree.
 * Las funciones deben recibir 2 parámetros del tipo de dato del que se declaró
 * el Segment Tree.
 */

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
	if(marked) lazy += update_val;
	else lazy = update_val;
}

void lazy_sum_max(int & tree, int & lazy, bool marked, int update_val, int l, int r) {
	tree += update_val;
	if(marked) lazy += update_val;
	else lazy = update_val;
}

template <typename T>
class LazySegmentTree {
	
	/**
	 * Segment tree que soporta operaciones de preguntas en rangos y update de un
	 * solo valor.
	 *
	 * Construcción: O(n log n)
	 * Actualización: O(log n)
	 * Pregunta: O(log n)
	 * Memoria: O(12n)
	 * n: tamaño del arreglo
	 *
	 * Funciona para responder fácilmente otro tipo de preguntas en O(log n) 
	 * a partir de un Segment tree básico, por ejemplo:
	 *
	 * - Encontrar el k-ésimo cero en todo el arreglo
	 * - Encontrar el prefijo de todo el arreglo cuya suma es >= x
	 * - Encontrar el primer elemento mayor a x en un rango
	 */
	
	T (*func) (T,T);
	void (*lazy_function) (T&,T&,bool,T,int,int);
	T *tree, *lazy;
	int n;
	bool * marked = NULL;
	
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
	 * Operación recursiva para responder la pregunta básica del segment tree.
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
	
	void update(int i, int j, int k, int l, int r, T val) {
		if(i <= l && r <= j)
			lazy_function(tree[k], lazy[k], marked[k], val, l, r);
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
	 * Constructor que crea un Segment Tree a partir de un vector.
	 *
	 * v: vector del que se construye el segment tree.
	 * custom_function: función con la que trabaja el segment tree.
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
	 * Constructor que crea un Segment Tree vacío, es decir, trabaja sobre un 
	 * arreglo inexistente cuyos valores son puestos por default.
	 *
	 * size: tamaño del arreglo.
	 * custom_function: función con la que trabaja el segment tree.
	 * default_value: valor por defecto de los elementos del arreglo.
	 */
	LazySegmentTree(int size, T (*custom_function) (T,T), void (*lazy_function) (T&,T&,bool,T,int,int), T default_value = 0) {
		vector<T> v(size, default_value);
		this(v, custom_function, lazy_function);
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
	void update(int i, int j, T val) {
		update(i, j, 1, 0, n - 1, val);
	}
	
};

int main() {
	
	return 0;
}
