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
	Request * request;
	Comparison * comparison;
	Condition * condition;
	Factor *factor;
	Statement *statement;
	Objects *objects;
	Pairs *pairs;
	Statements *statements;
	EnumTypes *enumTypes;
	Columns *columns;
	CheckBody *checkBody;
	Expression *expression;
	Term *term;
	Object *object;
	Column *column;
	Options *options;
	SingleType *singleType;
	Pair *pair;
	CreateTable *createTable;
	InsertBody *insertBody;
	CreateBody *createBody;
	DeleteBody *deleteBody;
	Check *check;
	QueryBody *queryBody;
	General *general;
	General *program;

	

	// Terminales.
	token token;
	char* integer;


	char *string;
    char* decimal;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> ADD
%token <token> SUB
%token <token> MUL
%token <token> DIV
%token <token> INSERT_INTO
%token <string> TC_NAME
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
%type <request> request
%type <comparison> comparison
%type <condition> condition
%type <factor> factor
%type <statement> statement
%type <objects> objects
%type <pairs> pairs
%type <statements> statements
%type <enumTypes> enum_types
%type <columns> columns
%type <checkBody> check_body
%type <expression> expression
%type <term> term
%type <object> object
%type <column> column
%type <options> options
%type <singleType> single_type
%type <pair> pair
%type <createTable> create_table
%type <insertBody> insert_body
%type <createBody> create_body
%type <deleteBody> delete_body
%type <check> check
%type <queryBody> query_body
%type <general> general


// El símbolo inicial de la gramatica.
%start program

%%
program: general 													{ $$ = GeneralGrammarAction($1); }
	;

general: insert_body													{ $$ = GeneralInsertBodyGrammarAction($1); }
	| create_body													{ $$ = GeneralCreateBodyGrammarAction($1); }
	| delete_body													{ $$ = GeneralDeleteBodyGrammarAction($1); }
	| check														{ $$ = GeneralCheckGrammarAction($1); }
	| query_body													{ $$ = GeneralQueryBodyGrammarAction($1); }
	;

insert_body: INSERT_INTO TC_NAME OPEN_CURLY objects CLOSE_CURLY								{ $$ = InsertObjectsGrammarAction($2, $4); }
	;

objects: object														{ $$ = ObjectsGrammarAction($1); }
	|	objects COMMA object											{ $$ = ObjectsMultipleGrammarAction($1, $3); }
	;

object:	OPEN_CURLY pairs CLOSE_CURLY											{ $$ = ObjectGrammarAction($2); }
	;

pairs: pair														{ $$ = PairsGrammarAction($1); }
	|	pairs COMMA pair											{ $$ = PairsCommaGrammarAction($1, $3); }
	;

pair: STRING COLON STRING												{ $$ = PairStringStringGrammarAction($1, $3); }
	|	STRING COLON INTEGER											{ $$ = PairStringIntegerGrammarAction($1, $3); }
	|	STRING COLON DECIMAL											{ $$ = PairStringDecimalGrammarAction($1, $3); }
	|	STRING COLON VTRUE											{ $$ = PairStringTrueGrammarAction($1); }
	|	STRING COLON VFALSE											{ $$ = PairStringFalseGrammarAction($1); }
	|	STRING COLON VNULL											{ $$ = PairStringNullGrammarAction($1); }
	;


create_body: CREATE create_table OPEN_CURLY statements CLOSE_CURLY							{ $$ = CreateBodyGrammarAction($2, $4); }
	;

create_table: TC_NAME													{ $$ = CreateTableNameGrammarAction($1); }
	|	TC_NAME USING_KEY TC_NAME										{ $$ = CreateTableUsingNameGrammarAction($1, $3); }
	;

statements: statements COMMA statement											{ $$ = StatementsMultipleGrammarAction($1, $3); }
	|	statement												{ $$ = StatementsSimpleGrammarAction($1); }
	;
	
statement: OPEN_PARENTHESIS columns CLOSE_PARENTHESIS AS TC_NAME							{ $$ = StatementColumnsGrammarAction($2, $5); }
	|	OPEN_PARENTHESIS columns CLOSE_PARENTHESIS AS TC_NAME NULLABLE						{ $$ = StatementColumnsNullableGrammarAction($2, $5); }
	| 	TC_NAME AS single_type											{ $$ = StatementSimpleGrammarAction($1, $3); }
	| 	TC_NAME AS single_type FROM TC_NAME OPEN_PARENTHESIS TC_NAME CLOSE_PARENTHESIS				{ $$ = StatementFromGrammarAction($1, $3, $5, $7); }
	| 	TC_NAME AS single_type FROM TC_NAME OPEN_PARENTHESIS TC_NAME CLOSE_PARENTHESIS ON_DELETE options	{ $$ = StatementOnDeleteGrammarAction($1, $3, $5, $7, $10); }
	| 	TC_NAME AS single_type FROM TC_NAME OPEN_PARENTHESIS TC_NAME CLOSE_PARENTHESIS ON_UPDATE options	{ $$ = StatementOnUpdateGrammarAction($1, $3, $5, $7, $10); }
	|	OPEN_PARENTHESIS columns CLOSE_PARENTHESIS AS_ENUM OPEN_PARENTHESIS enum_types CLOSE_PARENTHESIS	{ $$ = StatementColumnsAsEnumGrammarAction($2, $4); }
	|	TC_NAME AS_ENUM OPEN_PARENTHESIS enum_types CLOSE_PARENTHESIS						{ $$ = StatementAsEnumGrammarAction($1, $4); }
	;

