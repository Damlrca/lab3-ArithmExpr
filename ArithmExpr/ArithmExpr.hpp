#ifndef __CALC_ARITHM_EXPR_HPP__
#define __CALC_ARITHM_EXPR_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "parser.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

class ArithmExpr {
private:
	std::vector<Token> infix;
	std::vector<Token> postfix;
	ArithmExpr(const std::vector<Token>& _infix, const std::vector<Token>& _postfix) : infix{ _infix }, postfix{ _postfix } {}
	ArithmExpr(std::vector<Token>&& _infix, std::vector<Token>&& _postfix) : infix{ _infix }, postfix{ _postfix } {}
public:
	void print(std::ostream& = std::cout);
	void print_RPN(std::ostream& = std::cout); // Reverse Polish notation
	double calculate();
};

std::vector<ArithmExpr> get_ArithmExpr_vector(std::string);

#endif // !__CALC_ARITHM_EXPR_HPP__
