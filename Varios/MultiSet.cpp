/*
*	Multiset que resuelve el problema de eliminación en el multiset convencional.
*/
#include<map>
#include<set>
using namespace std;

class MultiSet {
	
	private:
	map<int,int> mapa;
	set<int> Set;
	int tam=0;
	public:
	
	void insert(int n) {
		mapa[n]++;
		if(mapa[n]==1)
			Set.insert(n);
		tam++;
	}
	
	void erase(int n) {
		if(mapa[n]==1)
			Set.erase(n);
		if(mapa[n]) {
			mapa[n]--;
			tam--;
		}
	}
	
	int size() {
		return tam;
	}
	
	bool empty() {
		return tam==0;
	}
	
	int count(int n) {
		return mapa[n];
	}
	
	set<int>::iterator begin() {
		return Set.begin();
	}
	
	set<int>::iterator end() {
		return Set.end();
	}
	
};

int main() {

	return 0;
}
