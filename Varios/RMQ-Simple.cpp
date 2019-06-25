#include<map>
#include<iostream>
using namespace std;

class RMQ {
	/**
	Clase para Range Minimum Query
	
	-No soporta update
	-Indexado desde 0
	-Para tener Range Maximum Query cambiar el min por el max
	
	Preprocesamiento: O(n logn)
	Query: O(1)
	**/
	private:
	map<pair<int,int>,int> mapa;
	
	public:
	RMQ(int *A,int n) {//Arreglo, tamaño
		int i,j,k;
		//Preprocesamiento de RMQ O(n logn)
		for(i=0;i<n;i++)
			mapa[make_pair(i,i)]=A[i];
		for(i=2,k=n-i;k>=0;i<<=1,k=n-i)
			for(j=0;j<=k;j++)
				mapa[make_pair(j,j+i-1)]=min(mapa[make_pair(j,j+i/2-1)],
							mapa[make_pair(j+i/2,j+i-1)]); //modificar aqui
		//Termina preprocesamiento de RMQ
	}
	
	/**
	*	Regresa el indice del arreglo donde se encuentra el valor más pequeño.
	*/
	int rmq(int a,int b) {//O(1) 
		int m=b-a+1,i;
		for(i=0;m>=1<<i;i++);
		int k=1<<(i-1);
		return min(mapa[make_pair(a,a+k-1)],mapa[make_pair(b-k+1,b)]);
	}

};

int main() {
	int A[]={5,2,8,3,0};
	RMQ rmq(A,5);
	cout<<rmq.rmq(1,2)<<endl;
	return 0;
}
/**
*	Output:
*	2
*/
