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
		size=1;
	}
	
};

inline int size(node *it) {
	return it?it->size:0;
}

void print( node *it ) {
	if(!it)
		return;
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

int query(node *it,int i,int j,int val,int sum=0) {
	int index=sum+size(it->l);
	int leftIndex=index-size(it->l),rightIndex=index+size(it->r);
	int res=0;
	if(i==leftIndex && j==rightIndex) {	//Encontró el rango
		
	}
	else if(index < i) {	//Buscar a la derecha
		res+=query(it->r,i,j,val,index+1);
	}
	else if(index > j) {	//Buscar a la izquierda
		res+=query(it->l,i,j,val,sum);
	}
	else {
		/**
		*	Evaluar si it->val cumple con la condición
		*	if(it->val <= val)
		*		res++
		*/
		
		if(i < index) 	//Dividir a la izquierda
			res+=query(it->l,i,index-1,val,sum);
		if(index < j) 	//Dividir a la derecha
			res+=query(it->r,index+1,j,val,index+1);
	}
	return res;
}

void split(node *it,node *&left,node *&right,int i) {
	if(!it) 
		left=right=NULL;
	else {
		if(size(it->l)<i) {
			split(it->r,it->r,right,i-size(it->l)-1);
			left=it;
		}
		else {
			split(it->l,left,it->l,i);
			right=it;
		}
		it->size=size(it->l)+size(it->r)+1;
	}
}

void merge(node *&it,node *left,node *right) {
	if(!left) 
		it=right;
	else if(!right) 
		it=left;
	else {
		if(left->weight<right->weight) {
			merge(left->r,left->r,right);
			it=left;
		}
		else {
			merge(right->l,left,right->l);
			it=right;
		}
		it->size=size(it->l)+size(it->r)+1;
	}	
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
