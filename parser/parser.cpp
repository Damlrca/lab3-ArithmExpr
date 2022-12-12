#include "parser.hpp"

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

vector<Token> lex(const string& input) {
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
					throw calc_exception{ "lex : incorrect real number format : '" + temp + "'"};
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
				throw calc_exception{ "lex : unknown symbol '" + string{input[i]} + "'" };
			}
		}
			break;
		}
	}

	return res;
}

bool Compare_Operators_Tokens(const Token& comp, const Token& basis) {
	if (comp.get_type() != TokenType::Un_Operator &&
		comp.get_type() != TokenType::Bn_Operator &&
		comp.get_type() != TokenType::Sp_Operator)
		throw calc_exception{ "cmp : comparable Token TokenType is not Operator" };
	if (basis.get_type() != TokenType::Un_Operator &&
		basis.get_type() != TokenType::Bn_Operator &&
		basis.get_type() != TokenType::Sp_Operator)
		throw calc_exception{ "cmp : basis Token TokenType is not Operator" };

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

vector<Token> parse(const vector<Token>& input) {
	vector<Token> res;

	int size = input.size();
	Stack<Token> s;

	bool end = false;

	for (int i = 0; i < size; i++) {
		if (end) break;

		switch (input[i].get_type())
		{
		case TokenType::Number:
		case TokenType::Name:
			res.push_back(input[i]);
			break;
		case TokenType::Un_Operator:
		case TokenType::Bn_Operator:
			while (!s.empty() && Compare_Operators_Tokens(s.top(), input[i]))
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
					throw calc_exception{ "parse : missing '(' operator" };
				}
			}
			else if (input[i].get_str() == "=") {
				while (!s.empty() && s.top().get_str() != "(" && s.top().get_str() != "=") {
					res.push_back(s.pop());
				}
				s.push(input[i]);
			}
			else {
				throw calc_exception{ "parse : unknown special operation '" + input[i].get_str() + "'" };
			}
			break;
		case TokenType::End:
			end = true;
			break;
		default:
			throw calc_exception{ "parse : unknown TokenType" };
			break;
		}
	}

	while (!s.empty()) {
		if (s.top().get_str() == "(") {
			throw calc_exception{ "parse : missing ')' operator" };
		}
		res.push_back(s.pop());
	}

	return res;
}

void check_infix_expr_correctness(const vector<Token>& input) {
	int size = input.size();
	int cnt_parenthesis = 0;

	bool end = false;

	for (int i = 0; i < size; i++) {
		if (end) break;

		switch (input[i].get_type())
		{
		case TokenType::Un_Operator:
			if (i + 1 == size || (
				input[i + 1].get_type() != TokenType::Un_Operator &&
				input[i + 1].get_type() != TokenType::Number &&
				input[i + 1].get_type() != TokenType::Name &&
				input[i + 1].get_str() != "("))
				throw calc_exception{ "check_inf : missing operand of unary operation '" + input[i].get_str() + "' : infix[" + to_string(i + 1) + "]" };
			break;
		case TokenType::Bn_Operator:
			if (i == 0 || (
				input[i - 1].get_type() != TokenType::Number &&
				input[i - 1].get_type() != TokenType::Name &&
				input[i - 1].get_str() != ")"))
				throw calc_exception{ "check_inf : missing left operand of binary operation '" + input[i].get_str() + "' : infix[" + to_string(i + 1) + "]" };
			if (i + 1 == size || (
				input[i + 1].get_type() != TokenType::Un_Operator &&
				input[i + 1].get_type() != TokenType::Number &&
				input[i + 1].get_type() != TokenType::Name &&
				input[i + 1].get_str() != "("))
				throw calc_exception{ "check_inf : missing right operand of binary operation '" + input[i].get_str() + "' : infix[" + to_string(i + 1) + "]" };
			break;
		case TokenType::Sp_Operator:
			if (input[i].get_str() == "(") {
				cnt_parenthesis++;
				if (i > 0 && (
					input[i - 1].get_type() == TokenType::Number ||
					input[i - 1].get_type() == TokenType::Name ||
					input[i - 1].get_str() == ")") )
					throw calc_exception{ "check_inf : missing operator between Token ans '(' : infix[" + to_string(i + 1) + "]" };
			}
			else if (input[i].get_str() == ")") {
				if (cnt_parenthesis == 0)
					throw calc_exception{ "check_inf : missing '(' operator : infix[" + to_string(i + 1) + "]" };
				cnt_parenthesis--;
				if (input[i - 1].get_str() == "(")
					throw calc_exception{ "check_inf : empty '()' : infix[" + to_string(i + 1) + "]" };
			}
			else if (input[i].get_str() == "=") {
				if (i == 0 || input[i - 1].get_type() != TokenType::Name)
					throw calc_exception{ "check_inf : missing left operand of special operation '=' : infix[" + to_string(i + 1) + "]" };
				if (i + 1 == size || (
					input[i + 1].get_type() != TokenType::Un_Operator &&
					input[i + 1].get_type() != TokenType::Number &&
					input[i + 1].get_type() != TokenType::Name &&
					input[i + 1].get_str() != "("))
					throw calc_exception{ "check_inf : missing right operand of special operation '=' : infix[" + to_string(i + 1) + "]" };
			}
			else {
				throw calc_exception{ "check_inf : unknown special operation : infix[" + to_string(i + 1) + "]" };
			}
			break;
		case TokenType::Number:
		case TokenType::Name:
			if (i > 0 && (
				input[i - 1].get_type() == TokenType::Name ||
				input[i - 1].get_type() == TokenType::Number ||
				input[i - 1].get_str() == ")"))
				throw calc_exception{ "check_inf : wrong Token before operand : infix[" + to_string(i + 1) + "]" };
			if (i + 1 < size && (
				input[i + 1].get_type() == TokenType::Name ||
				input[i + 1].get_type() == TokenType::Number ||
				input[i + 1].get_type() == TokenType::Un_Operator ||
				input[i + 1].get_str() == "("))
				throw calc_exception{ "check_inf : wrong Token after operand : infix[" + to_string(i + 1) + "]" };
			break;
		case TokenType::End:
			end = true;
			break;
		default:
			throw calc_exception{ "check_inf : unknown TokenType : infix[" + to_string(i + 1) + "]" };
			break;
		}
	}
	if (cnt_parenthesis > 0)
		throw calc_exception{ "check_inf : missing ')' operator" };
}

