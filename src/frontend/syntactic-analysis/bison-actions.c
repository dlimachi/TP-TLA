#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include "abstract-syntax-tree.h"

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
int ProgramGrammarAction(const int value) {
	LogDebug("\tProgramGrammarAction(%d)", value);
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
	state.result = value;
	return value;
}

int return0() {
	LogDebug("bien");
	state.succeed = true;
	return 0;
}

int AdditionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("\tAdditionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Add(leftValue, rightValue);
}

int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("\tSubtractionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Subtract(leftValue, rightValue);
}

int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("\tMultiplicationExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Multiply(leftValue, rightValue);
}

int DivisionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("\tDivisionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Divide(leftValue, rightValue);
}

int FactorExpressionGrammarAction(const int value) {
	LogDebug("\tFactorExpressionGrammarAction(%d)", value);
	return value;
}

int ExpressionFactorGrammarAction(const int value) {
	LogDebug("\tExpressionFactorGrammarAction(%d)", value);
	return value;
}

int ConstantFactorGrammarAction(const int value) {
	LogDebug("\tConstantFactorGrammarAction(%d)", value);
	return value;
}

int IntegerConstantGrammarAction(const int value) {
	LogDebug("\tIntegerConstantGrammarAction(%d)", value);
	return value;
}

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
RequestAllGrammarAction()

CheckGrammarAction($2, $4)

CheckConditionGrammarAction($1)

CheckAndGrammarAction($1, $3)

CheckOrGrammarAction($1, $3)

ConditionGrammarAction($1, $2, $3)

ExpressionTermGrammarAction($1)

ExpressionAddGrammarAction($1,$3)

ExpressionSubGrammarAction($1,$3)

Term * TermFactorGrammarAction(Factor * factor)

Term * TermAllGrammarAction(Term * term , Factor * factor) {
    LogDebug("\tTermAllGrammarAction");
    Term * termRet = malloc(sizeof(Term));
    termRet->tyep = ALL;
    termRet->term = term;
    termRet->factor = factor;
    return factor;
}

Term * TermDivGrammarAction(Term * term , Factor * factor) {
    LogDebug("\tTermDivGrammarAction");
    Term * termRet = malloc(sizeof(Term));
    termRet->tyep = DIV;
    termRet->term = term;
    termRet->factor = factor;
    return factor;
}

Factor * Tc_nameFactorGrammarAction(char * data) {
	LogDebug("\tTc_nameFactorGrammarAction (%s)", data);
	Factor * factor = malloc(sizeof(Factor));
	factor->type = TC_NAME;
    factor->data = data;
	return factor;
}

Factor * IntegerFactorGrammarAction(char * data) {
	LogDebug("\tIntegerFactorGrammarAction (%s)", data);
	Factor * factor = malloc(sizeof(Factor));
	factor->type = INT;
    factor->data = data;
	return factor;
}


Factor * StringFactorGrammarAction(char * data) {
	LogDebug("\tStringFactorGrammarAction (%s)", data);
	Factor * factor = malloc(sizeof(Factor));
	factor->type = STRING;
    factor->data = data;
	return factor;
}

Comparison * LesserConstantGrammarAction() {
	LogDebug("\tLesserConstantGrammarAction");
	Comparison * comp = malloc(sizeof(Comparison));
	comp->type = LT;
	return comp;
}

Comparison * EqualConstantGrammarAction() {
	LogDebug("\tEqualConstantGrammarAction");
	Comparison * comp = malloc(sizeof(Comparison));
	comp->type = EQ;
	return comp;
}

Comparison * GreaterOrEqualConstantGrammarAction() {
	LogDebug("\tEqualConstantGrammarAction");
	Comparison * comp = malloc(sizeof(Comparison));
	comp->type = GT;
	return comp;
}

Comparison * LesserOrEqualConstantGrammarAction(){
	Comparison * comp = malloc(sizeof(Comparison));
	comp->type = LTEQ;
	return comp;
}

Comparison * NotEqualConstantGrammarAction() {
	LogDebug("\tNotEqualConstantGrammarAction");
	Comparison * comp = malloc(sizeof(Comparison));
	comp->type = NEQ;
	return comp;
}