#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
#include "parser.hpp"
using namespace std;

int main() {
	cout << "Stack" << endl;
	Stack<Token> s;
	s.push(Token{ TokenType::End });
	s.push(Token{ TokenType::Name, "some_name" });
	s.push(Token{ TokenType::Bn_Operator, "+" });
	while (!s.empty())
		cout << s.pop() << endl;
	cout << "Queue" << endl;
	Queue<Token> q;
	q.push(Token{ TokenType::End });
	q.push(Token{ TokenType::Name, "some_name" });
	q.push(Token{ TokenType::Bn_Operator, "+" });
	while (!q.empty())
		cout << q.pop() << endl;
	return 0;
}
