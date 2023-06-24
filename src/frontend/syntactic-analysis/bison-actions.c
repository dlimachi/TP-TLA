#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
int GeneralGrammarAction(General * value) {
	LogDebug("\tGeneralGrammarAction(%d)", value);
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	state.succeed = true;
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/

	Program * program = malloc(sizeof(Program));
	program->general = value;

	state.program = program;
	return value;
}

int return0() {
	LogDebug("bien");
	state.succeed = true;
	return 0;
}

General * GeneralInsertBodyGrammarAction(InsertBody * InsertBody){
	LogDebug("\tGeneralInsertBodyGrammarAction");
	General * general = calloc(1,sizeof(General));
	general->type = INSERT;
	general->InsertBody = InsertBody;
	general->createBody = NULL;
	general->deleteBody = NULL;
	general->check = NULL;
	general->queryBody = NULL;
	return general;
};

General * GeneralCreateBodyGrammarAction(CreateBody * createBody){
	LogDebug("\tGeneralInsertBodyGrammarAction");
	General * general = calloc(1,sizeof(General));
	general->type = CREATE;
	general->InsertBody = NULL;
	general->createBody = createBody;
	general->deleteBody = NULL;
	general->check = NULL;
	general->queryBody = NULL;
	return general;
};

General * GeneralDeleteBodyGrammarAction(DeleteBody * deleteBody){
	LogDebug("\tGeneralInsertBodyGrammarAction");
	General * general = calloc(1,sizeof(General));
	general->type = CREATE;
	general->InsertBody = NULL;
	general->createBody = NULL;
	general->deleteBody = deleteBody;
	general->check = NULL;
	general->queryBody = NULL;
	return general;
};

General * GeneralCheckGrammarAction(Check * chek){
	LogDebug("\tGeneralInsertBodyGrammarAction");
	General * general = calloc(1,sizeof(General));
	general->type = CHECK;
	general->InsertBody = NULL;
	general->createBody = NULL;
	general->deleteBody = NULL;
	general->check = check;
	general->queryBody = NULL;
	return general;
};

General * GeneralQueryBodyGrammarAction(QueryBody * queryBody){
	LogDebug("\tGeneralInsertBodyGrammarAction");
	General * general = calloc(1,sizeof(General));
	general->type = QUERY;
	general->InsertBody = NULL;
	general->createBody = NULL;
	general->deleteBody = NULL;
	general->check = NULL;
	general->queryBody = queryBody;
	return general;
};

InsertBody * InsertObjectsGrammarAction(char * tcName, Objects* objects){
	LogDebug("\tInsertObjectsGrammarAction");	
	InsertBody * insertBody = calloc(1,sizeof(InsertBody));
	general->tc_name = tcName;
	general->objects = objects;
	return insertBody;
};

Objects * ObjectsGrammarAction(Object * object){
	LogDebug("\tInsertObjectsGrammarAction");	
	Objects * objects = calloc(1,sizeof(Objects));
	objects->type = SIMPLE;
	objects->object = object;
	objects->objects= NULL;
	return Objects;
};

Objects * ObjectsMultipleGrammarAction(Objects * objects, Object * object){
	LogDebug("\tInsertObjectsGrammarAction");	
	Objects * objectstoRet = calloc(1,sizeof(Objects));
	objectstoRet->type = MULTIPLE;
	objectstoRet->object = object;
	objectstoRet->objects= objects;
	return objectstoRet;
};

Object * ObjectGrammarAction(Pairs* pairs){
	LogDebug("\tInsertObjectsGrammarAction");	
	Object * object = calloc(1,sizeof(Object));
	object->pairs= pairs;
	return object;
};

Pairs * PairsGrammarAction(Pair* pair){
	LogDebug("\tInsertObjectsGrammarAction");	
	Pairs * pairs = calloc(1,sizeof(Pairs));
	pairs->type=SINGLE;
	pairs->pair= pair;
	pairs->pairs=NULL;
	return pairs;
};

