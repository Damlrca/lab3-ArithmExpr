#ifndef __CALC_ARITHM_EXPR_HPP__
#define __CALC_ARITHM_EXPR_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "parser.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

extern std::map<std::string, double> table;

class ArithmExpr_error : public parser_lib_exception {
public:
	ArithmExpr_error(std::string _s) : parser_lib_exception{ _s } {}
};

class ArithmExpr {
private:
	std::vector<Token> infix;
	std::vector<Token> postfix;
	void print(std::ostream&, const std::vector<Token>&) const;
public:
	ArithmExpr(const std::vector<Token>& _infix, const std::vector<Token>& _postfix) : infix{ _infix }, postfix{ _postfix } {}
	ArithmExpr(std::vector<Token>&& _infix, std::vector<Token>&& _postfix) : infix{ _infix }, postfix{ _postfix } {}
	void print_infix(std::ostream& = std::cout) const;
	void print_postfix(std::ostream& = std::cout) const;
	double calculate();
};

std::vector<ArithmExpr> get_ArithmExpr_vector(const std::string&, bool = false);

#endif // !__CALC_ARITHM_EXPR_HPP__
