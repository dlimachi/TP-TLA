#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

void BeginCommentPatternAction() {
	LogDebug("BeginCommentPatternAction.");
}

void EndCommentPatternAction() {
	LogDebug("EndCommentPatternAction.");
}

token OpenParenthesisPatternAction(const char * lexeme) {
	LogDebug("OpenParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}

token CloseParenthesisPatternAction(const char * lexeme) {
	LogDebug("CloseParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_PARENTHESIS;
	return CLOSE_PARENTHESIS;
}

token EqualOperatorPatternAction(const char * lexeme){
	LogDebug("EqualsPatternAction: '%s'.", lexeme);
	yylval.token = EQUAL;
	return EQUAL;
}

token SemicolonPatternAction(const char * lexeme){
	LogDebug("SemicolonPatternAction: '%s'.", lexeme);
	yylval.token = SEMICOLON;
	return SEMICOLON;
}

token OpenCurlyBracketsPatternAction(const char * lexeme){
	LogDebug("OpenCurlyBracketsPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_CURLY;
	return OPEN_CURLY;
}

token CloseCurlyBracketsPatternAction(const char * lexeme){
	LogDebug("CloseCurlyBracketsPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_CURLY;
	return CLOSE_CURLY;
}

token OpenBracketsPatternAction(const char * lexeme){
	LogDebug("OpenBracketsPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_BRACKETS;
	return OPEN_BRACKETS;
}

token CloseBracketsPatternAction(const char * lexeme){
	LogDebug("CloseBracketsPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_BRACKETS;
	return CLOSE_BRACKETS;
}

token CommaPatternAction(const char * lexeme){
	LogDebug("CommaPatternAction: '%s'.", lexeme);
	yylval.token = COMMA;
	return COMMA;
}

token ColonPatternAction(const char * lexeme) {
	LogDebug("ColonPatternAction: '%s'.", lexeme);
	yylval.token = COLON;
	return COLON;
}

token CreateOperatorPatternAction(const char * lexeme) {
	LogDebug("CreateOperatorPatternAction: '%s'.", lexeme);
	yylval.token = CREATE;
	return CREATE;
}


token InsertIntoOperatorPatternAction(const char * lexeme) {
	LogDebug("InsertIntoOperatorPatternAction: '%s'.", lexeme);
	yylval.token = INSERT_INTO;
	return INSERT_INTO;
}


token AdditionOperatorPatternAction(const char * lexeme) {
	LogDebug("AdditionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = ADD;
	return ADD;
}

token DivisionOperatorPatternAction(const char * lexeme) {
	LogDebug("DivisionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = DIV;
	return DIV;
}

token IntegerPatternAction(const char * lexeme, const int length) {
	LogDebug("IntegerPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.integer = atoi(lexeme);
	return INTEGER;
}

token MultiplicationOperatorPatternAction(const char * lexeme) {
	LogDebug("MultiplicationOperatorPatternAction: '%s'.", lexeme);
	yylval.token = MUL;
	return MUL;
}

token SubtractionOperatorPatternAction(const char * lexeme) {
	LogDebug("SubtractionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = SUB;
	return SUB;
}

token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}

void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}


token GreaterThanPatternAction(const char *lexeme) {
    LogDebug("GreaterThanPatternAction: '%s'.", lexeme);
    yylval.token = GT;
    return GT;
}

token LesserThanPatternAction(const char *lexeme) {
    LogDebug("LesserThanPatternAction: '%s'.", lexeme);
    yylval.token = LT;
    return LT;
}

token GreaterThanEqualToPatternAction(const char *lexeme) {
    LogDebug("GreaterThanEqualToPatternAction: '%s'.", lexeme);
    yylval.token = GTEQ;
    return GTEQ;
}

token LesserThanEqualToPatternAction(const char *lexeme) {
    LogDebug("LesserThanEqualToPatternAction: '%s'.", lexeme);
    yylval.token = LTEQ;
    return LTEQ;
}

token EqualToPatternAction(const char *lexeme) {
    LogDebug("EqualToPatternAction: '%s'.", lexeme);
    yylval.token = EQ;
    return EQ;
}

token NotEqualToPatternAction(const char *lexeme) {
    LogDebug("NotEqualToPatternAction: '%s'.", lexeme);
    yylval.token = NEQ;
    return NEQ;
}

token CheckPatternAction(const char *lexeme) {
    LogDebug("CheckPatternAction: '%s'.", lexeme);
    yylval.token = CHECK;
    return CHECK;
}

token AndPatternAction(const char *lexeme) {
    LogDebug("AndPatternAction: '%s'.", lexeme);
    yylval.token = AND;
    return AND;
}

token OrPatternAction(const char *lexeme) {
    LogDebug("OrPatternAction: '%s'.", lexeme);
    yylval.token = OR;
    return OR;
}

token InPatternAction(const char *lexeme) {
    LogDebug("InPatternAction: '%s'.", lexeme);
    yylval.token = IN;
    return IN;
}

token AsEnumPatternAction(const char *lexeme) {
    LogDebug("AsEnumPatternAction: '%s'.", lexeme);
    yylval.token = AS_ENUM;
    return AS_ENUM;
}

token AsOperatorPatternAction(const char *lexeme) {
    LogDebug("AsOperatorPatternAction: '%s'.", lexeme);
    yylval.token = AS;
    return AS;
}

token UsingKeyPatternAction(const char *lexeme) {
    LogDebug("UsingKeyPatternAction: '%s'.", lexeme);
    yylval.token = USING_KEY;
    return USING_KEY;
}

token DeletePatternAction(const char *lexeme) {
    LogDebug("DeletePatternAction: '%s'.", lexeme);
    yylval.token = DELETE;
    return DELETE;
}

token WherePatternAction(const char *lexeme) {
    LogDebug("WherePatternAction: '%s'.", lexeme);
    yylval.token = WHERE;
    return WHERE;
}

token FromPatternAction(const char *lexeme) {
    LogDebug("FromPatternAction: '%s'.", lexeme);
    yylval.token = FROM;
    return FROM;
}

token UniquePatternAction(const char *lexeme) {
    LogDebug("UniquePatternAction: '%s'.", lexeme);
    yylval.token = UNIQUE;
    return UNIQUE;
}

token QueryOperatorPatternAction(const char *lexeme) {
    LogDebug("QueryOperatorPatternAction: '%s'.", lexeme);
    yylval.token = QUERY;
    return QUERY;
}

token OnDeletePatternAction(const char *lexeme) {
    LogDebug("OnDeletePatternAction: '%s'.", lexeme);
    yylval.token = ON_DELETE;
    return ON_DELETE;
}

token OnUpdatePatternAction(const char *lexeme) {
    LogDebug("OnUpdatePatternAction: '%s'.", lexeme);
    yylval.token = ON_UPDATE;
    return ON_UPDATE;
}

token CascadePatternAction(const char *lexeme) {
    LogDebug("CascadePatternAction: '%s'.", lexeme);
    yylval.token = CASCADE;
    return CASCADE;
}

token RestrictPatternAction(const char *lexeme) {
    LogDebug("RestrictPatternAction: '%s'.", lexeme);
    yylval.token = RESTRICT;
    return RESTRICT;
}

token SetNullPatternAction(const char *lexeme) {
    LogDebug("SetNullPatternAction: '%s'.", lexeme);
    yylval.token = SET_NULL;
    return SET_NULL;
}

token WithPatternAction(const char *lexeme) {
    LogDebug("AllPatternAction: '%s'.", lexeme);
    yylval.token = WITH;
    return WITH;
}

token AllPatternAction(const char *lexeme) {
    LogDebug("AllPatternAction: '%s'.", lexeme);
    yylval.token = ALL;
    return ALL;
}


token DistinctPatternAction(const char *lexeme) {
    LogDebug("DistinctPatternAction: '%s'.", lexeme);
    yylval.token = DISTINCT;
    return DISTINCT;
}

token VNullPatternAction(const char *lexeme) {
    LogDebug("NullPatternAction: '%s'.", lexeme);
    yylval.token = VNULL;
    return VNULL;	
}

token NullablePatternAction(const char *lexeme) {
    LogDebug("NullPatternAction: '%s'.", lexeme);
    yylval.token = NULLABLE;
    return NULLABLE;	
}

token VTruePatternAction(const char *lexeme) {
    LogDebug("SetNullPatternAction: '%s'.", lexeme);
    yylval.token = VTRUE;
    return VTRUE;
}

token VFalsePatternAction(const char *lexeme) {
    LogDebug("SetNullPatternAction: '%s'.", lexeme);
    yylval.token = VFALSE;
    return VFALSE;
}