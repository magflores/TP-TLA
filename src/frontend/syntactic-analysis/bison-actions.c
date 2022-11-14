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
tProgram ProgramGrammarAction(tExprs * exprs) {
	LogDebug("Reconozco patrón. ProgramGrammarAction()");
	tProgram * value = malloc(sizeof(tProgram));
	if(value == NULL)
		/* FIXME: QUE DEVOLVEMOS SI NO PUEDE SER VOID?? */
		return NULL;
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

	/* FIXME: QUE DEVOLVEMOS SI NO PUEDE SER VOID?? */
	return value;
}

tExprs * ExprAction(tExpr * exp){
	LogDebug("ExprAction()");
	tExprs * exps = malloc(sizeof(tExprs));
	if(exps == NULL)
		return NULL;
	exp->next = NULL;
	exps->first = exp;
	exps->size = 1;
	return exps;
}

tExprs * ExprsAction(tExpr * exp, tExprs * exps){
	LogDebug("ExprsAction()");
	tExpr * aux = exps->first;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = exp;
	exps->size++;
	return exps;
}

tProgram EmptyExprAction(){
	LogDebug("EmptyExprAction()");

	/* FIXME: QUE DEVOLVEMOS SI NO PUEDE SER VOID?? */	
	return NULL;
}

tExpr * TitleExprAction(tTitle * title){
	LogDebug("TitleExprAction()");
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = TITLEEXPR;
	exp->expr = title;
	exp->next = NULL;
	return exp;
}

tExpr *  FontExprAction(tFont * font) {
	LogDebug("FontExprAction()");
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = FONTEXPR;
	exp->expr = font;
	exp->next = NULL;
	return exp;
}

tExpr * TextExprAction(tText * text){
	LogDebug("TextExprAction()");
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = TEXTEXPR;
	exp->expr = text;
	exp->next = NULL;
	return exp;
}

tExpr * ImgExprAction(tImage * img){
	LogDebug("ImgExprAction()");
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = IMGEXPR;
	exp->expr = img;
	exp->next = NULL;
	return exp;
}

tExpr * LinkExprAction(tLink * link){
	LogDebug("LinkExprAction()");
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = LINKEXPR;
	exp->expr = link;
	exp->next = NULL;
	return exp;
}

tExpr * TableExprAction(tTable * table){
	LogDebug("TableExprAction()");
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = TABLEEXPR;
	exp->expr = table;
	exp->next = NULL;
	return exp;
}

tExpr * ContainerExprAction(tContainer * div){
	LogDebug("ContainerExprAction()");
	tExpr * exp = malloc(sizeof(tExpr));
	if(exp == NULL)
		return NULL;
	exp->type = CONTAINEREXPR;
	exp->expr = div;
	exp->next = NULL;
	return exp;
}

tTitle * TitleWithoutAttrsGrammarAction(char * content){
	LogDebug("TitleWithoutAttrsGrammarAction()");
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
	LogDebug("TitleWithAttrsGrammarAction()");
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
	LogDebug("FontGrammarAction()");
	tFont * font = malloc(sizeof(tFont));
	if(font == NULL){
		return NULL;
	}
	font->content = malloc(sizeof(char) * (strlen(content) + 1));
	strcpy(font->content, content);
	return font;
}

tText * TextWithoutAttrsGrammarAction(char * content){
	LogDebug("TextWithoutAttrsGrammarAction()");
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
	LogDebug("TextWithAttrsGrammarAction()");
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
	LogDebug("ImgWithAttrsGrammarAction()");
	tImage * img = malloc(sizeof(tImage));
	if(img == NULL)
		return NULL; 
	img->link = malloc(sizeof(char) * (strlen(link) + 1));
	strcpy(img->link, link);
	img->attrs = attrs;
	return img;
}

tImage * ImgWithoutAttrsGrammarAction(char * link){
	LogDebug("ImgWithoutAttrsGrammarAction()");
	tImage * img = malloc(sizeof(tImage));
	if(img == NULL)
		return NULL;
	img->link = malloc(sizeof(char) * (strlen(link) + 1));
	strcpy(img->link, link);
	img->attrs = NULL;
	return img;
}

tLink * LinkWithAttrsGrammarAction(tAttributes * attrs, char * ref, char * text){
	LogDebug("LinkWithAttrsGrammarAction()");
	tLink * link = malloc(sizeof(tLink));
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
	LogDebug("LinkWithoutAttrsGrammarAction()");
	tLink * link = malloc(sizeof(tLink));
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
	LogDebug("TableGrammarAction()");
	tTable * table = malloc(sizeof(tTable));
	if(table == NULL){
		return NULL;
	}
	table->attrs = attrs;
	table->firstRow = rows;
	return table;
}

