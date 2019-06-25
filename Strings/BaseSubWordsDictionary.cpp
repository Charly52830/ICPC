#include<map>
#include<algorithm>
#include<vector>
#include<iostream>
#define mp make_pair
using namespace std;

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef map<int,int>::iterator mit;

/*
*	Dictionary of static sub words.
*	Construction: 	O(n log n)
*	Operations	:	O(log n)
*	Assign unique identifiers to each sub word of a given word.
*	Allow us to compare subwords in O(1) by comparing lexicographycally their identifiers.
*/
class BaseSubWordsDictionary {

	private:
	vector<vi> dictionary;
	int alphabetSize;

	//O(n log n)
	vi normalize(vi v) {
		map<int,int> mapa;
		for(auto i:v) 
			mapa[i]=1;

		for(mit it=mapa.begin();it!=mapa.end();it++) {
		
			mit tmp_it=it;
			tmp_it++;

			if( tmp_it != mapa.end() )
				mapa[tmp_it->first]+=it->second;
			else
				alphabetSize=it->second;
		}

		for(int i=0;i<v.size();i++) 
			v[i]=mapa[v[i]]-1;
		return v;
	}

	public:

	//O(n log n)
	BaseSubWordsDictionary(vi v) {
		int i,j,logTam,tam=v.size();
		//Normalize and set alphabetSize
		v=normalize(v);
		
		for(i=0;i<32;i++)
			if(tam&(1<<i))
				logTam=i;
		logTam++;
		dictionary.resize(logTam);
		for(i=0;i<tam;i++)
			dictionary[0].push_back(v[i]);

		for(i=1;i<logTam;i++) {
			vector< vector< pii > > A;
			A.resize(alphabetSize);
			int countingArray[alphabetSize];
			for(j=0;j<alphabetSize;j++)
				countingArray[j]=0;

			int levelTam=tam-(1<<i)+1;
			int B[levelTam];
			dictionary[i].resize(levelTam);
			for(j=0;j<levelTam;j++) {
				int a=dictionary[i-1][j];
				int b=dictionary[i-1][j+(1<<(i-1))];
				countingArray[a]++;
				A[b].push_back( mp(a,j) );
			}
			for(j=1;j<alphabetSize;j++)
				countingArray[j]+=countingArray[j-1];

			for(j=alphabetSize-1;j>=0;j--) {
				for(auto p:A[j]) {
					dictionary[i][p.second]=countingArray[p.first]-1;
					B[--countingArray[p.first]]=p.second;
				}
			}

			int cont=0;
			int previous_a=dictionary[i-1][B[0]];
			int previous_b=dictionary[i-1][B[0]+(1<<(i-1))];

			for(j=1;j<levelTam;j++) {
				int a=dictionary[i-1][B[j]];
				int b=dictionary[i-1][B[j]+(1<<(i-1))];
				cont+= a==previous_a && b==previous_b;
				dictionary[i][B[j]]-=cont;
				swap(a,previous_a);
				swap(b,previous_b);
			}
			alphabetSize=levelTam-cont;
		}
	}
	
	//O(log n)
	pii hash(int i,int j) {
		int tam=j-i+1,level=0;
		for(int x=0;x<32;x++) 
			if(tam&(1<<x))
				level=x;
		return mp(dictionary[level][i],dictionary[level][j-(1<<level)+1]);
	}
	
};

int main() {
	int n,x;
	string s="anitalavalatina";
	vi v;
	v.resize(s.size());
	for(x=0;x<s.size();x++)
		v[x]=s[x]-'a';
	BaseSubWordsDictionary dic(v);
	pii a=dic.hash(0,5),b=dic.hash(9,14);
	cout<<a.first<<" "<<a.second<<endl;
	cout<<b.first<<" "<<b.second<<endl;	
	return 0;
}

/*
	*	Output:
	*	2 5
	*	6 10
*/
