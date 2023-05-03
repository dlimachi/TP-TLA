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

<<<<<<< HEAD
{digit}+									{ return IntegerPatternAction(yytext, yyleng); }
=======
"INSERT INTO"                               { return InsertIntoOperatorPatternAction(yytext) ;}
"CREATE"                                    { return CreateOperatorPatternAction(yytext);}
"TYPE"                                      { return TYPE; }
"AS"                                        { return AS;}
"KEY"                                       { return KEY; }
"USING"                                     { return USING; }
>>>>>>> c826025f0a154d58a2c1694a370e0f812a49956c

"+"											{ return AdditionOperatorPatternAction(yytext); }
"-"											{ return SubtractionOperatorPatternAction(yytext); }
"*"											{ return MultiplicationOperatorPatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }

"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }

<<<<<<< HEAD
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

=======
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
>>>>>>> c826025f0a154d58a2c1694a370e0f812a49956c
{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }


"INSERT INTO"                               { return InsertIntoOperatorPatternAction(yytext) ;}
"CREATE"                                    { return CreateOperatorPatternAction(yytext);}
"AS"                                        { return AsOperatorPatternAction(yytext); }
"KEY"                                       { return KEY; }
"USING"                                     { return USING; }
"DELETE"                                    { return DELETE; }
"WHERE"                                     { return WHERE; }
"FROM"                                      { return FROM; }
"UNIQUE"                                    { return UNIQUE; }

\"[^"]*\"                                   {  yylval.string = strdup(yytext); return STRING; }
-?[0-9]+(\.[0-9]+)?                         {  yylval.decimal = atof(yytext); return DECIMAL; }
[a-zA-Z_][a-zA-Z0-9_]{0,127}                {  yylval.string = strdup(yytext); ECHO; return TC_NAME;}

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