tContainer * ContainerWithAttrsGrammarAction(tAttributes * attrs, tExprs * exprs){
	LogDebug("ContainerWithAttrsGrammarAction()");
	tContainer * container = malloc(sizeof(tContainer));
	if(container == NULL){
		return NULL;
	}
	container->attrs = attrs;
	container->content = exprs;
	container->size++; //????
	return container;
}

tContainer * ContainerWithoutAttrsGrammarAction(tExprs * exprs){
	LogDebug("ContainerWithoutAttrsGrammarAction()");
	tContainer * container = malloc(sizeof(tContainer));
	if(container == NULL){
		return NULL;
	}
	container->attrs = NULL;
	container->content = exprs;
	container->size++; //????
	return container;
}

tAttributes * AttrAction(tAttributes * attr){
	LogDebug("AttrAction()");
	tAttributes * aux = malloc(sizeof(tAttributes));
	if(aux == NULL){
		return NULL;
	}
	aux->first = attr->first;
	aux->size++;
	return aux;
}

tAttributes * AttrsAction(tAttributes * attr, tAttributes * attrs){
	LogDebug("AttrsAction()");
	tAttribute * aux = attrs->first;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = attr->first;
	attrs->size++;
	return attrs;
}

tAttributes * IdAttrPatternAction(tAttribute * id){
	LogDebug("IdAttrPatternAction()");
	tAttribute * AttrAux = malloc(sizeof(tAttribute));
	tAttributes * AttrsAux = malloc(sizeof(tAttributes));
	if(AttrAux == NULL || AttrsAux == NULL){
		return NULL;
	}
	AttrAux->type = id->type;
	AttrAux->next = id->next;
	AttrAux->value = id->value;
	AttrsAux->first = AttrAux;
	AttrsAux->size++;
	return AttrsAux;
}

