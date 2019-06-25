#include<iostream>
#include<math.h>
using namespace std;
int funcion(int a,int b,int c) {
    int n=(int)(log(b)/log(2))+1,napadas[n],k=1,x;
    napadas[0]=a%c;
    for(x=1;x<n;x++)
        napadas[x]=napadas[x-1]*napadas[x-1]%c;
    for(x=0;x<n;x++)
        if(b&(1<<x))
            k=(k*napadas[x])%c;
    return k;
}

int main() {
    int a,b,c;
    cin>>a>>b>>c;
    cout<<funcion(a,b,c);
    return 0;
}