Pairs * PairsCommaGrammarAction(Pairs* pairsArg,Pair* pair){
	LogDebug("\tInsertObjectsGrammarAction");	
	Pairs * pairs = calloc(1,sizeof(Pairs));
	pairs->type=MULTIPLE;
	pairs->pair= pair;
	pairs->pairs=pairsArg;
	return pairs;
};

Pair * PairStringStringGrammarAction(char* cName,char* cValue){
	LogDebug("\tInsertObjectsGrammarAction");	
	Pair * pair = calloc(1,sizeof(Pair));
	pair->type=STRING;
	pair->column_name= cName;
	pair->column_value_string=cValue;
	pair->column_boolean=NULL;
	return pair;
};

Pair * PairStringIntegerGrammarAction(char* cName,char* cValue){
	LogDebug("\tInsertObjectsGrammarAction");	
	Pair * pair = calloc(1,sizeof(Pair));
	pair->type=INTEGER;
	pair->column_name= cName;
	pair->column_value_string=cValue;
	pair->column_boolean=NULL;
	return pair;
};

Pair * PairStringDecimalGrammarAction(char* cName,char* cValue){
	LogDebug("\tInsertObjectsGrammarAction");	
	Pair * pair = calloc(1,sizeof(Pair));
	pair->type=DECIMAL;
	pair->column_name= cName;
	pair->column_value_string=cValue;
	pair->column_boolean=NULL;
	return pair;
};

Pair * PairStringTrueGrammarAction(char* cName){
	LogDebug("\tInsertObjectsGrammarAction");	
	Pair * pair = calloc(1,sizeof(Pair));
	pair->type=VTRUE;
	pair->column_name= cName;
	pair->column_value_string=NULL;
	return pair;
};

Pair * PairStringFalseGrammarAction(char* cName){
	LogDebug("\tInsertObjectsGrammarAction");	
	Pair * pair = calloc(1,sizeof(Pair));
	pair->type=VFALSE;
	pair->column_name= cName;
	pair->column_value_string=NULL;
	return pair;
};

Pair * PairStringNullGrammarAction(char* cName){
	LogDebug("\tInsertObjectsGrammarAction");	
	Pair * pair = calloc(1,sizeof(Pair));
	pair->type=VNULL;
	pair->column_name= cName;
	return pair;
};

CreateBody * CreateBodyGrammarAction(CreateTable * createTable, Statements * statements){
	LogDebug("\tInsertObjectsGrammarAction");	
	CreateBody * createBody = calloc(1,sizeof(CreateBody));
	createBody->createTable=createTable;
	createBody->statements= statements;
	return createBody;
};

CreateTable * CreateTableNameGrammarAction(char * tcName){
	LogDebug("\tInsertObjectsGrammarAction");	
	CreateTable * createTable = calloc(1,sizeof(CreateTable));
	createTable->using_key=0;
	createTable->tc_name= tcName;
	createTable->key_name= NULL;
	return createTable;
};

CreateTable * CreateTableUsingNameGrammarAction(char * tcName, char * keyName){
	LogDebug("\tInsertObjectsGrammarAction");	
	CreateTable * createTable = calloc(1,sizeof(CreateTable));
	createTable->using_key=1;
	createTable->tc_name= tcName;
	createTable->key_name= keyName;
	return createTable;
};

Statements * StatementsMultipleGrammarAction(Statements * statementsArg, Statement * statement){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statements * statements = calloc(1,sizeof(Statements));
	statements->type=MULTIPLE;
	statements->statements= statementsArg;
	statements->statement= statement;
	return statements;
};

Statements * StatementsSimpleGrammarAction(Statements * statementsArg, Statement * statement){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statements * statements = calloc(1,sizeof(Statements));
	statements->type=SIMPLE;
	statements->statements= NULL;
	statements->statement= statement;
	return statements;
};

