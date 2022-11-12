#include <iostream>
#include "parser.hpp"
using namespace std;

int main() {
	Stack<Token> s;
	s.push(Token{ TokenType::End });
	s.push(Token{ TokenType::Name, "some_name" });
	s.push(Token{ TokenType::Bn_Operator, "+" });
	while (!s.empty())
		cout << s.pop() << endl;
	return 0;
}
