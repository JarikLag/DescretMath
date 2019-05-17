#include <iostream>
#include "String.h"
#include <string>
#include <ctime>

using namespace std;

int main()
{
	String myString;
	string cppString;
	srand(time(0));
	for (int i = 0; i < rand() % 32; ++i) {
		char symb = 'a' + i;
		cppString += symb;
		myString += symb;
	}
	cout << cppString << endl << myString;
	return 0;
}