Statement * StatementColumnsGrammarAction(Columns * columns, char * asName){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statement * statement = calloc(1,sizeof(Statement));
	statement->type=NORMAL;
	statement->columns= columns;
	statement->as_name= asName;
	statement->column_name=NULL;
	statement->singleType=NULL;
	statement->tc_name_from=NULL;
	statement->column_name_from=NULL;
	statement->options=NULL;
	statement->enumTypes=NULL;
	return statement;
};

Statement * StatementColumnsNullableGrammarAction(Columns * columns, char * asName){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statement * statement = calloc(1,sizeof(Statement));
	statement->type=NULLABLE;
	statement->columns= columns;
	statement->as_name= asName;
	statement->column_name=NULL;
	statement->singleType=NULL;
	statement->tc_name_from=NULL;
	statement->column_name_from=NULL;
	statement->options=NULL;
	statement->enumTypes=NULL;
	return statement;
};

Statement * StatementSimpleGrammarAction(char * columnName, SingleType * singleType){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statement * statement = calloc(1,sizeof(Statement));
	statement->type=SINGLETYPE;
	statement->columns= NULL;
	statement->as_name= NULL;
	statement->column_name=columnName;
	statement->singleType=singleType;
	statement->tc_name_from=NULL;
	statement->column_name_from=NULL;
	statement->options=NULL;
	statement->enumTypes=NULL;
	return statement;
};

Statement * StatementFromGrammarAction(char * columnName, SingleType * singleType, char * tcNameFrom, char * columnNameFrom){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statement * statement = calloc(1,sizeof(Statement));
	statement->type=NORMALFROM;
	statement->columns= NULL;
	statement->as_name= NULL;
	statement->column_name=columnName;
	statement->singleType=singleType;
	statement->tc_name_from=tcNameFrom;
	statement->column_name_from=columnNameFrom;
	statement->options=NULL;
	statement->enumTypes=NULL;
	return statement;
};

Statement * StatementOnDeleteGrammarAction(char * columnName, SingleType * singleType, char * tcNameFrom, char * columnNameFrom, Options * options){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statement * statement = calloc(1,sizeof(Statement));
	statement->type=ONDELETEFROM;
	statement->columns= NULL;
	statement->as_name= NULL;
	statement->column_name=columnName;
	statement->singleType=singleType;
	statement->tc_name_from=tcNameFrom;
	statement->column_name_from=columnNameFrom;
	statement->options=options;
	statement->enumTypes=NULL;
	return statement;
};

Statement * StatementOnUpdateGrammarAction(char * columnName, SingleType * singleType, char * tcNameFrom, char * columnNameFrom, Options * options){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statement * statement = calloc(1,sizeof(Statement));
	statement->type=ONUPDATEFROM;
	statement->columns= NULL;
	statement->as_name= NULL;
	statement->column_name=columnName;
	statement->singleType=singleType;
	statement->tc_name_from=tcNameFrom;
	statement->column_name_from=columnNameFrom;
	statement->options=options;
	statement->enumTypes=NULL;
	return statement;
};

Statement * StatementColumnsAsEnumGrammarAction(Columns * columns, EnumTypes * enumTypes){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statement * statement = calloc(1,sizeof(Statement));
	statement->type=ASENUMCOLUMNS;
	statement->columns= columns;
	statement->as_name= NULL;
	statement->column_name=NULL;
	statement->singleType=NULL;
	statement->tc_name_from=NULL;
	statement->column_name_from=NULL;
	statement->options=NULL;
	statement->enumTypes=enumTypes;
	return statement;
};

