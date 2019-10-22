#include <chrono>
#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,
	tree_order_statistics_node_update> indexed_tree;

/**
*	Función para eficientar el hashing de las tablas hash.
*	https://codeforces.com/blog/entry/60737
*/
struct chash {
    const int RANDOM = (long long)(make_unique<char>().get()) ^ 
    	chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(int x) const { return hash_f(x)^RANDOM; }
};

int main() {
	gp_hash_table<int, int,chash> table;	//Tabla hash
	table[5]++;
	table[2]++;
	table[8]++;
	table[3]++;
	table[0]++;
	for(auto i:table)
		printf("%d ",i.first);
	printf("\n");
	indexed_tree tree;	//Árbol indexado
	tree.insert(5);
	tree.insert(2);
	tree.insert(8);
	tree.insert(3);
	tree.insert(0);
	for(auto i:tree)
		printf("%d ",i);
	printf("\n");
	return 0;	
}
/**
*	Salida: 
*	alguna permutación de 5,2,8,3,0
*	0 2 3 5 8
*/

