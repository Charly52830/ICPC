class DisjointSet {
	private:
	int *A,*S;
	int C;

	public:
	
	DisjointSet(int n) {
		A=(int*)malloc(n*sizeof(int));
		S=(int*)malloc(n*sizeof(int));
		for(int x=0;x<n;x++) {
			A[x]=x;
			S[x]=1;
		}
		C=n;
	}
		
	int padre(int x) {
		if(x!=A[x])
			A[x]=padre(A[x]);
		return A[x];
	}
	
	void unir(int i,int j) {
		int a=padre(i);
		int b=padre(j);
		if(a==b)
			return;
		C--;
		if(S[a]<S[b])
			swap(a,b);
		S[a]+=S[b];
		A[b]=a;
	}
		
	int getComponentes() {
		return C;
	}
	
	int getTam(int x) {
		return S[x];
	}
		
};
