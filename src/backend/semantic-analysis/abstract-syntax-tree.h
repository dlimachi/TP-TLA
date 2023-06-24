#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
//typedef struct Expression Expression;

/**
* Para cada no-terminal se define una nueva estructura que representa su tipo
* de dato y, por lo tanto, su nodo en el AST (Árbol de Sintaxis Abstracta).
*/
/*
typedef struct {
	int value;
} Constant;
*/
/**
* En caso de que un no-terminal ("Factor" en este caso), posea más de una
* regla de producción asociada, se crea además de la estructura un enumerado
* que identitifque cada reducción posible (cada regla de producción). Luego,
* se agrega una instancia de este enumerado dentro del nodo del no-terminal.
*
* De este modo, al recorrer el AST, es posible determinar qué nodos hijos
* posee según el valor de este enumerado.
*/
/*
typedef enum {
	EXPRESSION,
	CONSTANT
} FactorType;

typedef struct {
	FactorType type;
	Expression * expression;
} Factor;

typedef enum {
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	FACTOR
} ExpressionType;

struct Expression {
	ExpressionType type;
	Expression * leftExpression;
	Expression * rightExpression;
};

typedef struct {
	Expression * expression;
} Program;
*/

//A partir de aca voy a poner nuestras cosas
//tipos que se auto-referencian:
typedef struct Request Request;
typedef struct Comparison Comparison;
typedef struct Condition Condition;
typedef struct Factor Factor;
typedef struct Statement Statement;
typedef struct Objects Objects;
typedef struct Pairs Pairs;
typedef struct Statements Statements;
typedef struct EnumTypes EnumTypes;
typedef struct Columns Columns;
typedef struct CheckBody CheckBody;
typedef struct Expression Expression;
typedef struct Term Term;
typedef struct Object Object;
typedef struct Column Column;
typedef struct Options Options;
typedef struct singleType SingleType;
typedef struct Pair Pair;
typedef struct CreateTable CreateTable;
typedef struct InsertBody InsertBody;
typedef struct CreateBody CreateBody;
typedef struct DeleteBody DeleteBody;
typedef struct Check Check;
typedef struct QueryBody QueryBody;
typedef struct General General;
	

//enums a utilizar
typedef enum {
	CGT,
	CLT,
	CEQ,
	CGTEQ,
	CLTEQ,
	CNEQ
} ComparisonType;

typedef enum {
	FTC_NAME,
	INT,
	FSTRING
} FactorType;

typedef enum {
	FACTOR,
	TALL,
	TDIV //para que esta este?
} TermType;

typedef enum {
	TERM,
	EADD,
	ESUB
} ExpressionType;

typedef enum {
	CONDITION,
	CAND,
	COR
} CheckBodyType;

typedef enum {
	RTC_NAME,
	COLUMNS,
	DISTINCT_COLUMNS,
	RALL
} RequestType;

typedef enum {
	DWHERE,
	OBJECT
} DeleteType;

typedef enum {
	MULTIPLE,
	SINGLE
} MultiplesType;


typedef enum {
	SNORMAL,
	SNULLABLE,
	SWITH
} SingleTypeType;

typedef enum {
	OCASCADE,
	OSET_NULL,
	ORESTRICT
} OptionsType;

typedef enum {
	NORMAL,
	STNULLABLE,
	SINGLETYPE,
	NORMALFROM,
	ONDELETEFROM,
	ONUPDATEFROM,
	ASENUMCOLUMNS,
	ASENUMS
} StatementType;

typedef enum {
	PSTRING,
	PINTEGER,
	PDECIMAL,
	PVTRUE,
	PVFALSE,
	PVNULL
} PairType;



typedef enum {
	GINSERT,
	GCREATE,
	GDELETE,
	GCHECK,
	GQUERY
} GeneralType;

//no terminales con diferentes reglas de prod
struct Comparison {
	ComparisonType type;
};

struct Factor {
	FactorType type;
	char * data;
};

struct Term {
	TermType type;
	Term * term;
	Factor * factor;
};

struct Expression {
	ExpressionType type;
	Expression * expression;
	Term * term;
};

struct Condition {
	Expression * leftExpression;
	Comparison * comparison;
	Expression * rightExpression;
};

struct CheckBody {
	CheckBodyType type;
	Condition * condition;
	CheckBody * checkBody;
};

struct Check {
	char * tc_name;
	CheckBody * checkBody;
};

struct Request {
	RequestType type;
	char * tc_name;
	Columns * columns;
};

struct QueryBody {
	char * query_name;
	Request * request;
	char * tc_name;
	char * condition; //chequear esto?
};

struct DeleteBody {
	DeleteType type;
	char * tc_name;
	char * column_name;
	char * condition_string;
	Object * object;
};

struct Column {
	int is_unique;
	char * tc_name;
};

struct Columns {
	MultiplesType type;
	Columns * columns;
	Column * column;
};

struct EnumTypes {
	MultiplesType type;
	EnumTypes * enumTypes;
	char * string;
};

struct singleType {
	SingleTypeType type;
	char * tc_name;
	char * with_tc_name;
};

struct Options {
	OptionsType type;
};

struct Statement {
	StatementType type;
	Columns * columns;
	char * as_name;
	char * column_name;
	SingleType * singleType;
	char * tc_name_from;
	char * column_name_from;
	Options * options;
	EnumTypes * enumTypes;
};

struct Statements {
	MultiplesType * type;
	Statements * statements;
	Statement * statement;
};

struct CreateTable {
	int using_key;
	char * tc_name;
	char * key_name;
};

struct CreateBody {
	CreateTable * createTable;
	Statements * statements;
};

struct Pair {
	PairType type;
	char * column_name;
	char * column_value_string;
};

struct Pairs {
	MultiplesType type;
	Pairs * pairs;
	Pair * pair;
};

struct Object {
	Pairs * pairs;
};

struct Objects {
	MultiplesType type;
	Objects * objects;
	Object * object;
};

struct InsertBody {
	char * tc_name;
	Objects * objects;
};

struct General {
	GeneralType type;
	InsertBody * insertBody;
	CreateBody * createBody;
	DeleteBody * deleteBody;
	Check * check;
	QueryBody * queryBody;
};

typedef struct {
	General * general;
} Program;


#endif
