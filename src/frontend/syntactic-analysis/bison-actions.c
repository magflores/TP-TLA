#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
void ProgramGrammarAction(tExprs * exprs) {
	LogDebug("Reconozco patrón. ProgramGrammarAction()");
	tProgram * value = malloc(sizeof(tProgram));
	if(value == NULL)
		return;
	value->initial = exprs;
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	state.succeed = true;
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/
	state.result = value;
}

tExprs * ExprAction(tExpr * exp){
	tExprs * exps = malloc(sizeof(tExprs));
	if(exps == NULL)
		return NULL;
	exp->next = NULL;
	exps->first = exp;
	exps->size = 1;
	return exps;
}

tExprs * ExprsAction(tExprs * exps, tExpr * exp){
	tExpr * aux = exps->first;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = exp;
	exps->size++;
	return exps;
}

void EmptyExprAction(){
	return;
}

tExpr * TitleExprAction(tTitle * title){
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = TITLEEXPR;
	exp->expr = title;
	exp->next = NULL;
	return exp;
}

tExpr *  FontExprAction(tFont * font) {
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = FONTEXPR;
	exp->expr = font;
	exp->next = NULL;
	return exp;
}

tExpr * TextExprAction(tText * text){
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = TEXTEXPR;
	exp->expr = text;
	exp->next = NULL;
	return exp;
}

tExpr * ImgExpressionAction(tImage * img){
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = IMGEXPR;
	exp->expr = img;
	exp->next = NULL;
	return exp;
}

tExpr * LinkExprAction(tLink * link){
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = LINKEXPR;
	exp->expr = link;
	exp->next = NULL;
	return exp;
}

tExpr * TableExprAction(tTable * table){
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = TABLEEXPR;
	exp->expr = table;
	exp->next = NULL;
	return exp;
}

tExpr * ContainerExprAction(tContainer * div){
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = CONTAINEREXPR;
	exp->expr = div;
	exp->next = NULL;
	return exp;
}

tTitle * TitleWithoutAttrsGrammarAction(char * content){
	tTitle * title = malloc(sizeof(tTitle));
	if(title == NULL){
		return NULL;
	}
	title->content = malloc(sizeof(char) * (strlen(content) + 1));
	strcpy(title->content, content);
	title->attrs = NULL;
	return title;
}

tTitle * TitleWithAttrsGrammarAction(tAttributes * attrs, char * content){
	tTitle * title = malloc(sizeof(tTitle));
	if(title == NULL){
		return NULL;
	}
	title->content = malloc(sizeof(char) * (strlen(content) + 1));
	strcpy(title->content, content);
	title->attrs = attrs;
	return title;
}

tFont * FontGrammarAction(char * content){
	tFont * font = malloc(sizeof(tFont));
	if(font == NULL){
		return NULL;
	}
	font->content = malloc(sizeof(char) * (strlen(content) + 1));
	strcpy(font->content, content);
	return font;
}

tText * TextWithoutAttrsGrammarAction(char * content){
	tText* text = malloc(sizeof(tText));
	if(text == NULL){
		return NULL;
	}
	text->content = malloc(sizeof(char) * (strlen(content) + 1));
	strcpy(text->content, content);
	text->attrs = NULL;
	return text;
}

tText * TextWithAttrsGrammarAction(tAttributes * attrs, char * content){
	tText * text = malloc(sizeof(tText));
	if(text == NULL){
		return NULL;
	}
	text->content = malloc(sizeof(char) * (strlen(content) + 1));
	strcpy(text->content, content);
	text->attrs = attrs;
	return text;
}

tImage * ImgWithAttrsGrammarAction(tAttributes * attrs, char * link){
	tImage * img = malloc(sizeof(tImage));
	if(img == NULL)
		return NULL; 
	img->link = malloc(sizeof(char) * (strlen(link) + 1));
	strcpy(img->link, link);
	img->attrs = attrs;
	return img;
}

tImage * ImgWithoutAttrsGrammarAction(char * link){
	tImage * img = malloc(sizeof(tImage));
	if(img == NULL)
		return NULL;
	img->link = malloc(sizeof(char) * (strlen(link) + 1));
	strcpy(img->link, link);
	img->attrs = NULL;
	return img;
}

tLink * LinkWithAttrsGrammarAction(tAttributes * attrs, char * ref, char * text){
	tLink * link = malloc(sizeof(link));
	if(link == NULL){
		return NULL;
	}

	link->ref = malloc(sizeof(char)*(strlen(ref) - 4));
	link->text = malloc(sizeof(char)*(strlen(text) + 1));
	strncpy(link->ref, ref + 5, strlen(ref) - 7);
	strcpy(link->text, text);
	link->attrs = attrs;
	return link;
}

tLink * LinkWithoutAttrsGrammarAction(char * ref, char * text){
	tLink * link = malloc(sizeof(link));
	if(link == NULL){
		return NULL;
	}

	link->ref = malloc(sizeof(char)*(strlen(ref) - 4));
	link->text = malloc(sizeof(char)*(strlen(text) + 1));
	strncpy(link->ref, ref + 5, strlen(ref) - 6);
	strcpy(link->text, text);
	link->attrs = NULL;
	return link;
}

tTable * TableGrammarAction(tTableAttrs * attrs, tRows * rows){
	tTable * table = malloc(sizeof(table));
	if(table == NULL){
		return NULL;
	}
	table->attrs = attrs;
	table->firstRow = rows;
	return table;
}

tContainer * ContainerWithAttrsGrammarAction(tAttributes * attrs, tExprs * exprs){
	tContainer * container = malloc(sizeof(container));
	if(container == NULL){
		return NULL;
	}
	container->attrs = attrs;
	container->content = exprs;
	container->size = 1; //????
	return container;
}

tContainer * ContainerWithoutAttrsGrammarAction(tExprs * exprs){
	tContainer * container = malloc(sizeof(container));
	if(container == NULL){
		return NULL;
	}
	container->attrs = NULL;
	container->content = exprs;
	container->size = 1; //????
	return container;
}