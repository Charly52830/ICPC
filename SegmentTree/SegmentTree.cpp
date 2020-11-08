#include <vector>
#include <iostream>
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
	
	T (*func) (T,T);
	T *tree;
	int n;
	
	/**
	 * Operación para construir recursivamente el segment tree.
	 */
	void build(vector<T> & v, int i, int l, int r) {
		if(l == r) 
			tree[i] = v[l]; 
		else {
			int m = l + r >> 1;
			build(v, i * 2, l, m);
			build(v, i * 2 + 1, m + 1, r);
			tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
		}
	}
	
	/**
	 * Operación recursiva para responder la pregunta básica del segment tree.
	 */
	T query(int i, int j, int k, int l, int r) {
		if(i <= l && r <= j) return tree[k];
		int m = l + r >> 1;
		bool left = max(i, l) <= min(j, m);
		bool right = max(i, m + 1) <= min(j, r);
		if(left && right)
			return func(query(i, j, k * 2, l, m), query(i, j, k * 2 + 1, m + 1, r));
		else if(left)
			return query(i, j, k * 2, l, m);
		else
			return query(i, j, k * 2 + 1, m + 1, r);
	}
	
	/**
	 * Operación para actualizar una posición del segment tree.
	 */
	void update(int i, T val, bool add, int k, int l, int r) {
		if(l == r) {
			if(add) tree[k] += val;
			else tree[k] = val;
		}
		else {
			int m = l + r >> 1;
			if(i <= m) update(i, val, add, k * 2, l, m);
			else update(i, val, add, k * 2 + 1, m + 1, r);
			tree[k] = func(tree[k * 2], tree[k * 2 + 1]);
		}
	}
	
	public:
	
	/**
	 * Constructor que crea un Segment Tree a partir de un vector.
	 *
	 * v: vector del que se construye el segment tree.
	 * custom_function: función con la que trabaja el segment tree.
	 */
	SegmentTree(vector<T> & v, T (*custom_function) (T,T)) {
		func = custom_function;
		n = v.size();
		tree = new T[4 * n];
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
	SegmentTree(int size, T (*custom_function) (T,T), T default_value = 0) : func(custom_function) {
		func = custom_function;
		n = size;
		tree = new T[4 * n];
		vector<T> v(n, default_value);
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
	
};

int main() {
	
	return 0;
}
