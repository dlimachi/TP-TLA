%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int expression;
	int factor;
	int constant;
	int INSERT_INTO;

	// Terminales.
	token token;
	int integer;


	char *string;
    double decimal;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> ADD
%token <token> SUB
%token <token> MUL
%token <token> DIV
%token <token> INSERT_INTO
%token <token> CREATE
%token LCURLY RCURLY LBRAC RBRAC COMMA COLON
%token VTRUE VFALSE VNULL
%token <string> STRING;
%token <decimal> DECIMAL;

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

%token <token> OPEN_LLAVE
%token <token> CLOSE_LLAVE

%token <integer> INTEGER
%token <char> CHARS

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <factor> factor
%type <constant> constant

// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program

%%

insert_body: chars
	| value
	| OPEN_LLAVE
	| array
	| CLOSE_LLAVE
	;	

program: expression													{ $$ = ProgramGrammarAction($1); }
	;


// INSERT INTO "XXX" {
//	("name":"Bob", "email":"bob32@gmail.com"), 
// }

create clientes_banco{
    (codigo, unique dni) as integer,
	id as string
}

create_body: CREATE STRING LCURLY statements RCURLY

statements: statements COMMA statement
	| statement
	
statement: ( columns ) AS type
	| 	STRING as type

columns: columns COMMA column
	|	column



insert_body: INSERT_INTO STRING LCURLY objects RCURLY

objects: objects COMMA object
	|	object

object:	LCURLY pairs RCURLY

pairs: pairs COMMA pair
	|	pair

pair: STRING COLON STRING


expression: expression[left] ADD expression[right]					{ $$ = AdditionExpressionGrammarAction($left, $right); }
	| expression[left] SUB expression[right]						{ $$ = SubtractionExpressionGrammarAction($left, $right); }
	| expression[left] MUL expression[right]						{ $$ = MultiplicationExpressionGrammarAction($left, $right); }
	| expression[left] DIV expression[right]						{ $$ = DivisionExpressionGrammarAction($left, $right); }
	| factor														{ $$ = FactorExpressionGrammarAction($1); }
	| INSERT_INTO
	| json
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorGrammarAction($2); }
	| constant														{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantGrammarAction($1); }
	;

json:
    | value
    ;

value: object
     | STRING
     | DECIMAL
     | array
     | VTRUE
     | VFALSE
     | VNULL
     ;

object: LCURLY RCURLY
      | LCURLY members RCURLY
      ;

members: member
       | members COMMA member
       ;

member: STRING COLON value
      ;

array: LBRAC RBRAC
     | LBRAC values RBRAC
     ;

values: value
      | values COMMA value
      ;

%%
