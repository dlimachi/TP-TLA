#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"


/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
int ProgramGrammarAction(const int value);
int return0();

//General
General * GeneralInsertBodyGrammarAction(InsertBody * InsertBody);
General * GeneralCreateBodyGrammarAction(CreateBody * createBody);
General * GeneralDeleteBodyGrammarAction(DeleteBody * deleteBody);
General * GeneralCheckGrammarAction(Check * chek);
General * GeneralQueryBodyGrammarAction(QueryBody * queryBody);

//Insert
InsertBody * InsertObjectsGrammarAction(char * tcName, Objects* objects);

//Check
Check * CheckGrammarAction(char *tc_name, CheckBody * checkBody);

//CheckBody
CheckBody * CheckConditionGrammarAction(Condition * condition);
CheckBody * CheckAndGrammarAction(CheckBody * checkBody, Condition * condition);
CheckBody * CheckOrGrammarAction(CheckBody * checkBody, Condition * condition);

//Condition
Condition * ConditionGrammarAction(Expression * expL, Comparison * comparison, Expression * expR);

// Expression.
Expression * ExpressionTermGrammarAction(Term * term);
Expression * ExpressionAddGrammarAction(Expression * expression, Term * term);
Expression * ExpressionSubGrammarAction(Expression * expression, Term * term);

//Terminos
Term * TermFactorGrammarAction(Factor * factor);
Term * TermAllGrammarAction(Term * term , Factor * factor);
Term * TermDivGrammarAction(Term * term , Factor * factor);

// Factores.
Factor * Tc_nameFactorGrammarAction(char * data);
Factor * IntegerFactorGrammarAction(char * data);
Factor * StringFactorGrammarAction(char * data);

// Comparison
Comparison * LesserConstantGrammarAction();
Comparison * EqualConstantGrammarAction();
Comparison * GreaterOrEqualConstantGrammarAction();
Comparison * LesserOrEqualConstantGrammarAction();
Comparison * NotEqualConstantGrammarAction();
#endif
