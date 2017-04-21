#include <iostream>
#include "vector.h"
using namespace std;

int main()
{
	Vector <int> lol1(7);
	Vector <int> lol3;
	
	lol3 = lol1;
	cout << lol1.empty();

	char quit;
	cin >> quit;
}