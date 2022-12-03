#include "ArithmExpr.hpp"

using namespace std;

map<string, double> table;

void ArithmExpr::print(ostream& out, const vector<Token>& v) const {
	bool not_empty = 0;
	for (const auto& o : v) {
		switch (o.get_type())
		{
		case TokenType::Number:
			if (not_empty)
				out << " ";
			else
				not_empty = true;
			out << o.get_val();
			break;
		case TokenType::Name:
		case TokenType::Un_Operator:
		case TokenType::Bn_Operator:
		case TokenType::Sp_Operator:
			if (not_empty)
				out << " ";
			else
				not_empty = true;
			out << o.get_str();
			break;
		case TokenType::End:
			break;
		default:
			break;
		}
	}
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
		throw ArithmExpr_error{ "get_value : unexpected Token" };
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
			if (s.empty())
				throw ArithmExpr_error{ "ArithmExpr::calculate() : missing operand of unary operation '" + o.get_str() + "'" };
			auto x = s.pop();
			if (o.get_str() == "-")
				s.push(Token{ TokenType::Number, -get_value(x) });
			else if (o.get_str() == "+")
				s.push(Token{ TokenType::Number, +get_value(x) });
			break;
		}
		case TokenType::Bn_Operator:
		{
			if (s.empty())
				throw ArithmExpr_error{ "ArithmExpr::calculate() : missing operand of binary operation '" + o.get_str() + "'" };
			auto Y = s.pop();
			if (s.empty())
				throw ArithmExpr_error{ "ArithmExpr::calculate() : missing operand of binary operation '" + o.get_str() + "'" };
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
				throw ArithmExpr_error{ "ArithmExpr::calculate() : unexpected special operation '" + o.get_str() + "'" };
			if (s.empty())
				throw ArithmExpr_error{ "ArithmExpr::calculate() : missing operand of special operation '" + o.get_str() + "'" };
			auto Y = s.pop();
			if (s.empty())
				throw ArithmExpr_error{ "ArithmExpr::calculate() : missing operand of special operation '" + o.get_str() + "'" };
			auto X = s.pop();
			if (X.get_type() != TokenType::Name)
				throw ArithmExpr_error{ "ArithmExpr::calculate() : left operand of special operation '" + o.get_str() + "' is not Name" };
			table[X.get_str()] = get_value(Y);
			s.push(X);
			break;
		}
		case TokenType::End:
			break;
		default:
			break;
		}
	}
	if (s.empty())
		throw parser_error{ "parse : empty expression result" };
	auto t = s.pop();
	if (!s.empty())
		throw parser_error{ "parse : uncompleted expression" };
	if (t.get_type() != TokenType::Name && t.get_type() != TokenType::Number)
		throw parser_error{ "parse : incorrect expression" };
	return get_value(t);
}

vector<ArithmExpr> get_ArithmExpr_vector(const string& str, bool debug_mode) {
	vector<ArithmExpr> res;

	return res;
}
