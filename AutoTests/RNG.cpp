#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

int main() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> disN(1 , 100000),dis2(1,1000000000);
	int n=disN(gen),x,y;
	cout<<n<<endl;
	return 0;
}
