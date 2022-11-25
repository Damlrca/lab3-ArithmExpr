#include <iostream>
#include <string>
#include <vector>
#include "Queue.hpp"
#include "Stack.hpp"
#include "ArithmExpr.hpp"
#include "parser.hpp"
using namespace std;

int main() {
	string s{ "(12e-1 + 13.25e1) -.23e2 * (3 + 2)" };
	//string s{ "(10*(-25)+13.53 - (-0.12))*32 + 32/0.5" };
	//string s{ ";-24" };
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
	
	cout << "\nArithmExpr:\n" << endl;
	ArithmExpr a{ t1, t2 };
	cout << "infix: \"";
	a.print(cout);
	cout << "\"\n";
	cout << "postfix: \"";
	a.print_postfix(cout);
	cout << "\"\n";
	cout << "result: ";
	cout << a.calculate() << "\n";
	return 0;
}
