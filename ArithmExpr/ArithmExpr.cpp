#include "ArithmExpr.hpp"

using namespace std;

map<string, double> table;

void ArithmExpr::print(ostream& out, const vector<Token>& v) const {
	bool not_empty = false;
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
			return;
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

double get_value(const Token& t) {
	if (t.get_type() == TokenType::Number)
		return t.get_val();
	else if (t.get_type() == TokenType::Name)
		return table[t.get_str()];
	else
		throw calc_exception{ "get_value : unexpected TokenType" };
}

double ArithmExpr::calculate() const {
	Stack<Token> s;
	bool end = false;

	for (const auto& o : postfix) {
		if (end) break;

		switch (o.get_type())
		{
		case TokenType::Number:
		case TokenType::Name:
			s.push(o);
			break;
		case TokenType::Un_Operator:
		{
			if (s.empty())
				throw calc_exception{ "calc : missing operand of unary operation '" + o.get_str() + "'" };
			auto x = s.pop();
			if (o.get_str() == "-")
				s.push(Token{ TokenType::Number, -get_value(x) });
			else if (o.get_str() == "+")
				s.push(Token{ TokenType::Number, +get_value(x) });
			else
				throw calc_exception{ "calc : unknown unary operation '" + o.get_str() + "'" };
			break;
		}
		case TokenType::Bn_Operator:
		{
			if (s.empty())
				throw calc_exception{ "calc : missing operand of binary operation '" + o.get_str() + "'" };
			auto Y = s.pop();
			if (s.empty())
				throw calc_exception{ "calc : missing operand of binary operation '" + o.get_str() + "'" };
			auto X = s.pop();
			if (o.get_str() == "+")
				s.push(Token{ TokenType::Number, get_value(X) + get_value(Y) });
			else if (o.get_str() == "-")
				s.push(Token{ TokenType::Number, get_value(X) - get_value(Y) });
			else if (o.get_str() == "*")
				s.push(Token{ TokenType::Number, get_value(X) * get_value(Y) });
			else if (o.get_str() == "/")
				s.push(Token{ TokenType::Number, get_value(X) / get_value(Y) });
			else
				throw calc_exception{ "calc : unknown binary operation '" + o.get_str() + "'" };
			break;
		}
		case TokenType::Sp_Operator:
		{
			if (o.get_str() != "=")
				throw calc_exception{ "calc : unexpected special operation '" + o.get_str() + "'" };
			if (s.empty())
				throw calc_exception{ "calc : missing operand of special operation '='" };
			auto Y = s.pop();
			if (s.empty())
				throw calc_exception{ "calc : missing operand of special operation '='" };
			auto X = s.pop();
			if (X.get_type() != TokenType::Name)
				throw calc_exception{ "calc : left operand of special operation '=' is not Name" };
			table[X.get_str()] = get_value(Y);
			s.push(X);
			break;
		}
		case TokenType::End:
			end = true;
			break;
		default:
			throw calc_exception{ "calc : unknown TokenType" };
			break;
		}
	}

	if (s.empty())
		throw calc_exception{ "calc : empty expression result" };
	auto t = s.pop();
	if (!s.empty())
		throw calc_exception{ "calc : uncompleted expression" };

	if (t.get_type() != TokenType::Name && t.get_type() != TokenType::Number)
		throw calc_exception{ "calc : incorrect expression" };

	return get_value(t);
}

vector<ArithmExpr> get_ArithmExpr_vector(const string& str, bool debug_mode, ostream& out) {
	vector<ArithmExpr> res;

	auto l = lex(str);

	if (l.empty() || l.back().get_type() != TokenType::End)
		l.push_back(Token{ TokenType::End });

	vector<Token> temp;

	for (auto& o : l) {
		temp.push_back(o);
		if (o.get_type() == TokenType::End) {
			if (debug_mode) {
				out << "lexed Expr No." << res.size() + 1 << " ( " << temp.size() << " Tokens ) :" << endl;
				for (const auto& o : temp)
					out << o << endl;
			}
	
			auto p = parse(temp);

			if (debug_mode) {
				out << "parsed Expr No." << res.size() + 1 << " ( " << p.size() << " Tokens ) :" << endl;
				for (const auto& o : p)
					out << o << endl;
			}
			
			res.push_back(ArithmExpr{ move(temp),move(p) });
			temp.clear();
		}
	}

	return res;
}
