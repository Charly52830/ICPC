#include<iostream>
#define oo 1000000

using namespace std;

/**
 * Definición de Segment Tree para distintas preguntas comunes.
 * range minimum query: 
 *  SegmentTree<int> st(A, n, min_function, oo);
 *
 * range maximum query:
 *  SegmentTree<int> st(A, n, max_function, 0);
 *
 * range sum query:
 *  SegmentTree<int> st(A, n, sum_function, 0);
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
 * Se puede formar cualquier otro Segment Tree con funciones específicas y
 * valores por defecto específicos.
 *
 * Las funciones deben regresar el tipo de dato del que se declaró el Segment Tree.
 * Las funciones deben recibir 2 parámetros del tipo de dato del que se declaró
 * el Segment Tree.
 */

int min_function(int a,int b) {
	return min(a,b);
}

int max_function(int a,int b) {
	return max(a,b);
}

int sum_function(int a,int b) {
	return a+b;
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
	 * Memoria: O(2n)
	 * n: tamaño del arreglo
	 */
	
	T (*func) (T,T);
	T *tree, def;
	int n;
	
	public:
	
	/**
	 * Constructor que crea un Segment Tree a partir de un arreglo.
	 *
	 * A: arreglo del que se construye el segment tree.
	 * size: tamaño del arreglo.
	 * custom_function: función con la que trabaja el segment tree.
	 * default_value: valor por defecto utilizado para responder preguntas.
	 */
	SegmentTree(T *A, int size, T (*custom_function) (T,T), T default_value) : func(custom_function) {
		n = size;
		def = default_value;
		tree = new T[2 * n];
		for(int i = 0; i < n; i++) 
			tree[i + n] = A[i];
		for(int i = n - 1; i > 0; i--)
			tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
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
		n = size;
		def = default_value;
		tree = new T[2 * n];
		for(int i = 0; i < n; i++) 
			tree[i + n] = def;
		for(int i = n - 1; i > 0; i--)
			tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
	}
	
	/**
	 * Pregunta del arreglo en el rango de i a j evaluando con la función asignada
	 * Indexado desde 0 y los segmentos son cerrados (la pregunta incluye a los
	 * indices i y j).
	 *
	 * i: indice inferior.
	 * j: indice superior.
	 *
	 */
	T query(int i, int j) {
		T ans = def;
		i += n, j += n;
		while(i <= j) {
			if(i & 1) ans = func(ans, tree[i++]);
			if(!(j & 1)) ans = func(ans, tree[j--]);
			i >>= 1, j >>= 1;
		}
		return ans;
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
		i += n;
		if(add) tree[i] += val;
		else tree[i] = val;
		for(i >>= 1; i > 0; i >>= 1)
			tree[i] = func(tree[2 * i], tree[2 * i + 1]);
	}
	
	/**
	 * Operador que devuelve el valor actual del arreglo en la posición i
	 */
	T operator [] (int i) {
		return tree[i + n];
	}
	
};

int main() {
	
	return 0;
}
