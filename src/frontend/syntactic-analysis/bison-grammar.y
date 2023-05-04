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
	int TC_NAME;
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
%token <token> TC_NAME
%token <token> DOT
%token <token> CREATE
%token <token> AS
%token <token> USING_KEY
%token <token> UNIQUE
%token <token> QUERY
%token <token> ALL
%token <token> DISTINCT 
%token <token> DELETE
%token <token> FROM
%token <token> WHERE
%token <token> EQUAL

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

%token <token> OPEN_CURLY
%token <token> CLOSE_CURLY
%token <token> OPEN_BRACKETS
%token <token> CLOSE_BRACKETS
%token <token> COMMA
%token <token> SEMICOLON
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
	| delete_body
	| check
	;

insert_body: INSERT_INTO TC_NAME OPEN_CURLY objects CLOSE_CURLY
	;

objects: object
	|	objects COMMA object
	;

object:	OPEN_CURLY pairs CLOSE_CURLY
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


create_body: CREATE create_table OPEN_CURLY statements CLOSE_CURLY
	;

create_table: TC_NAME
	|	TC_NAME USING_KEY TC_NAME
	;

statements: statements COMMA statement
	|	statement	
	;
	
statement: OPEN_PARENTHESIS columns CLOSE_PARENTHESIS AS STRING
	| 	TC_NAME AS STRING
	;

columns: columns COMMA TC_NAME
	|	TC_NAME
	;



delete_body: DELETE FROM TC_NAME WHERE TC_NAME EQUAL STRING 
	;


query_body: TC_NAME OPEN_PARENTHESIS request COMMA TC_NAME COMMA check CLOSE_PARENTHESIS
	;

request: TC_NAME
	|	OPEN_BRACKETS columns CLOSE_BRACKETS
	|	DISTINCT OPEN_BRACKETS columns CLOSE_BRACKETS
	|	ALL
	;


check:
    CHECK TC_NAME OPEN_CURLY check_body CLOSE_CURLY
    ;

check_body:
    condition
    | check_body AND condition
    | check_body OR condition
    ;

condition:
    TC_NAME comparison INTEGER
    | TC_NAME comparison STRING
	| TC_NAME comparison TC_NAME
    ;

comparison: GT | LT | EQ ;


%%