options: CASCADE													{ $$ = OptionsCascadeGrammarAction(); }
	|	SET_NULL												{ $$ = OptionsSetNullGrammarAction(); }
	|	RESTRICT												{ $$ = OptionsRestrictGrammarAction(); }

single_type: TC_NAME													{ $$ = SingleTypeGrammarAction($1); }
	|	TC_NAME NULLABLE											{ $$ = SingleTypeNullableGrammarAction($1); }
	|	TC_NAME WITH TC_NAME											{ $$ = SingleTypeWithGrammarAction($1,$3); }
	;


enum_types: enum_types COMMA STRING											{ $$ = EnumTypesMultipleGrammarAction($1, $3); }
	|	STRING													{ $$ = EnumTypesSingleGrammarAction($1); }
	;


columns: columns COMMA column												{ $$ = ColumnsMultipleGrammarAction($1,$3); }
	| column													{ $$ = ColumnsSingleGrammarAction($1); }
	;

column: TC_NAME														{ $$ = ColumnGrammarAction($1); }
	| UNIQUE TC_NAME												{ $$ = ColumnUniqueGrammarAction($2); }
	;



delete_body: DELETE FROM TC_NAME WHERE TC_NAME EQ STRING								{ $$ = DeleteFromWhereGrammarAction($3,$5,$7); }
	| DELETE FROM TC_NAME object											{ $$ = DeleteFromGrammarAction($3,$4); }
	;


query_body: QUERY TC_NAME OPEN_PARENTHESIS request COMMA TC_NAME COMMA TC_NAME CLOSE_PARENTHESIS			{ $$ = QueryBodyGrammarAction($2,$4,$6,$8); }
	;

request: TC_NAME													{ $$ = RequestTc_nameGrammarAction($1); }
	|	OPEN_BRACKETS columns CLOSE_BRACKETS									{ $$ = RequestColumnsGrammarAction($2); }
	|	DISTINCT OPEN_BRACKETS columns CLOSE_BRACKETS								{ $$ = RequestDistinctColumnsGrammarAction($3); }
	|	ALL													{ $$ = RequestAllGrammarAction(); }
	;


check:
    CHECK TC_NAME OPEN_CURLY check_body CLOSE_CURLY									{ $$ = CheckGrammarAction($2, $4); }
    ;

check_body:
    condition														{ $$ = CheckConditionGrammarAction($1); }
    | check_body AND condition												{ $$ = CheckAndGrammarAction($1, $3); }
    | check_body OR condition												{ $$ = CheckOrGrammarAction($1, $3); }
    ;

condition:
    expression comparison expression											{ $$ = ConditionGrammarAction($1, $2, $3); }
    ;

expression:
    term														{ $$ = ExpressionTermGrammarAction($1); }
    | expression ADD term												{ $$ = ExpressionAddGrammarAction($1,$3); }
    | expression SUB term												{ $$ = ExpressionSubGrammarAction($1,$3); }
    ;

term:
    factor														{ $$ = TermFactorGrammarAction($1); }
    | term ALL factor													{ $$ = TermAllGrammarAction($1,$3); }
    | term DIV factor													{ $$ = TermDivGrammarAction($1,$3); }
    ;

factor:
    TC_NAME														{ $$ = Tc_nameFactorGrammarAction($1); }
    | INTEGER														{ $$ = IntegerFactorGrammarAction($1); }
    | STRING														{ $$ = StringFactorGrammarAction($1); }
    ;

comparison: GT 
	| LT 														{ $$ = LesserConstantGrammarAction(); }
	| EQ 														{ $$ = EqualConstantGrammarAction(); }
	| GTEQ 														{ $$ = GreaterOrEqualConstantGrammarAction(); }
	| LTEQ 														{ $$ = LesserOrEqualConstantGrammarAction(); }
	| NEQ														{ $$ = NotEqualConstantGrammarAction(); }
	;
%%

