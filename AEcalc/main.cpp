#include <iostream>
#include <string>
#include <vector>
#include "Queue.hpp"
#include "Stack.hpp"
#include "ArithmExpr.hpp"
#include "parser.hpp"
using namespace std;

int main() {
	string s[]{ {"(12e-1 + 13.25e1) -.23e2 * (3 + 2)"}
				,{"(10*(-25)+13.53 - (-0.12))*32 + 32/0.5"}
				,{"a"}
				,{"a = 2"}
				,{"b = 3"}
				,{"a = b"}
				,{"c = 1"}
				,{"a = b = c"}
				,{"c = 4"}
				,{"(a=b)=c"}
				,{"a"}
				,{"b"}
				,{"c"}
	};
	//string s{ ";-24" };
	for (string& c : s) {
		cout << "input: \"" << c << "\"" << endl;
		//auto t = get_ArithmExpr_vector(c);
		auto t1 = lex(c);
		auto t2 = parse(t1);
		/*cout << "infix:" << endl;
		for (auto o : t1)
			cout << o << endl;
		cout << "postfix:" << endl;
		for (auto o : t2)
			cout << o << endl;*/
		//cout << "ArithmExpr:" << endl;
		ArithmExpr a{ t1, t2 };
		cout << "infix: \" ";
		a.print_infix();
		cout << " \"" << endl;
		cout << "postfix: \" ";
		a.print_postfix();
		cout << " \"" << endl;
		cout << "result: "; cout << a.calculate();
		cout << endl << endl;
	}
	return 0;
}
