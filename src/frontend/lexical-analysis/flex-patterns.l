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

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

"+"											{ return AdditionOperatorPatternAction(yytext); }
"-"											{ return SubtractionOperatorPatternAction(yytext); }
"?"											{ return MultiplicationOperatorPatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }

">"                                         { return GT; }
"<"                                         { return LT; }
"=="                                        { return EQ; }

"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }

"="                                         { return EqualOperatorPatternAction(yytext); }
";"                                         { return SemicolonPatternAction(yytext); }
"{"                                         { return OpenCurlyBracketsPatternAction(yytext); }
"}"                                         { return CloseCurlyBracketsPatternAction(yytext); }
"["                                         { return OpenBracketsPatternAction(yytext); }
"]"                                         { return CloseBracketsPatternAction(yytext); }
","                                         { return CommaPatternAction(yytext); }
":"                                         { return ColonPatternAction(yytext); }

"true"                                      {  return VTRUE; }
"false"                                     {  return VFALSE; }
"null"                                      {  return VNULL; }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }

"CHECK"                                     { return CHECK; }
"AND"                                       { return AND; }
"OR"                                        { return OR; }
"IN"                                        { return IN; }
"AS ENUM"                                      { return AS_ENUM; }

"INSERT INTO"                               { return InsertIntoOperatorPatternAction(yytext); }
"CREATE"                                    { return CreateOperatorPatternAction(yytext); }
"AS"                                        { return AsOperatorPatternAction(yytext); }
"USING KEY"                                 { return USING_KEY; }
"DELETE"                                    { return DELETE; }
"WHERE"                                     { return WHERE; }
"FROM"                                      { return FROM; }
"UNIQUE"                                    { return UNIQUE; }
"QUERY"                                     { return QueryOperatorPatternAction(yytext); }
"*"                                         { return ALL;}
"!"                                         { return DISTINCT; }


\"[^"]*\"                                   {  yylval.string = strdup(yytext); return STRING; }
-?[0-9]+(\.[0-9]+)?                         {  yylval.decimal = atof(yytext); return DECIMAL; }
[a-zA-Z_][a-zA-Z0-9_]{0,127}                {  yylval.string = strdup(yytext); ECHO; return TC_NAME; }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
