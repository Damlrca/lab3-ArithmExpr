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

vector<Token> parse(vector<Token> input) {
	vector<Token> res;

	return res;
}
