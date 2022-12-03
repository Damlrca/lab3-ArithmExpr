# lab3-ArithmExpr

## AEcalc

**Commands**:
- `calc Expr-list`
- `debug` - turns on or off debug mode
- `exit`

## Arithmetic Expression syntax:

### Expression

**Expr-list**:
- `Expr`
- `Expr End`
- `Expr End Expr-list`

**Expr**:
- `Name`
- `Number`
- `Operation<unary> Expr`
- `Expr Operation<binary> Expr`
- `( Expr )`
- `Name = Expr`

### Token types

**Operators** (sorted by priority):
- \<unary\>: `+ -`
- \<binary\>: `* / + -`
- \<special\>: `( ) =`

**Number**:
- real number

**Name**:
- a string of Latin letters and the symbol `_` and numbers. First character is a Latin letter or the symbol `_`

**End**:
- `; \n`

## parser library functions

- lex: `string (infix, Expr-list) -> vector<Token> (infix, Expr-list)`
- parse: `vector<Token> (infix, Expr) -> vector<Token> (postfix, Expr)`
- check_expr_correctness: `vector<Token> (infix, Expr) -> void`
	- throws when expr is incorrect

ArithmExpr.hpp:
- get_ArithmExpr_vector `string (infix, Expr-list) -> vector<ArithmExpr>`

## ArithmExpr class

private:
- constructor `ArithmExpr(vector<Token> (infix, Expr), vector<Token> (postfix, Expr) )`

public:
- constructor `ArithmExpr(vector<Token> (infix, Expr)`
- print_infix
- print_postix
- calculate
