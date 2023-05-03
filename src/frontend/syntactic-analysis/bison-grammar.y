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
<<<<<<< HEAD
	int TC_NAME;
=======
	int TABLE_NAME;
>>>>>>> c826025f0a154d58a2c1694a370e0f812a49956c
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
<<<<<<< HEAD
%token <token> TC_NAME
%token <token> DOT
%token <token> CREATE
%token <token> AS
%token <token> KEY
%token <token> USING
%token <token> UNIQUE


%token <token> DELETE
%token <token> FROM
%token <token> WHERE
%token <token> EQUAL
=======
%token <token> TABLE_NAME
%token <token> DOT
%token <token> CREATE
%token <token> TYPE
%token <token> AS
%token <token> KEY
%token <token> USING
>>>>>>> c826025f0a154d58a2c1694a370e0f812a49956c

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

<<<<<<< HEAD
=======
%token <token> LCURLY
%token <token> RCURLY
%token <token> LBRAC
%token <token> RBRAC
%token <token> COMMA 
%token <token> COLON
%token <token> VTRUE 
%token <token> VFALSE
%token <token> VNULL

>>>>>>> c826025f0a154d58a2c1694a370e0f812a49956c
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
<<<<<<< HEAD
	| delete_body
=======
>>>>>>> c826025f0a154d58a2c1694a370e0f812a49956c
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

<<<<<<< HEAD
create_table: TC_NAME
	|	TC_NAME USING KEY TC_NAME
=======
create_table: TABLE_NAME
	|	TABLE_NAME USING KEY column
>>>>>>> c826025f0a154d58a2c1694a370e0f812a49956c
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


%%

