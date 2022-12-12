# lab3-ArithmExpr

## AEcalc

**Commands**:
- `calc Expr-list`
- `debug` - turns on or off debugging mode
- `print` - turns on or off print mode
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
- unary: `+ -`
- binary: `* / + -`
- special: `( ) =`

**Number**:
- real number

**Name**:
- a string of Latin letters and the symbol `_` and numbers. First character is a Latin letter or the symbol `_`

**End**:
- `; \n`

## parser library functions

- lex: `string (infix, Expr-list) -> vector<Token> (infix, Expr-list)`

- check_infix_expr_correctness: `vector<Token> (infix, Expr)`
	- throws when infix expr is incorrect

- parse: `vector<Token> (infix, Expr) -> vector<Token> (postfix, Expr)`
	- `vector<Token> (infix, Expr)` should be correct, check it using `check_infix_expr_correctness`
	
- check_postfix_expr_correctness: `vector<Token> (postfix, Expr)`
	- throws when postfix expr is incorrect

ArithmExpr.hpp:
- get_ArithmExpr_vector `string (infix, Expr-list) -> vector<ArithmExpr>`

## ArithmExpr class

- constructor `ArithmExpr(vector<Token> (infix, Expr), vector<Token> (postfix, Expr))`
	- `vector<Token> (infix, Expr)` and `vector<Token> (postfix, Expr)` should be correct,
	check it using `check_infix_expr_correctness` and `check_postfix_expr_correctness`
- print_infix
- print_postix
- calculate
