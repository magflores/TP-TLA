#include "../support/logger.h"
#include "generator.h"

/**
 * Implementación de "generator.h".
 */

FILE *file;

void Generator(tProgram *result)
{
	LogInfo("El resultado de la expresion computada es: ");

	// Creando archivo
	file = fopen("webpage.html", "w+");

	if (result == NULL || result->initial == NULL)
	{
		LogInfo("El resultado de la compilacion es nulo.");
		return;
	}

	// Abriendo HTML tags
	fprintf(file, "<!DOCTYPE html>\n<html>\n\t<head>\n\t<meta charset=\"utf-8\">\n</head>\n<body>\n");

	WebPage(result->initial);

	// Cerrando HTML tags
	fprintf(file, "</body>\n</html>\n\n");

	// Cerrando archivo
	fclose(file);

	freeMemory(result->initial);

	return;
}

void WebPage(tExprs *expressions)
{
	tExpr *current = expressions->first;
	while (current != NULL)
	{
		addHTML(current);
		current = current->next;
	}
}

void addHTML(tExpr *result)
{

	tExpr *current = result;

	switch (current->type)
	{
	case TITLEEXPR:
		addTitle(current->expr);
		break;
	case TEXTEXPR:
		addText(current->expr);
		break;
	case LINKEXPR:
		addLink(current->expr);
		break;
	case IMGEXPR:
		addImage(current->expr);
		break;
	case TABLEEXPR:
		addTable(current->expr);
		break;
	case CONTAINEREXPR:
		addContainer(current->expr);
		break;
	case FONTEXPR:
		addFont(current->expr);
		break;
	default:
		fprintf(file, "\nNone matched\n");
		break;
	}
}

int getTitleSize(tAttributes *attrs)
{
	tAttribute *currAttr = attrs->first;
	while (currAttr->type != SIZEVALUE)
	{
		currAttr = currAttr->next;
	}
	if (strcmp(currAttr->value, "x-small"))
	{
		return 6;
	}
	if (strcmp(currAttr->value, "small"))
	{
		return 5;
	}
	if (strcmp(currAttr->value, "medium"))
	{
		return 4;
	}
	if (strcmp(currAttr->value, "large"))
	{
		return 3;
	}
	if (strcmp(currAttr->value, "x-large"))
	{
		return 2;
	}
	if (strcmp(currAttr->value, "xx-large"))
	{
		return 1;
	}
	return 3;
}

void addTitle(tTitle *title)
{
	int bold = 0, italic = 0, underlined = 0;
	int size = 3;

	if (title->attrs != NULL)
	{

		tAttribute *currAttr = title->attrs->first;
		size = getTitleSize(title->attrs);
		fprintf(file, "<h%d", size);

		while (currAttr != NULL)
		{
			switch (currAttr->type)
			{
			case IDVALUE:
				fprintf(file, " id=\"%s\"", currAttr->value);
				break;
			case COLORVALUE:
				fprintf(file, " color=%s", currAttr->value);
				break;
			case POSITIONVALUE:
				fprintf(file, " style=\"text-align:%s;\"", currAttr->value);
				break;
			case BOLDVALUE:
				bold = 1;
				break;
			case ITALICVALUE:
				italic = 1;
				break;
			case UNDERLINEDVALUE:
				underlined = 1;
				break;
			}
			currAttr = currAttr->next;
		}
	}
	else
	{
		fprintf(file, "<h%d", size);
	}

	fprintf(file, ">");
	if (bold == 1)
		fprintf(file, "<b>");
	if (italic == 1)
		fprintf(file, "<i>");
	if (underlined == 1)
		fprintf(file, "<u>");

	fprintf(file, "%s", title->content);

	if (underlined == 1)
		fprintf(file, "</u>");
	if (italic == 1)
		fprintf(file, "</i>");
	if (bold == 1)
		fprintf(file, "</b>");

	fprintf(file, "</h%d>\n", size);
}

int getFontSize(tAttributes *attrs)
{
	tAttribute *currAttr = attrs->first;
	while (currAttr->type != SIZEVALUE)
	{
		currAttr = currAttr->next;
	}
	if (strcmp(currAttr->value, "x-small"))
	{
		return 10;
	}
	if (strcmp(currAttr->value, "small"))
	{
		return 14;
	}
	if (strcmp(currAttr->value, "medium"))
	{
		return 25;
	}
	if (strcmp(currAttr->value, "large"))
	{
		return 40;
	}
	if (strcmp(currAttr->value, "x-large"))
	{
		return 50;
	}
	if (strcmp(currAttr->value, "xx-large"))
	{
		return 64;
	}
	return 25;
}

