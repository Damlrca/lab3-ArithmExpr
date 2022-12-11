#include <iostream>
#include <string>
#include <vector>
#include "ArithmExpr.hpp"
#include "parser.hpp"

using namespace std;

int main() {
	bool debug_mode = false;
	while (true) {
		string command; cin >> command;
		string expr; getline(cin, expr);
		if (command == "calc") {
			try {
				auto t1 = lex(expr);
				if (debug_mode) {
					cout << "infix (lex):" << endl;
					for (auto& o : t1)
						cout << o << endl;
				}

				auto t2 = parse(t1);
				if (debug_mode) {
					cout << "postfix (parse):" << endl;
					for (auto& o : t2)
						cout << o << endl;
				}

				cout << "ArithmExpr:" << endl;
				ArithmExpr a{ t1, t2 };
				cout << "infix: \" ";
				a.print_infix();
				cout << " \"" << endl;
				cout << "postfix: \" ";
				a.print_postfix();
				cout << " \"" << endl;
				cout << "result: "; cout << a.calculate();
			}
			catch (calc_exception& c) {
				cout << "exception: " << c.get_str();
			}
		}
		else if (command == "debug") {
			debug_mode = !debug_mode;
			cout << "debugging mode is ";
			cout << (debug_mode ? "on" : "off");
		}
		else if (command == "exit") {
			break;
		}
		else {
			cout << "unknown command";
		}
		cout << endl << endl;
	}
	return 0;
}
