#include <iostream>
#include <string>
#include <vector>
#include "ArithmExpr.hpp"
#include "parser.hpp"

using namespace std;

int main() {
	bool debug_mode = false;
	bool print_mode = false;
	while (true) {
		string command; cin >> command;
		string expr; getline(cin, expr);
		if (command == "calc") {
			try {
				auto temp = get_ArithmExpr_vector(expr, debug_mode);
				if (!debug_mode) {
					int number = 0;
					for (const auto& o : temp) {
						cout << "Expr No." << ++number << ": ";
						if (print_mode) {
							cout << endl;
							cout << "infix: \" ";
							o.print_infix();
							cout << " \"" << endl;
							cout << "postfix: \" ";
							o.print_postfix();
							cout << " \"" << endl;
						}
						cout << "result: ";
						cout << o.calculate() << endl;
					}
				}
			}
			catch (calc_exception& c) {
				cout << "exception: " << c.get_str() << endl;
			}
			cout << endl;
		}
		else if (command == "debug") {
			debug_mode = !debug_mode;
			cout << "debugging mode is ";
			cout << (debug_mode ? "on" : "off") << endl << endl;
		}
		else if (command == "print") {
			print_mode = !print_mode;
			cout << "print mode is ";
			cout << (print_mode ? "on" : "off") << endl << endl;
		}
		else if (command == "exit") {
			break;
		}
		else {
			cout << "unknown command" << endl << endl;
		}
	}
	return 0;
}
