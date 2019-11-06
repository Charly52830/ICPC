#include<iostream>
using namespace std;

ostream& operator<<(ostream& os, __int128 t) {
	string s="";
	do s.push_back( (t%10)+'0' ); while(t/=10);
	for(int x=0;x<s.size()/2;x++) 
		swap(s[x],s[s.size()-x-1]);
	return os << s;
}

istream& operator >> (istream &in, __int128 &t) {
	string s;
	in >> s;
	t=0;
	for(int i=0;i<s.size();i++) {
		t*=10;
		t+=s[i]-'0';
	}
	return in;
}

__int128 construct(string str_number) {
	__int128 number=0;
	for(int i=0;i<str_number.size();i++)
		number=number*10 + (str_number[i]-'0');
	return number;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	__int128 a,b;
	cin>>a>>b;
	cout<<a<<" "<<b<<endl;
	a=construct("1234567890123456789");
	cout<<a<<endl;
	return 0;
}