void check_postfix_expr_correctness(const vector<Token>& input) {
	Stack<Token> test;
	bool end = false;

	int i = 0;
	for (const auto& o : input) {
		if (end) break;

		switch (o.get_type())
		{
		case TokenType::Number:
		case TokenType::Name:
			test.push(o);
			break;
		case TokenType::Un_Operator:
		{
			if (test.empty())
				throw calc_exception{ "check_post : missing operand of unary operation '" + o.get_str() + "' : postfix[" + to_string(i + 1) + "]" };
			auto x = test.pop();
			test.push(Token{ TokenType::Number, 0 });
			break;
		}
		case TokenType::Bn_Operator:
		{
			if (test.empty())
				throw calc_exception{ "check_post : missing operand of binary operation '" + o.get_str() + "' : postfix[" + to_string(i + 1) + "]" };
			auto Y = test.pop();
			if (test.empty())
				throw calc_exception{ "check_post : missing operand of binary operation '" + o.get_str() + "' : postfix[" + to_string(i + 1) + "]" };
			auto X = test.pop();
			test.push(Token{ TokenType::Number, 0 });
			break;
		}
		case TokenType::Sp_Operator:
		{
			if (o.get_str() != "=")
				throw calc_exception{ "check_post : unexpected special operation '" + o.get_str() + "' : postfix[" + to_string(i + 1) + "]" };
			if (test.empty())
				throw calc_exception{ "check_post : missing operand of special operation '=' : postfix[" + to_string(i + 1) + "]" };
			auto Y = test.pop();
			if (test.empty())
				throw calc_exception{ "check_post : missing operand of special operation '=' : postfix[" + to_string(i + 1) + "]" };
			auto X = test.pop();
			if (X.get_type() != TokenType::Name)
				throw calc_exception{ "check_post : left operand of special operation '=' is not Name : postfix[" + to_string(i + 1) + "]" };
			test.push(X);
			break;
		}
		case TokenType::End:
			end = true;
			break;
		default:
			throw calc_exception{ "check_post : unknown TokenType : postfix[" + to_string(i + 1) + "]" };
			break;
		}

		i++;
	}

	if (test.empty())
		throw calc_exception{ "check_post : empty expression result" };
	auto t = test.pop();
	if (!test.empty())
		throw calc_exception{ "check_post : uncompleted expression" };

	if (t.get_type() != TokenType::Name && t.get_type() != TokenType::Number)
		throw calc_exception{ "check_post : incorrect expression" };
}
