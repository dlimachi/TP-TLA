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
"+"											{ return AdditionOperatorPatternAction(yytext); }
"-"											{ return SubtractionOperatorPatternAction(yytext); }
"*"											{ return MultiplicationOperatorPatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }

"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }

"{"                                         { ECHO; return LCURLY; }
"}"                                         { ECHO; return RCURLY; }
"["                                         { ECHO; return LBRAC; }
"]"                                         { ECHO; return RBRAC; }
","                                         { ECHO; return COMMA; }
":"                                         { ECHO; return COLON; }
"true"                                      { ECHO; return VTRUE; }
"false"                                     { ECHO; return VFALSE; }
"null"                                      { ECHO; return VNULL; }
[ \t\r\n]+                                  { /* eat whitespace */ }
\"[^"]*\"                                   { yylval.string = strdup(yytext); ECHO; return STRING; }
[1-9]+\.?[0-9]*{EXP}?                       { ECHO; yylval.decimal = atof(yytext); return DECIMAL; }

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