tAttributes * SizeAttrPatternAction(tAttribute * size){
	LogDebug("SizeAttrPatternAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	tAttributes * AttrsAux = malloc(sizeof(tAttributes));
	if(aux == NULL || AttrsAux == NULL){
		return NULL;
	}
	aux->type = size->type;
	aux->next = size->next;
	aux->value = size->value;
	AttrsAux->first = aux;
	AttrsAux->size++;
	return AttrsAux;
}

tAttributes * ColorAttrPatternAction(tAttribute * color){
	LogDebug("ColorAttrPatternAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	tAttributes * AttrsAux = malloc(sizeof(tAttributes));
	if(aux == NULL || AttrsAux == NULL){
		return NULL;
	}
	aux->type = color->type;
	aux->next = color->next;
	aux->value = color->value;
	AttrsAux->first = aux;
	AttrsAux->size++;
	return AttrsAux;
}

tAttributes * PositionAttrPatternAction(tAttribute * position){
	LogDebug("PositionAttrPatternAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	tAttributes * AttrsAux = malloc(sizeof(tAttributes));
	if(aux == NULL || AttrsAux == NULL){
		return NULL;
	}
	aux->type = position->type;
	aux->next = position->next;
	aux->value = position->value;
	AttrsAux->first = aux;
	AttrsAux->size++;
	return AttrsAux;
}

tAttributes * StyleAttrPatternAction(tAttributes * style){
	LogDebug("StyleAttrPatternAction()");
	tAttributes * aux = malloc(sizeof(tAttributes));
	if(aux == NULL){
		return NULL;
	}
	aux->first = style->first;
	aux->size = style->size;
	return aux;
}

tAttributes * PropertiesAttrPaternAction(tAttributes * properties){
	LogDebug("PropertiesAttrPaternAction()");
	tAttributes * aux = malloc(sizeof(tAttributes));
	if(aux == NULL){
		return NULL;
	}
	aux->first = properties->first;
	aux->size = properties->size;
	return aux;
}

tAttributes * PropertiesListAction(tAttribute * property, tAttributes * properties){
	LogDebug("PropertiesListAction()");
	tAttribute * aux = properties->first;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = property;
	properties->size++;
	return properties;
}

tAttributes * PropertyAttrAction(tAttribute * property){
	LogDebug("PropertyAttrAction()");
	tAttributes * aux = malloc(sizeof(tAttributes));
	if(aux == NULL){
		return NULL;
	}
	aux->first = property;
	aux->size++;
	return aux;
}

tAttribute * IdAttrAction(char * ID){
	LogDebug("IdAttrAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	if(aux == NULL){
		return NULL;
	}
	aux->value = malloc(sizeof(char) * (strlen(ID) - 3));
	strncpy(aux->value, ID + 4, strlen(ID) - 5);
	aux->type = IDVALUE;
	aux->next = NULL;
	return aux;
}

tAttribute * SizeAttrAction(char * Size){
	LogDebug("SizeAttrAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	if(aux == NULL){
		return NULL;
	}
	aux->value = malloc(sizeof(char) * (strlen(Size) - 3));
	strncpy(aux->value, Size + 4, strlen(Size) - 5);
	aux->type = SIZEVALUE;
	aux->next = NULL;
	return aux;
}

tAttribute * ColorAttrAction(char * Color){
	LogDebug("ColorAttrAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	if(aux == NULL){
		return NULL;
	}
	aux->value = malloc(sizeof(char) * (strlen(Color) - 3));
	strncpy(aux->value, Color + 4, strlen(Color) - 5);
	aux->type = COLORVALUE;
	aux->next = NULL;
	return aux;
}

tAttribute * PositionAttrAction(char * Position){
	LogDebug("PositionAttrAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	if(aux == NULL){
		return NULL;
	}
	aux->value = malloc(sizeof(char) * (strlen(Position) - 3));
	strncpy(aux->value, Position + 4, strlen(Position) - 5);
	aux->type = POSITIONVALUE;
	aux->next = NULL;
	return aux;
}

tAttribute * BoldAttrAction(char * Bold){
	LogDebug("BoldAttrAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	if(aux == NULL){
		return NULL;
	}
	aux->value = malloc(sizeof(char) * (strlen(Bold) - 3));
	strncpy(aux->value, Bold + 4, strlen(Bold) - 5);
	aux->type = BOLDVALUE;
	aux->next = NULL;
	return aux;
}

tAttribute * UnderlinedAttrAction(char * Underlined){
	LogDebug("UnderlinedAttrAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	if(aux == NULL){
		return NULL;
	}
	aux->value = malloc(sizeof(char) * (strlen(Underlined) - 3));
	strncpy(aux->value, Underlined + 4, strlen(Underlined) - 5);
	aux->type = UNDERLINEDVALUE;
	aux->next = NULL;
	return aux;
}

tAttribute * ItalicsAttrAction(char * Italics){
	LogDebug("ItalicsAttrAction()");
	tAttribute * aux = malloc(sizeof(tAttribute));
	if(aux == NULL){
		return NULL;
	}
	aux->value = malloc(sizeof(char) * (strlen(Italics) - 3));
	strncpy(aux->value, Italics + 4, strlen(Italics) - 5);
	aux->type = ITALICVALUE;
	aux->next = NULL;
	return aux;
}

tTableAttrs * IdAndRowxColAttrPaternAction(tAttribute * id, tRowxColAttr * rowxcol){
	LogDebug("IdAndRowxColAttrPaternAction()");
	tTableAttrs * aux = malloc(sizeof(tTableAttrs));
	if(aux == NULL){
		return NULL;
	}
	aux->ID = id;
	aux->rowxcol = rowxcol;
	return aux;
}

tTableAttrs * RowxColAttrPatternAction(tRowxColAttr * rowxcol){
	LogDebug("RowxColAttrPatternAction()");
	tTableAttrs * aux = malloc(sizeof(tTableAttrs));
	if(aux == NULL){
		return NULL;
	}
	aux->ID = NULL;
	aux->rowxcol = rowxcol;
	return aux;
}

tRowxColAttr * RowxColAttrAction(int cols, int rows){
	LogDebug("RowxColAttrAction()");
	tRowxColAttr * aux = malloc(sizeof(tRowxColAttr));
	if(aux == NULL){
		return NULL;
	}
	aux->cols = cols;
	aux->rows = rows;
	return aux;
}

tRows * TableAndRowContentAction(tRow * row_content, tRows * table_content){
	LogDebug("TableAndRowContentAction()");
	tRow * aux = table_content->firstRow;
	while(aux->nextRow != NULL)
		aux = aux->nextRow;
	aux->nextRow = row_content;
	table_content->size++;
	return table_content;
}

tRows * RowContentAction(tRow * row_content){
	LogDebug("RowContentAction()");
	tRows * aux = malloc(sizeof(tRows));
	if(aux == NULL){
		return NULL;
	}
	aux->firstRow = row_content;
	aux->size++;
	return aux;
}

tRow * RowExpressionsAction(tExprs * content){
	LogDebug("RowExpressionsAction()");
	tRow * aux = malloc(sizeof(tRow));
	if(aux == NULL){
		return NULL;
	}
	aux->size = 1;
	aux->nextRow = NULL;
	aux->content = content;
	return aux;
}