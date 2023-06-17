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
%token <token> AND
%token <token> EQ
%token <token> GT
%token <token> LT
%token <token> LTEQ
%token <token> NEQ
%token <token> GTEQ
%token <token> OR
%token <token> CHECK
%token <token> IN
%token <token> NULLABLE
%token <token> ON_DELETE
%token <token> ON_UPDATE
%token <token> CASCADE
%token <token> RESTRICT
%token <token> SET_NULL
%token <token> AS_ENUM
%token <token> WITH

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


// El símbolo inicial de la gramatica.
%start program

%%
program: general 																							{ $$ = GeneralGrammarAction($1); }
	;

general: insert_body																						{ $$ = InsertBodyGrammarAction($1); }
	| create_body																							{ $$ = CreateBodyGrammarAction($1); }
	| delete_body																							{ $$ = DeleteBodyGrammarAction($1); }
	| check																									{ $$ = CheckGrammarAction($1); }
	| query_body																							{ $$ = QueryBodyGrammarAction($1); }
	;

insert_body: INSERT_INTO TC_NAME OPEN_CURLY objects CLOSE_CURLY												{ $$ = InsertObjectsGrammarAction($1); }
	;

objects: object																								{ $$ = ObjectGrammarAction($1); }
	|	objects COMMA object																				{ $$ = PairObjectsGrammarAction($1); }
	;

object:	OPEN_CURLY pairs CLOSE_CURLY																		{ $$ = ObjectGrammarAction($2); }
	;

pairs: pair																									{ $$ = PairsGrammarAction($1); }
	|	pairs COMMA pair																					{ $$ = PairsCommaGrammarAction($1, $3); }
	;

pair: STRING COLON STRING																					{ $$ = PairDoubleStringGrammarAction($1, $3); }
	|	STRING COLON INTEGER																				{ $$ = PairStringIntegerGrammarAction($1, $3); }
	|	STRING COLON DECIMAL																				{ $$ = PairStringDecimalGrammarAction($1, $3); }
	|	STRING COLON VTRUE																					{ $$ = PairStringTrueGrammarAction($1, $3); }
	|	STRING COLON VFALSE																					{ $$ = PairStringFalseGrammarAction($1, $3); }
	|	STRING COLON VNULL																					{ $$ = PairStringNullGrammarAction($1, $3); }
	;


create_body: CREATE create_table OPEN_CURLY statements CLOSE_CURLY											{ $$ = CreateBodyGrammarAction($2, $4); }
	;

create_table: TC_NAME																						{ $$ = CreateTableNameGrammarAction($1); }
	|	TC_NAME USING_KEY TC_NAME																			{ $$ = CreateTableUsingNameGrammarAction($2); }
	;

statements: statements COMMA statement																		{ $$ = StatementsGrammarAction($1, $2); }
	|	statement												
	;
	
statement: OPEN_PARENTHESIS columns CLOSE_PARENTHESIS AS TC_NAME											{ $$ = StatementGrammarAction($1, $4); }
	|	OPEN_PARENTHESIS columns CLOSE_PARENTHESIS AS TC_NAME NULLABLE										{ $$ = CreateStatementNullableGrammarAction($1, $3); }
	| 	TC_NAME AS single_type																				{ $$ = CreateStatementGrammarAction($1, $3); }
	| 	TC_NAME AS single_type FROM TC_NAME OPEN_PARENTHESIS TC_NAME CLOSE_PARENTHESIS						{ $$ = CreateStatementGrammarAction($1, $2); }
	| 	TC_NAME AS single_type FROM TC_NAME OPEN_PARENTHESIS TC_NAME CLOSE_PARENTHESIS ON_DELETE options	
	| 	TC_NAME AS single_type FROM TC_NAME OPEN_PARENTHESIS TC_NAME CLOSE_PARENTHESIS ON_UPDATE options
	|	OPEN_PARENTHESIS columns CLOSE_PARENTHESIS AS_ENUM OPEN_PARENTHESIS enum_types CLOSE_PARENTHESIS
	|	TC_NAME AS_ENUM OPEN_PARENTHESIS enum_types CLOSE_PARENTHESIS										{ $$ = CreateAsEnumStatementGrammarAction($1, $4); }
	;

options: CASCADE
	|	SET_NULL
	|	RESTRICT

single_type: TC_NAME
	|	TC_NAME NULLABLE
	|	TC_NAME WITH TC_NAME
	;


enum_types: enum_types COMMA STRING
	|	STRING
	;


columns: columns COMMA column
	| column
	;

column: TC_NAME
	| UNIQUE TC_NAME
	;



delete_body: DELETE FROM TC_NAME WHERE TC_NAME EQUAL STRING
	| DELETE FROM TC_NAME object
	;


query_body: QUERY TC_NAME OPEN_PARENTHESIS request COMMA TC_NAME COMMA TC_NAME CLOSE_PARENTHESIS
	;

request: TC_NAME
	|	OPEN_BRACKETS columns CLOSE_BRACKETS
	|	DISTINCT OPEN_BRACKETS columns CLOSE_BRACKETS
	|	ALL
	;


check:
    CHECK TC_NAME OPEN_CURLY check_body CLOSE_CURLY				{ $$ = CheckGrammarAction($1, $2, $3); }
    ;

check_body:
    condition													{ $$ = CheckConditionGrammarAction($1, $2); }
    | check_body AND condition									{ $$ = CheckAndGrammarAction($1, $2); }
    | check_body OR condition									{ $$ = CheckOrGrammarAction($1, $2); }
    ;

condition:
    expression comparison expression							{ $$ = ConditionGrammarAction($1, $2); }
    ;

expression:
    term
    | expression ADD term
    | expression SUB term
    ;

term:
    factor
    | term ALL factor
    | term DIV factor
    ;

factor:
    TC_NAME												
    | INTEGER
    | STRING
    ;

comparison: GT | LT | EQ | GTEQ | LTEQ | NEQ;					{ $$ = ComparitionConstantGrammarAction($1); }

%%

