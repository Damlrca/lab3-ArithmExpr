#ifndef __CALC_PARSER_HPP__
#define __CALC_PARSER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "Stack.hpp"
#include "Queue.hpp"

enum class TokenType {
	Un_Operator,	//str: +(unary) -(unary)
	Bn_Operator,	//str: +(binary) -(binary) * /
	Sp_Operator,	//str: ( ) =
	Number,			//val: real value
	Name,			//str: variable name
	End				// no: ; '\n' EOF
};

class Token {
private:
	TokenType type;
	std::string str;
	double val;
public:
	explicit Token(TokenType t) : type{ t }, str{}, val{} {
		if (type != TokenType::End)
			throw -1;
	}
	explicit Token(TokenType t, const std::string& s) : type{ t }, str{ s }, val{} {
		switch (t)
		{
		case TokenType::Un_Operator:
			if (s != "+" && s != "-")
				throw -1;
			break;
		case TokenType::Bn_Operator:
			if (s != "+" && s != "-" && s != "*" && s != "/")
				throw -1;
			break;
		case TokenType::Sp_Operator:
			if (s != "(" && s != ")" && s != "=")
				throw -1;
			break;
		case TokenType::Name:
			//check if is uncorrect?
			break;
		default:
			throw -1;
			break;
		}
	}
	explicit Token(TokenType t, double v) : type{ t }, str{}, val{ v } {
		if (type != TokenType::Number)
			throw -1;
	}
	std::string get_str() const { return str; }
	TokenType get_type() const { return type; }
	double get_val() const { return val; }
};

std::ostream& operator<<(std::ostream& out, const Token& t);

std::vector<Token> lex(std::string);

std::vector<Token> parse(std::vector<Token>);

#endif // !__CALC_PARSER_HPP__
