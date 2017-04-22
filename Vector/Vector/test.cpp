#include <iostream>
#include "vector.h"
using namespace std;

int main()
{
	Vector <int> lol;


	for (int i = 0; i < lol.numCapacity(); i++)
	{
		cout << lol[i] << endl;
	}
	// Quit the program
	{
		char quit;
		cin >> quit;
	}
}