Statement * StatementAsEnumGrammarAction(char * columnName, EnumTypes * enumTypes){
	LogDebug("\tInsertObjectsGrammarAction");	
	Statement * statement = calloc(1,sizeof(Statement));
	statement->type=ASENUMS;
	statement->columns= NULL;
	statement->as_name= NULL;
	statement->column_name=columnName;
	statement->singleType=NULL;
	statement->tc_name_from=NULL;
	statement->column_name_from=NULL;
	statement->options=NULL;
	statement->enumTypes=enumTypes;
	return statement;
};

Options * OptionsCascadeGrammarAction(){
	LogDebug("\tInsertObjectsGrammarAction");	
	Options * options = calloc(1,sizeof(Options));
	options->type=CASCADE;
	return options;
};

Options * OptionsSetNullGrammarAction(){
	LogDebug("\tInsertObjectsGrammarAction");	
	Options * options = calloc(1,sizeof(Options));
	options->type=SET_NULL;
	return options;
};

Options * OptionsRestrictGrammarAction(){
	LogDebug("\tInsertObjectsGrammarAction");	
	Options * options = calloc(1,sizeof(Options));
	options->type=RESTRICT;
	return options;
};

SingleType * SingleTypeGrammarAction(char * tcName){
	LogDebug("\tInsertObjectsGrammarAction");	
	SingleType * singleType = calloc(1,sizeof(SingleType));
	singleType->type=NORMAL;
	singleType->tc_name=tcName;
	singleType->with_tc_name=NULL;
	return singleType;
};

SingleType * SingleTypeNullableGrammarAction(char * tcName){
	LogDebug("\tInsertObjectsGrammarAction");	
	SingleType * singleType = calloc(1,sizeof(SingleType));
	singleType->type=NULLABLE;
	singleType->tc_name=tcName;
	singleType->with_tc_name=NULL;
	return singleType;
};

SingleType * SingleTypeWithGrammarAction(char * tcName, char * withTcName){
	LogDebug("\tInsertObjectsGrammarAction");	
	SingleType * singleType = calloc(1,sizeof(SingleType));
	singleType->type=WITH;
	singleType->tc_name=tcName;
	singleType->with_tc_name=withTcName;
	return singleType;
};

EnumTypes * EnumTypesMultipleGrammarAction(EnumTypes * enumTypesArg, char * string){
	LogDebug("\tInsertObjectsGrammarAction");	
	EnumTypes * enumTypes = calloc(1,sizeof(EnumTypes));
	enumTypes->type=MULTIPLE;
	enumTypes->enumTypes=enumTypesArg;
	enumTypes->string=string;
	return enumTypes;
};

EnumTypes * EnumTypesSingleGrammarAction(char * string){
	LogDebug("\tInsertObjectsGrammarAction");	
	EnumTypes * enumTypes = calloc(1,sizeof(EnumTypes));
	enumTypes->type=SINGLE;
	enumTypes->enumTypes=NULL;
	enumTypes->string=string;
	return enumTypes;
};

Columns * ColumnsMultipleGrammarAction(Columns * columns, Column * column){
	LogDebug("\tInsertObjectsGrammarAction");	
	Columns * columns = calloc(1,sizeof(Columns));
	columns->type=MULTIPLE;
	columns->columns=columns;
	columns->column=column;
	return columns;
};

Columns * ColumnsSingleGrammarAction( Column * column){
	LogDebug("\tInsertObjectsGrammarAction");	
	Columns * columns = calloc(1,sizeof(Columns));
	columns->type=SINGLE;
	columns->columns=NULL;
	columns->column=column;
	return columns;
};

Column * ColumnGrammarAction( char * cName){
	LogDebug("\tInsertObjectsGrammarAction");	
	Column * column = calloc(1,sizeof(Column));
	column->is_unique=0;
	column->tc_name=cName;
	return column;
};

Column * ColumnUniqueGrammarAction( char * cName){
	LogDebug("\tInsertObjectsGrammarAction");	
	Column * column = calloc(1,sizeof(Column));
	column->is_unique=1;
	column->tc_name=cName;
	return column;
};

