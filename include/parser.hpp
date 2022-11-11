#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "Stack.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class TokenType {
	Operator,
	Value,
	Name
};

string TokenType_name(TokenType x) {
	switch (x)
	{
	case TokenType::Operator:
		return "operator";
		break;
	case TokenType::Value:
		return "value";
		break;
	case TokenType::Name:
		return "name";
		break;
	default:
		return "unknown";
		break;
	}
}

class Token {
	TokenType type;
	string str;
public:
	Token(TokenType t, const string& s) : type{ t }, str{ s } {}
	string get_str() { return str; }
	TokenType get_type() { return type; }
	friend ostream& operator<<(ostream& out, const Token& t) {
		out << "{" << t.str << ", " << TokenType_name(t.type) << "}";
		return out;
	}
};

vector<Token> lex(string input) {
	vector<Token> res;

	return res;
}

template<class T>
class A {
	T a;
	Stack<int> s{ 10 };
public:
	A(int _a) : a(_a) {
		for (int i = 0; i < 10; i++)
			s.push(i);
	}
	T get() { return a; }
	int pop() { return s.pop(); }
};

#endif __PARSER_HPP__
