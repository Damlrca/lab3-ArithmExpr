#ifndef __CALC_PARSER_HPP__
#define __CALC_PARSER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "Stack.hpp"

class calc_exception {
	std::string s;
public:
	calc_exception(const std::string& _s) : s{_s} {}
	std::string get_str() const { return s; };
};

enum class TokenType {
	Un_Operator,  //str: +(unary) -(unary)
	Bn_Operator,  //str: +(binary) -(binary) * /
	Sp_Operator,  //str: ( ) =
	Number,       //val: real value
	Name,         //str: variable name
	End           // no: ; '\n'
};

class Token {
private:
	TokenType type;
	std::string str;
	double val;
public:
	explicit Token(TokenType t) : type{ t }, str{}, val{} {
		if (type != TokenType::End)
			throw calc_exception{ "Token(TokenType) : TokenType is not TokenType::End" };
	}
	explicit Token(TokenType t, const std::string& s) : type{ t }, str{ s }, val{} {
		switch (t)
		{
		case TokenType::Un_Operator:
			if (s != "+" && s != "-")
				throw calc_exception{ "Token(TokenType, string) : '" + s + "' is not supported unary operation"};
			break;
		case TokenType::Bn_Operator:
			if (s != "*" && s != "/" && s != "+" && s != "-")
				throw calc_exception{ "Token(TokenType, string) : '" + s + "' is not supported binary operation" };
			break;
		case TokenType::Sp_Operator:
			if (s != "(" && s != ")" && s != "=")
				throw calc_exception{ "Token(TokenType, string) : '" + s + "' is not supported special operation" };
			break;
		case TokenType::Name:
		{
			if (s.empty())
				throw calc_exception{ "Token(TokenType, string) : empty name" };
			if (!( s.front() == '_' ||
				(s.front() >= 'A' && s.front() <= 'Z') ||
				(s.front() >= 'a' && s.front() <= 'z')) )
				throw calc_exception{ "Token(TokenType, string) : uncorrect first character in name"};
			for (int i = 0; i < s.size(); i++)
				if (!(s[i] == '_' ||
					(s[i] >= 'A' && s[i] <= 'Z') ||
					(s[i] >= 'a' && s[i] <= 'z') ||
					(s[i] >= '0' && s[i] <= '9')))
					throw calc_exception{ "Token(TokenType, string) : uncorrect character [" + std::to_string(i + 1) + "] in name" };
		}
			break;
		default:
			throw calc_exception{ "Token(TokenType, string) : unknown TokenType" };
			break;
		}
	}
	explicit Token(TokenType t, double v) : type{ t }, str{}, val{ v } {
		if (type != TokenType::Number)
			throw calc_exception{ "Token(TokenType, double) : TokenType is not TokenType::Number" };
	}
	TokenType get_type() const { return type; }
	std::string get_str() const { return str; }
	double get_val() const { return val; }
};

std::ostream& operator<<(std::ostream& out, const Token& t);

std::vector<Token> lex(const std::string& input);

bool Compare_Operators_Tokens(const Token& l, const Token& r);

std::vector<Token> parse(const std::vector<Token>&);

void check_infix_expr_correctness(const std::vector<Token>&);

void check_postfix_expr_correctness(const std::vector<Token>&);

#endif // !__CALC_PARSER_HPP__
