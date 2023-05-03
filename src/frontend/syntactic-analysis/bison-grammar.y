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
	int INSERT_INTO;
	int TABLE_NAME;
	int CREATE;
	

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
%token <token> TABLE_NAME
%token <token> DOT
%token <token> CREATE
%token <token> TYPE
%token <token> AS
%token <token> KEY
%token <token> USING

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

%token <token> OPEN_LLAVE
%token <token> CLOSE_LLAVE

%token <token> LCURLY
%token <token> RCURLY
%token <token> LBRAC
%token <token> RBRAC
%token <token> COMMA 
%token <token> COLON
%token <token> VTRUE 
%token <token> VFALSE
%token <token> VNULL

%token <string> STRING;
%token <decimal> DECIMAL;

%token <integer> INTEGER;
%token <char> CHARS;

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program


// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program

%%
program: general 	{$$ = return0();}
	;

general: insert_body
	| create_body
	;

insert_body: INSERT_INTO TABLE_NAME LCURLY objects RCURLY
	;

objects: object
	|	objects COMMA object
	;

object:	LCURLY pairs RCURLY
	;

pairs: pair
	|	pairs COMMA pair	
	;

pair: STRING COLON STRING
	|	STRING COLON DECIMAL
	|	STRING COLON VTRUE
	|	STRING COLON VFALSE
	|	STRING COLON VNULL
	;


create_body: CREATE create_table LCURLY statements RCURLY
	;

create_table: TABLE_NAME
	|	TABLE_NAME USING KEY column
	;

statements: statements COMMA statement
	|	statement	
	;
	
statement: OPEN_PARENTHESIS columns CLOSE_PARENTHESIS AS TYPE
	| 	STRING AS TYPE
	;

columns: columns COMMA column
	|	column
	;

column: STRING
	;

%%

