# lab3-ArithmExpr

## AEcalc

**Commands**:
- `calc Expr-list`
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
- constant real number

**Name**:
- a string of Latin letters and the symbol `_` and numbers. First character is a Latin letter or the symbol `_`

**End**:
- `\n`
- `;`

## parser library functions

- lex: `string (infix) -> vector<Token> (infix)`
- parse: `vector<Token> (infix) -> vector<Token> (postfix)`

## ArithmExpr class

private:
- constructor `ArithmExpr(vector<Token> (infix), vector<Token> (postfix) )`

public:
- print
- print_postix
- calculate

friend:
- get_ArithmExpr_vector: `string (infix) -> vector<ArithmExpr>`
