%{

#include "flex-actions.h"

%}

EXP ([Ee][-+]?[0-9]+)
/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT

/* Patrones reutilizables. */
digit			[0-9]
endline			[\n]
whitespace		[ \f\n\r\t\v]

%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"INSERT INTO"                               { return InsertIntoOperatorPatternAction(yytext) ;}
"CREATE"                                    { return CreateOperatorPatternAction(yytext);}
"TYPE"                                      { return TYPE; }
"AS"                                        { return AS;}
"KEY"                                       { return KEY; }
"USING"                                     { return USING; }

"+"											{ return AdditionOperatorPatternAction(yytext); }
"-"											{ return SubtractionOperatorPatternAction(yytext); }
"*"											{ return MultiplicationOperatorPatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }

"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }

"{"                                         {  return LCURLY; }
"}"                                         {  return RCURLY; }
"["                                         {  return LBRAC; }
"]"                                         {  return RBRAC; }
","                                         {  return COMMA; }
":"                                         {  return COLON; }
"true"                                      {  return VTRUE; }
"false"                                     {  return VFALSE; }
"null"                                      {  return VNULL; }
\"[^"]*\"                                   {  yylval.string = strdup(yytext); return STRING; }
-?[0-9]+(\.[0-9]+)?                         {  yylval.decimal = atof(yytext); return DECIMAL; }
[a-zA-Z_][a-zA-Z0-9_]{0,127}                {  yylval.string = strdup(yytext); ECHO; return TABLE_NAME;}


{digit}+									{ return IntegerPatternAction(yytext, yyleng); }
"."                                         { return DOT; }
{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
