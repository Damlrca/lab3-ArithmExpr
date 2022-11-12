#ifndef __CALC_PARSER_HPP__
#define __CALC_PARSER_HPP__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class TokenType {
	Operator,	// +(binary) -(binary) +(unary) -(unary) * / ( ) =
	Literal,	// const value
	Name,		// variable name
	End		// ; '\n' EOF
};

class Token {
private:
	TokenType type;
	string str;
	double val;
public:
	Token(TokenType t, const string& s) : type{ t }, str{ s }, val{} {}
	Token(TokenType t, double v) : type{ t }, str{}, val{ v } {}
	string get_str() const { return str; }
	TokenType get_type() const { return type; }
	double get_val() const { return val; }
};

ostream& operator<<(ostream& out, const Token& t) {
	out << "{";
	switch (t.get_type())
	{
	case TokenType::Operator:
		out << t.get_str() << ", operator";
		break;
	case TokenType::Literal:
		out << t.get_val() << ", literal";
	case TokenType::Name:
		out << t.get_str() << ", name";
		break;
	case TokenType::End:
		out << "NONE, end";
		break;
	default:
		out << "ERROR";
		break;
	}
	out << "}";
	return out;
}

vector<Token> lex(string input) {
	vector<Token> res;

	return res;
}

#endif // !__CALC_PARSER_HPP__
