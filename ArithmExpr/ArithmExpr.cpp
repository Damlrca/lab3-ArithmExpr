#include "ArithmExpr.hpp"

using namespace std;

map<string, double> table;

void ArithmExpr::print(ostream& out, const vector<Token>& v) const {
	bool not_empty = 0;
	stringstream ss;
	for (const auto& o : v) {
		switch (o.get_type())
		{
		case TokenType::Number:
			if (not_empty)
				ss << " ";
			else
				not_empty = true;
			ss << o.get_val();
			break;
		case TokenType::Name:
		case TokenType::Un_Operator:
		case TokenType::Bn_Operator:
		case TokenType::Sp_Operator:
			if (not_empty)
				ss << " ";
			else
				not_empty = true;
			ss << o.get_str();
			break;
		case TokenType::End:
			break;
		default:
			break;
		}
	}
	out << ss.str();
}

void ArithmExpr::print_infix(ostream& out) const {
	print(out, infix);
}

void ArithmExpr::print_postfix(ostream& out) const {
	print(out, postfix);
}

double get_value(Token t) {
	if (t.get_type() == TokenType::Number)
		return t.get_val();
	else if (t.get_type() == TokenType::Name)
		return table[t.get_str()];
	else
		throw -1;
}

double ArithmExpr::calculate() {
	Stack<Token> s;

	for (const auto& o : postfix) {
		switch (o.get_type())
		{
		case TokenType::Number:
		case TokenType::Name:
			s.push(o);
			break;
		case TokenType::Un_Operator:
		{
			auto x = s.pop();
			if (o.get_str() == "-")
				s.push(Token{ TokenType::Number, -get_value(x) });
			else //if (o.get_str() == "+")
				s.push(Token{ TokenType::Number, +get_value(x) });
			break;
		}
		case TokenType::Bn_Operator:
		{
			if (s.empty())
				throw -1;
			auto Y = s.pop();
			if (s.empty())
				throw -1;
			auto X = s.pop();
			if (o.get_str() == "+")
				s.push(Token{ TokenType::Number, get_value(X) + get_value(Y) });
			else if (o.get_str() == "-")
				s.push(Token{ TokenType::Number, get_value(X) - get_value(Y) });
			else if (o.get_str() == "*")
				s.push(Token{ TokenType::Number, get_value(X) * get_value(Y) });
			else if (o.get_str() == "/")
				s.push(Token{ TokenType::Number, get_value(X) / get_value(Y) });
			break;
		}
		case TokenType::Sp_Operator:
		{
			if (o.get_str() != "=")
				throw -1;
			if (s.empty())
				throw -1;
			auto Y = s.pop();
			if (s.empty())
				throw -1;
			auto X = s.pop();
			if (X.get_type() != TokenType::Name)
				throw -1;
			table[X.get_str()] = get_value(Y);
			s.push(X);
			break;
		}
		default:
			break;
		}
	}

	return get_value(s.pop());
}

vector<ArithmExpr> get_ArithmExpr_vector(const string& str) {
	vector<ArithmExpr> res;

	return res;
}
