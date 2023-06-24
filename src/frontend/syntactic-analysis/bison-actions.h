#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
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

//Objects
Objects * ObjectsGrammarAction(Object * object);
Objects * ObjectsMultipleGrammarAction(Objects * objects, Object * object);
Object * ObjectGrammarAction(Pairs* pairs);

//Pairs
Pairs * PairsGrammarAction(Pair* pair);
Pairs * PairsCommaGrammarAction(Pairs* pairsArg,Pair* pair);
Pair * PairStringStringGrammarAction(char* cName,char* cValue);
Pair * PairStringIntegerGrammarAction(char* cName,char* cValue);
Pair * PairStringDecimalGrammarAction(char* cName,char* cValue);
Pair * PairStringTrueGrammarAction(char* cName);
Pair * PairStringFalseGrammarAction(char* cName);
Pair * PairStringNullGrammarAction(char* cName);

//CreateBody
CreateBody * CreateBodyGrammarAction(CreateTable * createTable, Statements * statements);

//CreateTable
CreateTable * CreateTableNameGrammarAction(char * tcName);
CreateTable * CreateTableUsingNameGrammarAction(char * tcName, char * keyName);

//Statements
Statements * StatementsMultipleGrammarAction(Statements * statementsArg, Statement * statement);
Statements * StatementsSimpleGrammarAction(Statement * statement);
Statement * StatementColumnsGrammarAction(Columns * columns, char * asName);
Statement * StatementColumnsNullableGrammarAction(Columns * columns, char * asName);
Statement * StatementSimpleGrammarAction(char * columnName, SingleType * singleType);
Statement * StatementFromGrammarAction(char * columnName, SingleType * singleType, char * tcNameFrom, char * columnNameFrom);
Statement * StatementOnDeleteGrammarAction(char * columnName, SingleType * singleType, char * tcNameFrom, char * columnNameFrom, Options * options);
Statement * StatementOnUpdateGrammarAction(char * columnName, SingleType * singleType, char * tcNameFrom, char * columnNameFrom, Options * options);
Statement * StatementColumnsAsEnumGrammarAction(Columns * columns, EnumTypes * enumTypes);
Statement * StatementAsEnumGrammarAction(char * columnName, EnumTypes * enumTypes);

//Options
Options * OptionsCascadeGrammarAction();
Options * OptionsSetNullGrammarAction();
Options * OptionsRestrictGrammarAction();

//SingleType
SingleType * SingleTypeGrammarAction(char * tcName);
SingleType * SingleTypeNullableGrammarAction(char * tcName);
SingleType * SingleTypeWithGrammarAction(char * tcName, char * withTcName);

//EnumType
EnumTypes * EnumTypesMultipleGrammarAction(EnumTypes * enumTypesArg, char * string);
EnumTypes * EnumTypesSingleGrammarAction(char * string);

//Colums
Columns * ColumnsMultipleGrammarAction(Columns * columns, Column * column);
Columns * ColumnsSingleGrammarAction( Column * column);
Column * ColumnGrammarAction( char * cName);
Column * ColumnUniqueGrammarAction( char * cName);

//DeleteBody
DeleteBody * DeleteFromWhereGrammarAction( char * fromTable, char * conditionColumn, char * conditionString);
DeleteBody * DeleteFromGrammarAction( char * fromTable, Object * object);

//QueryBody
QueryBody * QueryBodyGrammarAction( char * queryName, Request * request, char * tc_name, char * condition);

//Request
Request * RequestTc_nameGrammarAction( char * tcName);
Request * RequestColumnsGrammarAction( Columns * columns);
Request * RequestDistinctColumnsGrammarAction( Columns * columns);
Request * RequestAllGrammarAction();

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


void FreeInsertBody(InsertBody* insertBody);
void FreeColumn(Column * column);
void FreeColumns(Columns * columns);
void FreePair(Pair* pair);
void FreePairs(Pairs* pairs);
void FreeObject(Object* object);
void FreeObjects(Objects* objects);
void FreeInsertBody(InsertBody* insertBody);
void FreeSingleType(SingleType* singleType);
void FreeOptions(Options* options);
void FreeEnumTypes(EnumTypes* enumTypes);
void FreeStatement(Statement* statement);
void FreeStatements(Statements* statements);
void FreeCreateTable(CreateTable* createTable);
void FreeCreateBody(CreateBody* createBody);
void FreeDeleteBody(DeleteBody* deleteBody);
void FreeCheck(Check* check);
void FreeRequest(Request* request);
void FreeQueryBody(QueryBody* queryBody);
void FreeGeneral(General* general);

#endif
