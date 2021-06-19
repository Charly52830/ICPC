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
	 * Memoria: O(2n)
	 * n: tamaño del arreglo
	 */
	
	T (*func) (T,T);
	T *tree;
	int n;
	
	public:
	
	/**
	 * Constructor que crea un Segment Tree a partir de un arreglo.
	 *
	 * v: arreglo del que se construye el segment tree.
	 * custom_function: función con la que trabaja el segment tree.
	 */
	SegmentTree(vector<T> & v, T (*custom_function) (T,T)) {
		n = v.size();
		func = custom_function;
		tree = new T[2 * n];
		for(int i = 0; i < n; i++) 
			tree[i + n] = v[i];
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
	 */
	T query(int i, int j) {
		T ans;
		bool b = 0;
		i += n, j += n;
		while(i <= j) {
			if(i & 1) ans = b ? func(ans, tree[i ++]) : tree[i ++], b = 1;
			if(!(j & 1)) ans = b ? func(ans, tree[j --]) : tree[j --], b = 1;
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
	
};

int main() {
	
	return 0;
}
