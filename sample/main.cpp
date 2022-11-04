#include <iostream>
#include "parser.hpp"
using namespace std;

int main() {
	cout << "Hello world" << endl;
	A<int> a(10);
	cout << a.get() << endl;
	for (int i = 0; i < 10; i++)
		cout << a.pop() << " ";
	return 0;
}
