#include <iostream>
#include <string>
#include <vector>
#include "Queue.hpp"
#include "Stack.hpp"
#include "ArithmExpr.hpp"
#include "parser.hpp"
using namespace std;

int main() {
	string s{ "(12 + 13) / -23 * (3 + 2)" };
	cout << "input: \"" << s << "\"" << endl;
	//auto t = get_ArithmExpr_vector(s);
	cout << "infix:" << endl;
	auto t1 = lex(s);
	for (auto o : t1)
		cout << o << endl;
	cout << "postfix:" << endl;
	auto t2 = parse(t1);
	for (auto o : t2)
		cout << o << endl;
	cout << "result:" << endl;
	Stack<double> st;
	for (auto o : t2) {
		switch (o.get_type())
		{
		case TokenType::Number:
			st.push(o.get_val());
			break;
		case TokenType::Un_Operator:
			double x;
			x = st.pop();
			if (o.get_str() == "-")
				st.push(-x);
			else
				st.push(x);
			break;
		case TokenType::Bn_Operator:
			double Y;
			Y = st.pop();
			double X;
			X = st.pop();
			if (o.get_str() == "+") {
				st.push(X + Y);
			}
			else if (o.get_str() == "-") {
				st.push(X - Y);
			}
			else if (o.get_str() == "*") {
				st.push(X * Y);
			}
			else if (o.get_str() == "/") {
				st.push(X / Y);
			}
		default:
			break;
		}
	}
	cout << st.pop() << endl;
	return 0;
}
