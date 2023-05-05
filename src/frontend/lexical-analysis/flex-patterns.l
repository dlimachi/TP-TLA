%{

#include "flex-actions.h"

%}

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
"?"											{ return NullablePatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }

">"                                         { return GreaterThanPatternAction(yytext); }
"<"                                         { return LesserThanPatternAction(yytext); }
">="                                        { return GreaterThanEqualToPatternAction(yytext); }
"<="                                        { return LesserThanEqualToPatternAction(yytext); }
"=="                                        { return EqualToPatternAction(yytext); }
"!="                                        { return NotEqualToPatternAction(yytext); }
"<>"                                        { return NotEqualToPatternAction(yytext); }

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

"true"                                      {  return VTruePatternAction(yytext); }
"false"                                     {  return VFalsePatternAction(yytext); }
"null"                                      {  return VNullPatternAction(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }

"CHECK"                                     { return CheckPatternAction(yytext); }
"AND"                                       { return AndPatternAction(yytext); }
"OR"                                        { return OrPatternAction(yytext); }
"IN"                                        { return InPatternAction(yytext); }
"AS ENUM"                                   { return AsEnumPatternAction(yytext); }

"INSERT INTO"                               { return InsertIntoOperatorPatternAction(yytext); }
"CREATE"                                    { return CreateOperatorPatternAction(yytext); }
"AS"                                        { return AsOperatorPatternAction(yytext); }
"USING KEY"                                 { return UsingKeyPatternAction(yytext); }
"DELETE"                                    { return DeletePatternAction(yytext); }
"WHERE"                                     { return WherePatternAction(yytext); }
"FROM"                                      { return FromPatternAction(yytext); }
"UNIQUE"                                    { return UniquePatternAction(yytext); }
"QUERY"                                     { return QueryOperatorPatternAction(yytext); }
"ON DELETE"                                 { return OnDeletePatternAction(yytext); }
"ON UPDATE"                                 { return OnUpdatePatternAction(yytext); }
"CASCADE"                                   { return CascadePatternAction(yytext); }
"RESTRICT"                                  { return RestrictPatternAction(yytext); }
"NO ACTION"                                 { return RestrictPatternAction(yytext); }
"SET NULL"                                  { return SetNullPatternAction(yytext); }
"WITH"                                      { return WithPatternAction(yytext); }
"*"                                         { return AllPatternAction(yytext);}
"!"                                         { return DistinctPatternAction(yytext); }


\"[^"]*\"                                   {  yylval.string = strdup(yytext); return STRING; }
-?[0-9]+(\.[0-9]+)?                         {  yylval.decimal = atof(yytext); return DECIMAL; }
[a-zA-Z_][a-zA-Z0-9_]{0,127}                {  yylval.string = strdup(yytext); ECHO; return TC_NAME; }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
