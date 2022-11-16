#include "../../backend/support/logger.h"
#include "flex-actions.h"

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

token BeginTableSizePatternAction() {
	LogDebug("BeginTableSizePatternAction.");
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}
token EndTableSizePatternAction() {
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
token StartPatternTag() {
	LogDebug("StartOperatorPatternTag.");
	yylval.token = START;
	return START;
}

token EndPatternTag() {
	LogDebug("EndPatternTag.");
	yylval.token = END;
	return END;
}

token ContainerPatternTag() {
	LogDebug("ContainerPatternTag.");
	yylval.token = CONTAINER;
	return CONTAINER;
}

token TitlePatternTag() {
	LogDebug("TitlePatternTag.");
	yylval.token = TITLE;
	return TITLE;
}

token TablePatternTag() {
	LogDebug("TablePatternTag.");
	yylval.token = TABLE;
	return TABLE;
}

token ColorAttributeKey() {
	LogDebug("ColorAttributeKey.");
	yylval.token = COLOR;
	return COLOR;
}

token SizeAttributeKey() {
	LogDebug("SizeAttributeKey.");
	yylval.token = SIZE;
	return SIZE;
}

token PositionAttributeKey() {
	LogDebug("PositionAttributeKey.");
	yylval.token = POSITION;
	return POSITION;
}

token BoldAttributeValue() {
	LogDebug("BoldAttributeValue.");
	int length = strlen("bold") + 1;
	char * text = (char *) calloc(length, sizeof(char));
	strncpy(text, "bold", length);
	yylval.token_string = text;
	//free(text);
	return BOLD;
}

token UnderlinedAttributeValue() {
	LogDebug("UnderlinedAttributeValue.");
	int length = strlen("underlined") + 1;
	char * text = (char *) calloc(length, sizeof(char));
	strncpy(text, "underlined", length);
	yylval.token_string = text;
	//free(text);
	return UNDERLINED;
}

token ItalicsAttributeValue() {
	LogDebug("ItalicsAttributeValue.");
	int length = strlen("italics") + 1;
	char * text = (char *) calloc(length, sizeof(char));
	strncpy(text, "italics", length);
	yylval.token_string = text;
	//free(text);
	return ITALICS;
}

token ImagePatternTag() {
	LogDebug("ImagePatternTag.");
	yylval.token = IMG;
	return IMG;
}

token LinkPatternTag() {
	LogDebug("LinkPatternTag.");
	yylval.token = LINK;
	return LINK;
}

token RowPatternTag() {
	LogDebug("RowPatternTag.");
	yylval.token = ROW;
	return ROW;
}

token TableSizeAttributeKey() {
	LogDebug("TableSizeAttributeKey.");
	yylval.token = ROWXCOL;
	return ROWXCOL;
}

token TextPatternTag() {
	LogDebug("TextPatternTag.");
	yylval.token = TEXT;
	return TEXT;
}

token FontPatternTag() {
	LogDebug("FontPatternTag.");
	yylval.token = FONT;
	return FONT;
}

token IdAttributeKey() {
	LogDebug("IdAttributeKey.");
	yylval.token = ID;
	return ID;
}

token ColonPatternTag() {
	LogDebug("ColonPatternTag.");
	yylval.token = COLON;
	return COLON;
}

token CommaPatternTag() {
	LogDebug("CommaPatternTag.");
	yylval.token = COMMA;
	return COMMA;
}

token XPatternTag() {
	LogDebug("XPatternTag");
	yylval.token = X;
	return X;
}

token IdAttributeValue(const char * lexeme, const int length) {
	LogDebug("IdAttributeValue: '%s' (length = %d).", lexeme, length);
	char * text = (char *) calloc(length + 1, sizeof(char));
	strncpy(text, lexeme, length);
	yylval.token_string = text;
	//free(text);
	return ID_ATTR;
}

token StringAttributeValue(const char * lexeme, const int length) {
	LogDebug("StringAttributeValue: '%s' (length = %d).", lexeme, length);
	char * text = (char *) calloc(length + 1, sizeof(char));
	strncpy(text, lexeme, length);
	yylval.token_string = text;
	//free(text);
	return STRING;
}


token SizeAttributeValue(const char * lexeme, const int length) {
	LogDebug("SizeAttributeValue: '%s' (length = %d).", lexeme, length);
	char * text = (char *) calloc(length + 1, sizeof(char));
	strncpy(text, lexeme, length);
	yylval.token_string = text;
	//free(text);
	return SIZE_ATTR;
}

token ColorAttributeValue(const char * lexeme, const int length) {
	LogDebug("ColorAttributeValue: '%s' (length = %d).", lexeme, length);
	char * text = (char *) calloc(length + 1, sizeof(char));
	strncpy(text, lexeme, length);
	yylval.token_string = text;
	//free(text);
	return COLOR_ATTR;
}

token PositionAttributeValue(const char * lexeme, const int length) {
	LogDebug("PositionAttributeValue: '%s' (length = %d).", lexeme, length);
	char * text = (char *) calloc(length + 1, sizeof(char));
	strncpy(text, lexeme, length);
	yylval.token_string = text;
	//free(text);
	return POSITION_ATTR;
}

token NumberAttributeValue(const char * lexeme, const int length) {
	LogDebug("NumberAttributeValue: '%s' (length = %d).", lexeme, length);
	char * text = (char *) calloc(length + 1, sizeof(char));
	strncpy(text, lexeme, length);
	yylval.number = atoi(text);
	//free(text);
	return NUMBER;
}

token FontAttributeValue(const char * lexeme, const int length) {
	LogDebug("FontAttributeValue: '%s' (length = %d).", lexeme, length);
	char * text = (char *) calloc(length + 1, sizeof(char));
	strncpy(text, lexeme, length);
	yylval.token_string = text;
	//free(text);
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
