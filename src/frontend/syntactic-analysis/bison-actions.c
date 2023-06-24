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

StatementColumnsAsEnumGrammarAction($2, $4) 

StatementAsEnumGrammarAction($1, $4)

OptionsCascadeGrammarAction()

OptionsSetNullGrammarAction()

OptionsRestrictGrammarAction()

SingleTypeGrammarAction($1)

SingleTypeNullableGrammarAction($1)

SingleTypeWithGrammarAction($1,$3)

EnumTypesMultipleGrammarAction($1, $3)

EnumTypesSingleGrammarAction($1)

ColumnsMultipleGrammarAction($1,$3)

ColumnsSingleGrammarAction($1)

ColumnGrammarAction($1)

ColumnUniqueGrammarAction($2)

DeleteFromWhereGrammarAction($3,$5,$7)

DeleteFromGrammarAction($3,$4)

QueryBodyGrammarAction($4)

RequestColumnsGrammarAction($2)

RequestDistinctColumnsGrammarAction($3)
////////////////////////////////////////////////////////////////////////////////////
Request * RequestAllGrammarAction() {
    LogDebug("\tRequestAllGrammarAction");
    Request * request = calloc(1, sizeof(Request));
    request->type = ALL;
    request->tc_name = null;
    request->columns = null;
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
    cond->checkBody = null;
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
    exp->expression = null;
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
    termRet->term = null;
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