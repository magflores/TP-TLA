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

void BeginStringPatternAction();
void EndStringPatternAction();

token BeginTableSizePatternAction(const char * lexeme);
token EndTableSizePatternAction(const char * lexeme);



// Patrones terminales del lenguaje diseñado.
token StartPatternTag(const char * lexeme);
token EndPatternTag(const char * lexeme);
token ContainerPatternTag(const char * lexeme);
token TitlePatternTag(const char * lexeme);
token TablePatternTag(const char * lexeme);
token ImagePatternTag(const char * lexeme);
token LinkPatternTag(const char * lexeme);
token RowPatternTag(const char * lexeme);
token TextPatternTag(const char * lexeme);
token FontPatternTag(const char * lexeme);
token ColonPatternTag(const char * lexeme);
token CommaPatternTag(const char * lexeme);
token XPatternTag(const char * lexeme);

token IdAttributeKey(const char * lexeme);
token StyleAttributeKey(const char * lexeme);
token SizeAttributeKey(const char * lexeme);
token ColorAttributeKey(const char * lexeme);
token PositionAttributeKey(const char * lexeme);
token BoldAttributeValue(const char * lexeme);
token UnderlinedAttributeValue(const char * lexeme);
token ItalicsAttributeValue(const char * lexeme);
token TableSizeAttributeKey(const char * lexeme);


token IdAttributeValue(const char * lexeme, const int length);
token StringAttributeValue(const char * lexeme, const int length);
token SizeAttributeValue(const char * lexeme, const int length);
token ColorAttributeValue(const char * lexeme, const int length);
token StyleAttributeValue(const char * lexeme, const int length);
token PositionAttributeValue(const char * lexeme, const int length);
token NumberAttributeValue(const char * lexeme, const int length);
token FontAttributeValue(const char * lexeme, const int length);

token EndlinePatternAttribute(const char * lexeme, const int length);

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);

#endif
