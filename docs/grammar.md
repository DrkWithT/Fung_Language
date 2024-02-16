# Grammar

### Pre-Notes
"?" is the nil-check operator. If the expression gets nil, an error is thrown.

### BNF Rules
```bnf
; basic tokens
whitespace ::= (SP | TAB | CR | LF)+
line-comment ::= "#" (non-newline) LF
keyword ::= (ALPHA)+
identifier ::= (ALPHA | "_")+
nil ::= "$N"
boolean ::= "$T" | "$F"
numeric ::= (DIGIT)+ "." (DIGIT)+
string ::= "\"" (non-double-quotes) "\""
list ::= "[" (literal-expr)* "]"
object ::= identifier "{" (literal-expr)* "}"

; basic expressions
element-expr ::= nil | boolean | numeric | string | list | object | identifier
access-expr ::= element-expr ("[" (string | numeric) "]")*
unary-expr ::= ("-" | "?")* access-expr
term-expr ::= unary ("+" || "-" unary-expr)*
factor-expr ::= term-expr ("*" || "/" term-expr)*
comparison-expr ::= factor-expr ("==" || "!=" || "<=" || ">=" || "<" || ">" factor-expr)*
conditional-expr ::= comparison-expr ("or" | "and" comparison-expr)*
expr ::= conditional-expr

; basic stmts
use-decl ::= "use" identifier
var-decl ::= ("let" | "mut") identifier "=" expr
param-decl ::= ("val" | "ref") identifier
func-decl ::= "fun" identifier "(" (param-decl)* ")" block
field-decl ::= "field" identifier
object-decl ::= "object" identifier (field-decl)* "end"
assign-stmt ::= access-expr "=" expr
return-stmt ::= "ret" expr
if-stmt ::= "if" conditional-expr block (alt-stmt){0,1}
else-stmt ::= "else" block
while-stmt ::= "while" conditional-expr block
each-stmt ::= "each" identifier "in" expr block
func-call ::= identifier (expr)* ("," expr)*
stmt ::= use-decl | var-decl | func-decl | object-decl | func-call
block ::= (stmt)+ "end"
program ::= (stmt)*
```
