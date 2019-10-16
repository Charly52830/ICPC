#include<random>
#include<iostream>
#define MAX_INT 2147483647
using namespace std;

int randInt() {
	static random_device ran;
	static mt19937 gen( ran() );
	static uniform_int_distribution<> dis( 0 , MAX_INT );
	return dis( gen );
}

struct node {
	
	int val;
	int weight,size;
	node *l,*r;
	
	node(int v) {
		val=v;
		l=r=NULL;
		weight=randInt();
	}
	
};

inline int size(node *it) {
	return it?it->size:0;
}

void print( node *it ) {
	if( it->l != NULL ) 
		print( it->l );
	cout<< it->val <<" ";
	if( it->r != NULL ) 
		print( it->r );
}

void heapify(node *it) {
	node *min=it;
	do {
		swap(it->weight,min->weight);
		it=min;
		if(it->l != NULL && it->l->weight < min->weight)
			min=it->l;
		if(it->r != NULL && it->r->weight < min->weight)
			min=it->r;
	}while(min!=it);
}

node* build(int *A,int n) {
	if(n==0) return NULL;
	int m=n/2;
	node *it=new node(A[m]);
	it->l=build(A,m);
	it->r=build(A+m+1,n-m-1);
	heapify(it);
	it->size=size(it->l)+size(it->r)+1;
	return it;
}

int main() {
	int A[]={5,2,8,3,0};
	node *treap=build(A,5);
	print(treap);
	printf("\n");
	return 0;
}

/**
*	Salida:
*	5 2 8 3 0
*/
