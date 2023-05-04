#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

// Bloque de comentarios multilínea.
void BeginCommentPatternAction();
void EndCommentPatternAction();

// Patrones de símbolos y operadores.
token OpenParenthesisPatternAction(const char * lexeme);
token CloseParenthesisPatternAction(const char * lexeme);
token SemicolonPatternAction(const char * lexeme);
token OpenCurlyBracketsPatternAction(const char * lexeme);
token CloseCurlyBracketsPatternAction(const char * lexeme);
token OpenBracketsPatternAction(const char * lexeme);
token CloseBracketsPatternAction(const char * lexeme);
token CommaPatternAction(const char * lexeme);
token ColonPatternAction(const char * lexeme);
token CreateOperatorPatternAction(const char * lexeme);
token AsOperatorPatternAction(const char * lexeme);
token EqualOperatorPatternAction(const char * lexeme);
token InsertIntoOperatorPatternAction(const char * lexeme);

// Patrones terminales del lenguaje diseñado.
token AdditionOperatorPatternAction(const char * lexeme);
token DivisionOperatorPatternAction(const char * lexeme);
token IntegerPatternAction(const char * lexeme, const int length);
token MultiplicationOperatorPatternAction(const char * lexeme);
token SubtractionOperatorPatternAction(const char * lexeme);

token GreaterThanPatternAction(const char *lexeme);
token LesserThanPatternAction(const char *lexeme);
token GreaterThanEqualToPatternAction(const char *lexeme);
token LesserThanEqualToPatternAction(const char *lexeme);
token EqualToPatternAction(const char *lexeme);
token NotEqualToPatternAction(const char *lexeme);
token CheckPatternAction(const char *lexeme);
token AndPatternAction(const char *lexeme);
token OrPatternAction(const char *lexeme);
token InPatternAction(const char *lexeme);
token AsEnumPatternAction(const char *lexeme);
token UsingKeyPatternAction(const char *lexeme);
token DeletePatternAction(const char *lexeme);
token WherePatternAction(const char *lexeme);
token FromPatternAction(const char *lexeme);
token UniquePatternAction(const char *lexeme);
token QueryOperatorPatternAction(const char *lexeme);
token OnDeletePatternAction(const char * lexeme);
token OnUpdatePatternAction(const char *lexeme);
token CascadePatternAction(const char *lexeme);
token RestrictPatternAction(const char *lexeme);
token SetNullPatternAction(const char *lexeme);
token AllPatternAction(const char *lexeme);
token DistinctPatternAction(const char *lexeme);
token WithPatternAction(const char *lexeme);
token VNullPatternAction(const char *lexeme);
token VTruePatternAction(const char *lexeme);
token VFalsePatternAction(const char *lexeme);
token NullablePatternAction(const char *lexeme);

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);

#endif
