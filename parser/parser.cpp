#include "parser.hpp"

#include <map>

using namespace std;

bool operator>=(const Token& l, const Token& r) {
	// un+ un-
	// * /
	// bn+ bn-
	// ( ) = ???
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
			if (input[i] == '+' || input[i] == '-') {
				if (!res.empty() && (
					res.back().get_type() == TokenType::Name ||
					res.back().get_type() == TokenType::Number ||
					res.back().get_str() == ")" ))
					res.push_back(Token{ TokenType::Bn_Operator, string{input[i]} });
				else
					res.push_back(Token{ TokenType::Un_Operator, string{input[i]} });
			}
			i++;
			break;
		default:
		{
			string temp;
			if ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') {
				// 111.222e-333
				while (i < size && input[i] >= '0' && input[i] <= '9') {
					temp.push_back(input[i]);
					i++;
				}
				if (i < size && input[i] == '.') {
					temp.push_back(input[i]);
					i++;
				}
				while (i < size && input[i] >= '0' && input[i] <= '9') {
					temp.push_back(input[i]);
					i++;
				}
				if (i < size && (input[i] == 'e' || input[i] == 'E')) {
					temp.push_back(input[i]);
					i++;
					if (i < size && input[i] == '-') {
						temp.push_back(input[i]);
						i++;
					}
					while (i < size && input[i] >= '0' && input[i] <= '9') {
						temp.push_back(input[i]);
						i++;
					}
				}
				try { // can stod throw?
					res.push_back(Token{ TokenType::Number, stod(temp) });
				}
				catch (...) {
					throw exception{ "wrong real number format" };
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
					temp.push_back(input[i]);
					i++;
				}
				res.push_back(Token{ TokenType::Name, temp });
			}
			else {
				throw exception{ "unknown symbol" };
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
			while (!s.empty() && s.top() >= input[i])
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

	//int cnt = 0;
	//for (const auto &o : res) {
	//	switch (o.get_type())
	//	{
	//	case TokenType::Number:
	//	case TokenType::Name:
	//		cnt++;
	//		break;
	//	case TokenType::Un_Operator:
	//		if (cnt < 1)
	//			throw -1;
	//		break;
	//	case TokenType::Bn_Operator:
	//		if (cnt < 2)
	//			throw -1;
	//		cnt--;
	//		break;
	//	case TokenType::Sp_Operator:
	//		
	//		break;
	//	case TokenType::End:
	//		//???
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//if (cnt != 1)
	//	throw -1;

	return res;
}
