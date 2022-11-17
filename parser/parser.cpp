#include "parser.hpp"

#include <map>

using namespace std;

bool operator>=(const Token& l, const Token& r) {
	if (l.get_type() == TokenType::Sp_Operator)
		return false;
	if (l.get_type() == TokenType::Un_Operator)
		return true;
	if (r.get_type() == TokenType::Un_Operator)
		return false;
	if (l.get_str() == "*" || l.get_str() == "/")
		return true;
	if (r.get_str() == "+" || r.get_str() == "-");
	return false;
}

ostream& operator<<(ostream& out, const Token& t) {
	out << "{";
	switch (t.get_type())
	{
	case TokenType::Un_Operator:
		out << t.get_str() << ", unary operator";
		break;
	case TokenType::Bn_Operator:
		out << t.get_str() << ", binary operator";
		break;
	case TokenType::Sp_Operator:
		out << t.get_str() << ", special operator";
		break;
	case TokenType::Number:
		out << t.get_val() << ", number";
		break;
	case TokenType::Name:
		out << t.get_str() << ", name";
		break;
	case TokenType::End:
		out << "END, end";
		break;
	default:
		out << "INCORRECT TOKEN";
		break;
	}
	out << "}";
	return out;
}

vector<Token> lex(string input) {
	vector<Token> res;

	input += " ";

	string tmp;
	int in_numb = 0;

	for (char c : input) {
		switch (c) {
		case ' ':
			if (in_numb) {
				res.push_back(Token{TokenType::Number, stod(tmp)});
				in_numb = 0;
				tmp.clear();
			}
			break;
		case '+': case '-': case '*': case '/':
			if (in_numb) {
				res.push_back(Token{ TokenType::Number, stod(tmp) });
				in_numb = 0;
				tmp.clear();
			}
			if ((c == '+' || c == '-') && (res.size() == 0 || res.back().get_type() != TokenType::Number)) {
				res.push_back(Token{ TokenType::Un_Operator, string{c} });
			}
			else {
				res.push_back(Token{ TokenType::Bn_Operator, string{c} });
			}
			break;
		case '(': case ')':
			if (in_numb) {
				res.push_back(Token{ TokenType::Number, stod(tmp) });
				in_numb = 0;
				tmp.clear();
			}
			res.push_back(Token{ TokenType::Sp_Operator, string{c} });
			break;
		default:
			if (c >= '0' && c <= '9') {
				tmp += c;
				in_numb = 1;
			}
			else {
				// error
				break;
			}
			break;
		}
	}

	return res;
}

vector<Token> parse(const vector<Token>& input) {
	vector<Token> res;

	Stack<Token> s;

	for (auto o : input) {
		switch (o.get_type())
		{
		case TokenType::Number:
			res.push_back(o);
			break;
		case TokenType::Bn_Operator:
		case TokenType::Un_Operator:
			while (!s.empty() && s.top() >= o) {
				res.push_back(s.pop());
			}
			s.push(o);
			break;
		case TokenType::Sp_Operator:
			if (o.get_str() == "(") {
				s.push(o);
			}
			else if (o.get_str() == ")") {
				while (s.top().get_str() != "(") {
					res.push_back(s.pop());
				}
				s.pop();
			}
			break;
		default:
			break;
		}
	}

	while (!s.empty())
		res.push_back(s.pop());

	return res;
}
