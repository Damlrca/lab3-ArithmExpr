#include "parser.hpp"

#include <map>

using namespace std;

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
		out << "END TOKEN";
		break;
	default:
		out << "INCORRECT TOKEN";
		break;
	}
	out << "}";
	return out;
}

bool Operator_cmp(const Token& comp, const Token& basis) {
	if (comp.get_type() != TokenType::Un_Operator &&
		comp.get_type() != TokenType::Bn_Operator &&
		comp.get_type() != TokenType::Sp_Operator)
		throw cmp_error{ "Operator_cmp() : comparable Token TokenType is not Operator" };
	if (basis.get_type() != TokenType::Un_Operator &&
		basis.get_type() != TokenType::Bn_Operator &&
		basis.get_type() != TokenType::Sp_Operator)
		throw cmp_error{ "Operator_cmp() : basis Token TokenType is not Operator" };
	
	if (comp.get_type() == TokenType::Sp_Operator)
		return false;
	if (basis.get_type() == TokenType::Sp_Operator)
		return false;

	if (basis.get_type() == TokenType::Un_Operator)
		return false;
	if (comp.get_type() == TokenType::Un_Operator)
		return true;

	if (comp.get_str() == "*" || comp.get_str() == "/")
		return true;
	if (basis.get_str() == "*" || basis.get_str() == "/")
		return false;

	return true;
}

vector<Token> lex(string input) {
	vector<Token> res;

	int size = input.size();

	for (int i = 0; i < size;) {
		switch (input[i])
		{
		case ' ': case '\t':
			i++;
			break;
		case ';': case '\n':
			res.push_back(Token{ TokenType::End });
			i++;
			break;
		case '*': case '/':
			res.push_back(Token{ TokenType::Bn_Operator, string{input[i]} });
			i++;
			break;
		case '(': case ')': case '=':
			res.push_back(Token{ TokenType::Sp_Operator, string{input[i]} });
			i++;
			break;
		case '+': case '-':
			if (!res.empty() && (
				res.back().get_type() == TokenType::Number ||
				res.back().get_type() == TokenType::Name ||
				res.back().get_str() == ")" ))
				res.push_back(Token{ TokenType::Bn_Operator, string{input[i]} });
			else
				res.push_back(Token{ TokenType::Un_Operator, string{input[i]} });
			i++;
			break;
		default:
		{
			string temp;
			if ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') {
				// 111.222e-333
				while (i < size && input[i] >= '0' && input[i] <= '9') {
					temp += input[i];
					i++;
				}
				if (i < size && input[i] == '.') {
					temp += input[i];
					i++;
				}
				while (i < size && input[i] >= '0' && input[i] <= '9') {
					temp += input[i];
					i++;
				}
				if (i < size && (input[i] == 'e' || input[i] == 'E')) {
					temp += input[i];
					i++;
					if (i < size && input[i] == '-') {
						temp += input[i];
						i++;
					}
					while (i < size && input[i] >= '0' && input[i] <= '9') {
						temp += input[i];
						i++;
					}
				}
				try {
					res.push_back(Token{ TokenType::Number, stod(temp) });
				}
				catch (...) {
					throw lexer_error{ "lex : incorrect real number format" };
				}
			}
			else if ( input[i] == '_' ||
				(input[i] >= 'A' && input[i] <= 'Z') ||
				(input[i] >= 'a' && input[i] <= 'z') ) {
				while (i < size && 
					( input[i] == '_' ||
					(input[i] >= 'A' && input[i] <= 'Z') ||
					(input[i] >= 'a' && input[i] <= 'z') ||
					(input[i] >= '0' && input[i] <= '9') ) ) {
					temp += input[i];
					i++;
				}
				res.push_back(Token{ TokenType::Name, temp });
			}
			else {
				throw lexer_error{ "lex : unknown symbol" };
			}
		}
			break;
		}
	}

	return res;
}

vector<Token> parse(const vector<Token>& input) {
	vector<Token> res;

	int size = input.size();
	Stack<Token> s;

	for (int i = 0; i < size; i++) {
		switch (input[i].get_type())
		{
		case TokenType::Number:
		case TokenType::Name:
			res.push_back(input[i]);
			break;
		case TokenType::Un_Operator:
		case TokenType::Bn_Operator:
			while (!s.empty() && Operator_cmp(s.top(), input[i]))
				res.push_back(s.pop());
			s.push(input[i]);
			break;
		case TokenType::Sp_Operator:
			if (input[i].get_str() == "(") {
				s.push(input[i]);
			}
			else if (input[i].get_str() == ")") {
				while (!s.empty() && s.top().get_str() != "(") {
					res.push_back(s.pop());
				}
				if (!s.empty() && s.top().get_str() == "(") {
					s.pop();
				}
				else {
					throw exception{ "missing \"(\" operator" };
				}
			}
			else if (input[i].get_str() == "=") {
				while (!s.empty() && s.top().get_str() != "(" && s.top().get_str() != "=") {
					res.push_back(s.pop());
				}
				s.push(input[i]);
				// throws when what ???
			}
			break;
		case TokenType::End:
			//???
			break;
		default:
			break;
		}
	}

	while (!s.empty()) {
		if (s.top().get_str() == "(") {
			throw exception{ "missing \")\" operator" };
		}
		res.push_back(s.pop());
	}
	
	return res;
}
