# lab3-ArithmExpr

## AEcalc

**Commands**:
- `calc Expr-list`
- `exit`


## Arithmetic Expression syntax:

### Expression

**Expr-list**:
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

**Operators**:
- \<binary\>: `+ - * /`
- \<unary\>: `+ -`
- \<special\>: `( ) =`

**Number**:
- constant real number

**Name**:
- a string of Latin letters and the symbol `_` and numbers. First character is a Latin letter or the symbol `_`

**End**:
- `\n`
- `;`
- `EOF`

## parser lib functions

- lex: `string -> vector<Token>`
- parse: `vector<Token> -> vector<Token> (RPN: Reverse Polish notation)`

## ArithmExpr class

private:
- constructor `ArithmExpr(vector<Token>, vector<Token> (RPN) )`

public:
- print
- print_RPN

friend:
- get_ArithmExpr_vector: `string -> vector<ArithmExpr>`
