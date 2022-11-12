#include <iostream>
#include "parser.hpp"
using namespace std;

int main() {
	cout << "Hello world" << endl;
	Token t{ TokenType::Name, "test_name" };
	cout << t;
	return 0;
}