/*
	recorrer la lista de attrs buscando position o size
	una vez que se encuentra alguno de los dos
	abrir tag style e imprimir el contenido del encontrado
	y seguir recorriendo la lista hasta encontrar el que falta e imprimir el contenido
	Finalmente cerrar el tag style
*/
void addStyle(tAttributes * attrs) {
	tAttribute *currAttr = attrs->first;
	int size = getFontSize(attrs);

	while (currAttr != NULL)
	{ 
		if (currAttr->type != POSITIONVALUE || currAttr->type != SIZEVALUE) {
			currAttr = currAttr->next;
		}
		if (currAttr->type == POSITIONVALUE)
		{
			fprintf(file, " style=\"");
			fprintf(file, " text-align:%s;", currAttr->value);
			while(currAttr->type != SIZEVALUE) {
				currAttr = currAttr->next;
			}
			if (currAttr->type == SIZEVALUE)
			{
				fprintf(file, " font-size:%dpt;", size);
			}
			fprintf(file, " \"");
		}
		else if (currAttr->type == SIZEVALUE)
		{
			fprintf(file, " style=\"");
			fprintf(file, " font-size:%dpt;", size);
			while(currAttr->type != SIZEVALUE) {
				currAttr = currAttr->next;
			}
			if (currAttr->type == POSITIONVALUE)
			{
				fprintf(file, " text-align:%s;", currAttr->value);
			}
			fprintf(file, " \"");
		}
	}

}

void addText(tText *text)
{
	int bold = 0, italic = 0, underlined = 0;
	int style = 0;

	fprintf(file, "<p");

	if (text->attrs != NULL)
	{
		addStyle(text->attrs);
		tAttribute *current = text->attrs->first;

		while (current != NULL)
		{
			switch (current->type)
			{
			case IDVALUE:
				fprintf(file, " id=\"%s\"", current->value);
				break;
			case COLORVALUE:
				fprintf(file, " color=\"%s\"", current->value);
				break;
			case BOLDVALUE:
				bold = 1;
				break;
			case ITALICVALUE:
				italic = 1;
				break;
			case UNDERLINEDVALUE:
				underlined = 1;
				break;
			}
			current = current->next;
		}
	}

	fprintf(file, ">");
	if (bold == 1)
		fprintf(file, "<b>");
	if (italic == 1)
		fprintf(file, "<i>");
	if (underlined == 1)
		fprintf(file, "<u>");

	fprintf(file, "%s", text->content);

	if (underlined == 1)
		fprintf(file, "</u>");
	if (italic == 1)
		fprintf(file, "</i>");
	if (bold == 1)
		fprintf(file, "</b>");

	fprintf(file, "</p>\n");
}

void addLink(tLink *link)
{
	int bold = 0, italic = 0, underlined = 0;

	fprintf(file, "<a");
	fprintf(file, " href=\"%s\"", link->ref);

	if (link->attrs != NULL)
	{
		addStyle(link->attrs);
		tAttribute *current = link->attrs->first;
		
		while (current != NULL)
		{
			switch (current->type)
			{
			case COLORVALUE:
				fprintf(file, " color=%s", current->value);
				break;
			case BOLDVALUE:
				bold = 1;
				break;
			case ITALICVALUE:
				italic = 1;
				break;
			case UNDERLINEDVALUE:
				underlined = 1;
				break;
			}
			current = current->next;
		}
	}
	fprintf(file, ">");

	if (bold == 1)
		fprintf(file, "<b>");
	if (italic == 1)
		fprintf(file, "<i>");
	if (underlined == 1)
		fprintf(file, "<u>");

	fprintf(file, "%s", link->text);

	if (underlined == 1)
		fprintf(file, "</u>");
	if (italic == 1)
		fprintf(file, "</i>");
	if (bold == 1)
		fprintf(file, "</b>");

	fprintf(file, "</a>\n");
}

int getImgSize(tAttributes *attrs)
{
	tAttribute *currAttr = attrs->first;
	while (currAttr->type != SIZEVALUE)
	{
		currAttr = currAttr->next;
	}
	if (strcmp(currAttr->value, "x-small"))
	{
		return 100;
	}
	if (strcmp(currAttr->value, "small"))
	{
		return 200;
	}
	if (strcmp(currAttr->value, "medium"))
	{
		return 300;
	}
	if (strcmp(currAttr->value, "large"))
	{
		return 400;
	}
	if (strcmp(currAttr->value, "x-large"))
	{
		return 500;
	}
	if (strcmp(currAttr->value, "xx-large"))
	{
		return 600;
	}
	return 300;
}

void addImage(tImage *image)
{

	int size[2] = {300, 300};
	fprintf(file, "<img");

	if (image->attrs != NULL)
	{

		// TODO: REVISAR --> USAR SOLO WIDTH?
		size[0] = getImgSize(image->attrs);
		size[1] = size[0];

		tAttribute *current = image->attrs->first;

		while (current != NULL)
		{
			switch (current->type)
			{
			case IDVALUE:
				fprintf(file, " id=\"%s\"", current->value);
				break;
			case POSITIONVALUE:
				fprintf(file, " style=\"text-align:%s;\"", current->value);
				break;
			case SIZEVALUE:
				fprintf(file, " height=\"%d\" width=\"%d\"", size[0], size[1]);
				break;
			}
			current = current->next;
		}
	}

	fprintf(file, " src=%s", image->link);
	fprintf(file, " alt=%s", image->link);

	fprintf(file, "/>\n");
}

