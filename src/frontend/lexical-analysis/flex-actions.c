#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

/**
 * Implementación de "flexnTags.h".
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

// Bloque de comentarios multilínea.
void BeginCommentPatternAction() {
	LogDebug("BeginCommentPatternAction.");
}
void EndCommentPatternAction() {
	LogDebug("EndCommentPatternAction.");
}

token BeginTableSizePatternAction(const char * lexeme) {
	LogDebug("BeginTableSizePatternAction.");
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}
token EndTableSizePatternAction(const char * lexeme) {
	LogDebug("EndTableSizePatternAction.");
	yylval.token = CLOSE_PARENTHESIS;
	return CLOSE_PARENTHESIS;
}

void BeginStringPatternAction() {
	LogDebug("BeginStringPatternAction.");
}

void EndStringPatternAction() {
	LogDebug("EndStringPatternAction.");
}

// Patrones terminales del lenguaje diseñado.
token StartPatternTag(const char * lexeme) {
	LogDebug("StartOperatorPatternTag: '%s'.", lexeme);
	yylval.token = START;
	return START;
}

token EndPatternTag(const char * lexeme) {
	LogDebug("EndPatternTag: '%s'.", lexeme);
	yylval.token = END;
	return END;
}

token ContainerPatternTag(const char * lexeme) {
	LogDebug("ContainerPatternTag: '%s'.", lexeme);
	yylval.token = CONTAINER;
	return CONTAINER;
}

token TitlePatternTag(const char * lexeme) {
	LogDebug("TitlePatternTag: '%s'.", lexeme);
	yylval.token = TITLE;
	return TITLE;
}

token TablePatternTag(const char * lexeme) {
	LogDebug("TablePatternTag: '%s'.", lexeme);
	yylval.token = TABLE;
	return TABLE;
}


token StylePatternTag(const char * lexeme) {
	LogDebug("StylePatternTag: '%s'.", lexeme);
	yylval.token = STYLE;
	return STYLE;
}

token ColorPatternTag(const char * lexeme) {
	LogDebug("ColorPatternTag: '%s'.", lexeme);
	yylval.token = COLOR;
	return COLOR;
}

token SizePatternTag(const char * lexeme) {
	LogDebug("SizePatternTag: '%s'.", lexeme);
	yylval.token = SIZE;
	return SIZE;
}

token PositionPatternTag(const char * lexeme) {
	LogDebug("PositionPatternTag: '%s'.", lexeme);
	yylval.token = POSITION;
	return POSITION;
}

token BoldPatternTag(const char * lexeme) {
	LogDebug("BoldPatternTag: '%s'.", lexeme);
	yylval.token = BOLD;
	return BOLD;
}

token UnderlinedPatternTag(const char * lexeme) {
	LogDebug("UnderlinedPatternTag: '%s'.", lexeme);
	yylval.token = UNDERLINED;
	return UNDERLINED;
}

token ItalicsPatternTag(const char * lexeme) {
	LogDebug("ItalicsPatternTag: '%s'.", lexeme);
	yylval.token = ITALICS;
	return ITALICS;
}

token ImagePatternTag(const char * lexeme) {
	LogDebug("ImagePatternTag: '%s'.", lexeme);
	yylval.token = IMG;
	return IMG;
}

token LinkPatternTag(const char * lexeme) {
	LogDebug("LinkPatternTag: '%s'.", lexeme);
	yylval.token = LINK;
	return LINK;
}

token RowPatternTag(const char * lexeme) {
	LogDebug("RowPatternTag: '%s'.", lexeme);
	yylval.token = ROW;
	return ROW;
}

token TableSizePatternTag(const char * lexeme) {
	LogDebug("TableSizePatternTag: '%s'.", lexeme);
	yylval.token = ROWXCOL;
	return ROWXCOL;
}

token TextPatternTag(const char * lexeme) {
	LogDebug("TextPatternTag: '%s'.", lexeme);
	yylval.token = TEXT;
	return TEXT;
}

token FontPatternTag(const char * lexeme) {
	LogDebug("FontPatternTag: '%s'.", lexeme);
	yylval.token = FONT;
	return FONT;
}

token IdPatternTag(const char * lexeme) {
	LogDebug("IdPatternTag: '%s'.", lexeme);
	yylval.token = ID;
	return ID;
}

token ColonPatternTag(const char * lexeme) {
	LogDebug("ColonPatternTag: '%s'.", lexeme);
	yylval.token = COLON;
	return COLON;
}

token CommaPatternTag(const char * lexeme) {
	LogDebug("CommaPatternTag: '%s'.", lexeme);
	yylval.token = COMMA;
	return COMMA;
}

token XPatternTag(const char * lexeme) {
	LogDebug("XPatternTag: '%s'.", lexeme);
	yylval.token = X;
	return X;
}

token IdPatternAttribute(const char * lexeme, const int length) {
	LogDebug("IdPatternAttribute: '%s' (length = %d).", lexeme, length);
	yylval.token = ID_ATTR;
	return ID_ATTR;
}

token StringPatternAttribute(const char * lexeme, const int length) {
	LogDebug("StringPatternAttribute: '%s' (length = %d).", lexeme, length);
	yylval.token = STRING;
	return STRING;
}


token SizePatternAttribute(const char * lexeme, const int length) {
	LogDebug("SizePatternAttribute: '%s' (length = %d).", lexeme, length);
	yylval.token = SIZE_ATTR;
	return SIZE_ATTR;
}

token ColorPatternAttribute(const char * lexeme, const int length) {
	LogDebug("ColorPatternAttribute: '%s' (length = %d).", lexeme, length);
	yylval.token = COLOR_ATTR;
	return COLOR_ATTR;
}

token PositionPatternAttribute(const char * lexeme, const int length) {
	LogDebug("PositionPatternAttribute: '%s' (length = %d).", lexeme, length);
	yylval.token = POSITION_ATTR;
	return POSITION_ATTR;
}

token NumberPatternAttribute(const char * lexeme, const int length) {
	LogDebug("NumberPatternAttribute: '%s' (length = %d).", lexeme, length);
	yylval.token = NUMBER;
	return NUMBER;
}

token FontPatternAttribute(const char * lexeme, const int length) {
	LogDebug("FontPatternAttribute: '%s' (length = %d).", lexeme, length);
	yylval.token = FONT_ATTR;
	return FONT_ATTR;
}

token EndlinePatternAttribute(const char * lexeme, const int length) {
	LogDebug("EndlinePatternAttribute: '%s' (length = %d).", lexeme, length);
	yylval.token = ENDLINE;
	return ENDLINE;
}

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}