DeleteBody * DeleteFromWhereGrammarAction( char * fromTable, char * conditionColumn, char * conditionString){
	LogDebug("\tInsertObjectsGrammarAction");	
	DeleteBody * deleteBody = calloc(1,sizeof(DeleteBody));
	deleteBody->type=WHERE;
	deleteBody->tc_name=fromTable;
	deleteBody->column_name=conditionColumn;
	deleteBody->conditionString=conditionString;
	deleteBody->object=NULL;
	return deleteBody;
};

DeleteBody * DeleteFromGrammarAction( char * fromTable, Object * object){
	LogDebug("\tInsertObjectsGrammarAction");	
	DeleteBody * deleteBody = calloc(1,sizeof(DeleteBody));
	deleteBody->type=OBJECT;
	deleteBody->tc_name=fromTable;
	deleteBody->column_name=NULL;
	deleteBody->conditionString=NULL;
	deleteBody->object=object;
	return deleteBody;
};

QueryBody * QueryBodyGrammarAction( char * queryName, Request * request, char * tc_name, char * condition){
	LogDebug("\tInsertObjectsGrammarAction");	
	QueryBody * queryBody = calloc(1,sizeof(QueryBody));
	queryBody->query_name=queryName;
	queryBody->request=request;
	queryBody->tc_name=tc_name;
	queryBody->condition=condition;
	return queryBody;
};

Request * RequestTc_nameGrammarAction( char * tcName){
	LogDebug("\tInsertObjectsGrammarAction");	
	Request * request = calloc(1,sizeof(Request));
	request->type=TC_NAME;
	request->tc_name=tcName;
	request->columns=NULL;
	return request;
};

Request * RequestColumnsGrammarAction( Columns * columns){
	LogDebug("\tInsertObjectsGrammarAction");	
	Request * request = calloc(1,sizeof(Request));
	request->type=COLUMNS;
	request->tc_name=NULL;
	request->columns=columns;
	return request;
};

Request * RequestDistinctColumnsGrammarAction( Columns * columns){
	LogDebug("\tInsertObjectsGrammarAction");	
	Request * request = calloc(1,sizeof(Request));
	request->type=DISTINCT_COLUMNS;
	request->tc_name=NULL;
	request->columns=columns;
	return request;
};
////////////////////////////////////////////////////////////////////////////////////
Request * RequestAllGrammarAction() {
    LogDebug("\tRequestAllGrammarAction");
    Request * request = calloc(1, sizeof(Request));
    request->type = ALL;
    request->tc_name = NULL;
    request->columns = NULL;
    return request;
}

Check * CheckGrammarAction(char *tc_name, CheckBody * checkBody) {
    LogDebug("\tCheckGrammarAction");
    CheckBody * check = calloc(1, sizeof(Check));
    check->tc_name = tc_name;
    cond->checkBody = checkBody;
    return check;
}

CheckBody * CheckConditionGrammarAction(Condition * condition) {
    LogDebug("\tCheckAndGrammarAction");
    CheckBody * check = calloc(1, sizeof(CheckBody));
    check->type = CONDITION;
    check->condition = condition;
    cond->checkBody = NULL;
    return check;
}

CheckBody * CheckAndGrammarAction(CheckBody * checkBody, Condition * condition) {
    LogDebug("\tCheckAndGrammarAction");
    CheckBody * check = calloc(1, sizeof(CheckBody));
    check->type = AND;
    check->condition = condition;
    cond->checkBody = checkBody;
    return check;
}

CheckBody * CheckOrGrammarAction(CheckBody * checkBody, Condition * condition) {
    LogDebug("\tCheckOrGrammarAction");
    CheckBody * check = calloc(1, sizeof(CheckBody));
    check->type = OR;
    check->condition = condition;
    cond->checkBody = checkBody;
    return check;
}

