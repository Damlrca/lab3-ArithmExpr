#include "ArithmExpr.hpp"

using namespace std;

map<string, double> table;

void ArithmExpr::print(ostream& out) {
	string res;
	stringstream ss;
	for (const auto& o : infix) {
		switch (o.get_type())
		{
		case TokenType::Number:
			ss << o.get_val() << " ";
			break;
		case TokenType::Name:
		case TokenType::Un_Operator:
		case TokenType::Bn_Operator:
		case TokenType::Sp_Operator:
			ss << o.get_str() << " ";
			break;
		case TokenType::End:
			break;
		default:
			break;
		}
	}
	res = ss.str();
	if (!res.empty()) res.pop_back();
	out << res;
}

void ArithmExpr::print_postfix(ostream& out) {
	string res;
	stringstream ss;
	for (const auto& o : postfix) {
		switch (o.get_type())
		{
		case TokenType::Number:
			ss << o.get_val() << " ";
			break;
		case TokenType::Name:
		case TokenType::Un_Operator:
		case TokenType::Bn_Operator:
		case TokenType::Sp_Operator:
			ss << o.get_str() << " ";
			break;
		case TokenType::End:
			break;
		default:
			break;
		}
	}
	res = ss.str();
	if (!res.empty()) res.pop_back();
	out << res;
}

double ArithmExpr::calculate() {
	Stack<double> s;

	for (const auto& o : postfix) {
		switch (o.get_type())
		{
		case TokenType::Number:
			s.push(o.get_val());
			break;
		case TokenType::Un_Operator:
			double x;
			x = s.pop();
			if (o.get_str() == "-")
				s.push(-x);
			else
				s.push(x);
			break;
		case TokenType::Bn_Operator:
			double Y;
			Y = s.pop();
			double X;
			X = s.pop();
			if (o.get_str() == "+") {
				s.push(X + Y);
			}
			else if (o.get_str() == "-") {
				s.push(X - Y);
			}
			else if (o.get_str() == "*") {
				s.push(X * Y);
			}
			else if (o.get_str() == "/") {
				s.push(X / Y);
			}
		default:
			break;
		}
	}

	return s.pop();
}

vector<ArithmExpr> get_ArithmExpr_vector(const string& str) {
	vector<ArithmExpr> res;

	return res;
}
