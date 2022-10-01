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

//void BeginStringPatternAction();
//void EndStringPatternAction();

// Patrones terminales del lenguaje diseñado.
token StartPatternTag(const char * lexeme);
token EndPatternTag(const char * lexeme);
token ContainerPatternTag(const char * lexeme);
token TitlePatternTag(const char * lexeme);
token TablePatternTag(const char * lexeme);
token StylePatternTag(const char * lexeme);
token SizePatternTag(const char * lexeme);
token ColorPatternTag(const char * lexeme);
token PositionPatternTag(const char * lexeme);
token BoldPatternTag(const char * lexeme);
token UnderlinedPatternTag(const char * lexeme);
token ItalicsPatternTag(const char * lexeme);
token ImagePatternTag(const char * lexeme);
token LinkPatternTag(const char * lexeme);
token RowPatternTag(const char * lexeme);
token TextPatternTag(const char * lexeme);
token IdPatternTag(const char * lexeme);
token ColonPatternTag(const char * lexeme);
token CommaPatternTag(const char * lexeme);
token XPatternTag(const char * lexeme);
token TableSizePatternTag(const char * lexeme);


token IdPatternAttribute(const char * lexeme);
token StringPatternAttribute(const char * lexeme);
token SourcePatternAttribute(const char * lexeme);
token SizePatternAttribute(const char * lexeme);
token ColorPatternAttribute(const char * lexeme);
token StylePatternAttribute(const char * lexeme);
token PositionPatternAttribute(const char * lexeme);
token NumberPatternAttribute(const char * lexeme);
token FontPatternAttribute(const char * lexeme);
token EndlinePatternAttribute(const char * lexeme);

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);

#endif