Condition * ConditionGrammarAction(Expression * expL, Comparison * comparison, Expression * expR) {
    LogDebug("\tConditionGrammarAction");
    Condition * cond= calloc(1, sizeof(Condition));
    cond->leftExpression = expL;
    cond->comparison = comparison;
    cond->rightExpression = expR;
    return comp;
}

Expression * ExpressionTermGrammarAction(Term * term) {
    LogDebug("\tExpressionTermGrammarAction");
    Expression * exp = calloc(1, sizeof(Expression));
    exp->type = TERM;
    exp->expression = NULL;
    exp->term = term;
    return exp;
}

Expression * ExpressionAddGrammarAction(Expression * expression, Term * term) {
    LogDebug("\tExpressionAddGrammarAction");
    Expression * exp = calloc(1, sizeof(Expression));
    exp->type = SUB;
    exp->expression = expression;
    exp->term = term;
    return exp;
}

Expression * ExpressionSubGrammarAction(Expression * expression, Term * term){
    LogDebug("\tExpressionSubGrammarAction");
    Expression * exp = calloc(1, sizeof(Expression));
    exp->type = ADD;
    exp->expression = expression;
    exp->term = term;
    return exp;
}

Term * TermFactorGrammarAction(Factor * factor) {
    LogDebug("\tTermFactorGrammarAction");
    Term * termRet = calloc(1,sizeof(Term));
    termRet->type = FACTOR;
    termRet->term = NULL;
    termRet->factor = factor;
    return termRet;
}

Term * TermAllGrammarAction(Term * term , Factor * factor) {
    LogDebug("\tTermAllGrammarAction");
    Term * termRet = calloc(1,sizeof(Term));
    termRet->type = ALL;
    termRet->term = term;
    termRet->factor = factor;
    return termRet;
}

Term * TermDivGrammarAction(Term * term , Factor * factor) {
    LogDebug("\tTermDivGrammarAction");
    Term * termRet = calloc(1,sizeof(Term));
    termRet->type = DIV;
    termRet->term = term;
    termRet->factor = factor;
    return termRet;
}

Factor * Tc_nameFactorGrammarAction(char * data) {
	LogDebug("\tTc_nameFactorGrammarAction (%s)", data);
	Factor * factor = calloc(1,sizeof(Factor));
	factor->type = TC_NAME;
    factor->data = data;
	return factor;
}

Factor * IntegerFactorGrammarAction(char * data) {
	LogDebug("\tIntegerFactorGrammarAction (%s)", data);
	Factor * factor = calloc(1,sizeof(Factor));
	factor->type = INT;
    factor->data = data;
	return factor;
}


Factor * StringFactorGrammarAction(char * data) {
	LogDebug("\tStringFactorGrammarAction (%s)", data);
	Factor * factor = calloc(1,sizeof(Factor));
	factor->type = STRING;
    factor->data = data;
	return factor;
}

Comparison * LesserConstantGrammarAction() {
	LogDebug("\tLesserConstantGrammarAction");
	Comparison * comp = calloc(1,sizeof(Comparison));
	comp->type = LT;
	return comp;
}

Comparison * EqualConstantGrammarAction() {
	LogDebug("\tEqualConstantGrammarAction");
	Comparison * comp = calloc(1,sizeof(Comparison));
	comp->type = EQ;
	return comp;
}

Comparison * GreaterOrEqualConstantGrammarAction() {
	LogDebug("\tEqualConstantGrammarAction");
	Comparison * comp = calloc(1,sizeof(Comparison));
	comp->type = GT;
	return comp;
}

Comparison * LesserOrEqualConstantGrammarAction(){
	Comparison * comp = calloc(1,sizeof(Comparison));
	comp->type = LTEQ;
	return comp;
}

Comparison * NotEqualConstantGrammarAction() {
	LogDebug("\tNotEqualConstantGrammarAction");
	Comparison * comp = calloc(1,sizeof(Comparison));
	comp->type = NEQ;
	return comp;
}