void addContainer(tContainer *container)
{
	fprintf(file, "<div");
	if (container->attrs != NULL)
	{

		tAttribute *current = container->attrs->first;

		while (current != NULL)
		{
			switch (current->type)
			{
			case IDVALUE:
				fprintf(file, " id=\"%s\"", current->value);
				break;
			case POSITIONVALUE:
				fprintf(file, " style=\"text-align:%s;\"", current->value);
				break;
			}
			current = current->next;
		}
	}
	fprintf(file, ">\n");
	WebPage(container->content); // LO DE ADENTRO EN COMO UNA PAGINA
	fprintf(file, "</div>\n");
}

void addRowContent(tExprs *rowContent, int cols)
{
	tExpr *auxExpr = rowContent->first;
	for (int col = 0; col < cols; col++)
	{
		if (auxExpr != NULL)
		{
			fprintf(file, "\n\t<td>");
			addHTML(auxExpr);
		}
		else
		{
			fprintf(file, "\n\t<td>");
		}
		fprintf(file, "</td>\n");
	}
	auxExpr = auxExpr->next;
}

void addTable(tTable *table)
{
	fprintf(file, "<table style=\"border:1px solid black;\"");
	fprintf(file, " id=\"%s\"", table->attrs->ID->value);
	fprintf(file, ">\n");
	tRow *auxRow = table->firstRow->firstRow;
	for (int row = 0; row < table->attrs->rowxcol->rows; row++)
	{
		fprintf(file, "<tr>");
		if (auxRow != NULL)
		{
			rowContent(auxRow->content, table->attrs->rowxcol->cols);
		}
		auxRow = auxRow->nextRow;
		fprintf(file, "</tr>\n");
	}
	fprintf(file, "</table>\n");
}

void addFont(tFont *font)
{
	if (font != NULL && font->content != NULL)
	{
		fprintf(file, "<style>\n");
		fprintf(file, "body { font-family: '%s'; }", font->content);
		fprintf(file, "</style>\n");
	}
}

//TODO: REVISAR LIBERACION DE MEMORIA

void freeMemory(tExpr * expr) {
	if(expr == NULL){
		printf("error");
		return;
	}
	else if(expr->next->next == NULL){
		freeExpression(expr->next);
		tExpr * prev = expr->next;
		expr->next = NULL;
		free(prev);
		return;
	}
	else{
		freeMemory(expr->next);
		freeExpression(expr->next);
		tExpr * prev = expr->next;
		expr->next = NULL;
		free(prev);
		return;
	}
}

void freeExpression(tExpr * expr) {
	switch(expr->type){
		case TITLEEXPR:
		{
			tTitle * aux = (tTitle *) expr->expr;
			free(aux->content);
			freeAttributes(aux->attrs);
			free(aux->attrs);
			free(aux);
			free(expr);
			return;
		}
		case IMGEXPR:
		{
			tImage * aux = (tImage *) expr->expr;
			free(aux->link);
			freeAttributes(aux->attrs);
			free(aux->attrs);
			free(aux);
			free(expr);
			return;
		}
		case LINKEXPR:
		{
			tLink * aux = (tLink *) expr->expr;
			free(aux->ref);
			free(aux->text);
			freeAttributes(aux->attrs);
			free(aux->attrs);
			free(aux);
			free(expr);
			return;
		}
		case TABLEEXPR:
		{
			tTable * aux = (tTable *) expr->expr;
			//TODO: FREE TABLE CONTENT
			free(aux);
			free(expr);
			return;
		}
		case CONTAINEREXPR:
		{
			tContainer * aux = (tContainer *) expr->expr;
			freeAttributes(aux->attrs);
			freeMemory(aux->content->first);
			free(aux->content);
			free(aux);
			free(expr);
			return;
		}
		case TEXTEXPR:
		{
			tText * aux = (tText *) expr->expr;
			freeAttributes(aux->attrs);
			free(aux->content);
			free(aux->attrs);
			free(aux);
			free(expr);
			return;
		}
		case FONTEXPR:
			tFont * aux = (tFont *) expr->expr;
			free(aux);
			free(expr);	
			return;
		default:
			free(expr);
			break;
	}
}

void freeAttributes(tAttribute * attrs) {
	if(attrs == NULL) {
		return;
	}
	else if(attrs->next->next == NULL){
		free(attrs->next->value);
		tAttribute * prev = attrs->next;
		attrs->next = NULL;
		free(prev);
		return;
	}
	else{
		freeAttributes(attrs->next);
		free(attrs->next->value);
		tAttribute * prev = attrs->next;
		attrs->next = NULL;
		free(prev);
		return;
	}
}
