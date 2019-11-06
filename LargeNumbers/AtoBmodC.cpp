#include<iostream>
using namespace std;

typedef long long ll;

ll binary_exp(ll a,int b,ll c) {
	int n=32,x;
	ll TMP[n],k=1;
	TMP[0]=a%c;
	for(x=1;x<n;x++)
		TMP[x]=TMP[x-1]*TMP[x-1]%c;
	for(x=0;x<n;x++) if(b&(1<<x))
		k=k*TMP[x]%c;
    return k;
}

int main() {
	ll a,c;
	int b;
    cin>>a>>b>>c;
    cout<<binary_exp(a,b,c)<<endl;
    return 0;
}
