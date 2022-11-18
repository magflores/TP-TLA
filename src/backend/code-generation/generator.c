#include "../support/logger.h"
#include "generator.h"

/**
 * Implementación de "generator.h".
 */

FILE *file;

void Generator(tProgram *result)
{
	LogInfo("El resultado de la expresion computada es: ");
	
	const char * file_name = strcat(state.output, ".html");

	// Creando archivo
	file = fopen(file_name, "w+");	

	if (result == NULL )
	{
		LogInfo("El resultado de la compilacion es nulo.");
		return;
	}

	if (result->initial == NULL)
	{
		fprintf(file, "<!DOCTYPE html>\n<html>\n\t<head>\n\t<meta charset=\"utf-8\">\n</head>\n<body>\n</body>\n</html>\n\n");
		fclose(file);
		//free(result);
		return;
	}

	// Abriendo HTML tags
	fprintf(file, "<!DOCTYPE html>\n<html>\n\t<head>\n\t<meta charset=\"utf-8\">\n</head>\n<body>\n");

	WebPage(result->initial);

	// Cerrando HTML tags
	fprintf(file, "</body>\n</html>\n\n");

	// Cerrando archivo
	fclose(file);

	// freeMemory(result->initial->first);
	// freeExpression(result->initial->first);
	// free(result->initial);
	// free(result);

	return;
}

void WebPage(tExprs *expressions)
{
	LogDebug("WebPage()");
	tExpr *current = expressions->first;
	while (current != NULL)
	{
		addHTML(current);
		current = current->next;
	}
}

void addHTML(tExpr *result)
{
	LogDebug("AddHtml()");
	tExpr *current = result;

	switch (current->type)
	{
	case TITLEEXPR:
		addTitle((tTitle *)current->expr);
		break;
	case TEXTEXPR:
		addText((tText *)current->expr);
		break;
	case LINKEXPR:
		addLink((tLink *)current->expr);
		break;
	case IMGEXPR:
		addImage((tImage *)current->expr);
		break;
	case TABLEEXPR:
		addTable((tTable *)current->expr);
		break;
	case CONTAINEREXPR:
		addContainer((tContainer *)current->expr);
		break;
	case FONTEXPR:
		addFont((tFont *)current->expr);
		break;
	default:
		fprintf(file, "\nNone matched\n");
		break;
	}
}

int getTitleSize(tAttributes * attrs)
{
	LogDebug("getTitleSize()");
	tAttribute *currAttr = attrs->first;
	while (currAttr != NULL && currAttr->type != SIZEVALUE)
	{
		currAttr = currAttr->next;
	}
	if (currAttr != NULL)
	{
		if (strcmp(currAttr->value, "x-small") == 0)
		{
			return 6;
		}
		if (strcmp(currAttr->value, "small") == 0)
		{
			return 5;
		}
		if (strcmp(currAttr->value, "medium") == 0)
		{
			return 4;
		}
		if (strcmp(currAttr->value, "large") == 0)
		{
			return 3;
		}
		if (strcmp(currAttr->value, "x-large") == 0)
		{
			return 2;
		}
		if (strcmp(currAttr->value, "xx-large") == 0)
		{
			return 1;
		}
	}
	return 3;
}

/*
	recorrer la lista de attrs buscando position o color
	una vez que se encuentra alguno de los dos
	abrir tag style e imprimir el contenido del encontrado
	y seguir recorriendo la lista hasta encontrar el que falta e imprimir el contenido
	Finalmente cerrar el tag style
*/
void addTitleStyle(tAttributes * attrs) {

	LogDebug("addTitleStyle()");

	tAttribute *currAttr = attrs->first;

	while (currAttr != NULL && (currAttr->type != POSITIONVALUE || currAttr->type != COLORVALUE)) 
	{
		if (currAttr->type == POSITIONVALUE)
		{
			fprintf(file, " style=\"");
			fprintf(file, "text-align:%s;", currAttr->value);
			while(currAttr != NULL && currAttr->type != COLORVALUE) {
				currAttr = currAttr->next;
			}
			if (currAttr != NULL && currAttr->type == COLORVALUE)
			{
				fprintf(file, " color:%s;", currAttr->value);
			}
			fprintf(file, "\"");
		}
		else if (currAttr->type == COLORVALUE)
		{
			fprintf(file, " style=\"");
			fprintf(file, "color:%s;", currAttr->value);
			while(currAttr != NULL && currAttr->type != POSITIONVALUE) {
				currAttr = currAttr->next;
			}
			if (currAttr != NULL && currAttr->type == POSITIONVALUE)
			{
				fprintf(file, " text-align:%s;", currAttr->value);
			}
			fprintf(file, "\"");
		}
		if(currAttr != NULL){
			currAttr = currAttr->next;
		}
	}
}

void addTitle(tTitle *title)
{
	LogDebug("AddTitle()");
	int bold = 0, italic = 0, underlined = 0;
	int size = 3;

	if (title->attrs != NULL)
	{
		size = getTitleSize(title->attrs);


		tAttribute *currAttr = title->attrs->first;

		fprintf(file, "<h%d", size);
		
		addTitleStyle(title->attrs);


		while (currAttr != NULL)
		{
			switch (currAttr->type)
			{
			case IDVALUE:
				fprintf(file, " id=\"%s\"", currAttr->value);
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

int getFontSize(char * value)
{
	if (strcmp(value, "x-small") == 0)
	{
		return 10;
	}
	if (strcmp(value, "small") == 0)
	{
		return 14;
	}
	if (strcmp(value, "medium") == 0)
	{
		return 25;
	}
	if (strcmp(value, "large") == 0)
	{
		return 40;
	}
	if (strcmp(value, "x-large") == 0)
	{
		return 50;
	}
	if (strcmp(value, "xx-large") == 0)
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

void addTextStyle(tAttributes * attrs) {

	tAttribute *currAttr = attrs->first;

	while (currAttr != NULL && (currAttr->type != POSITIONVALUE || currAttr->type != SIZEVALUE || currAttr->type != COLORVALUE)) 
	{
		if (currAttr->type == POSITIONVALUE)
		{
			fprintf(file, " style=\"");
			fprintf(file, "text-align:%s;", currAttr->value);
			while(currAttr != NULL && (currAttr->type != SIZEVALUE || currAttr->type != COLORVALUE)) {
				if (currAttr->type == SIZEVALUE) {
					int size = getFontSize(currAttr->value);
					fprintf(file, " font-size:%dpt;", size);
					while(currAttr != NULL && currAttr->type != COLORVALUE) {
						currAttr = currAttr->next;
					}
					if (currAttr != NULL && currAttr->type == COLORVALUE)
					{
						fprintf(file, " color:%s;", currAttr->value);
					}
				}
				else if (currAttr->type == COLORVALUE) {
					fprintf(file, " color:%s;", currAttr->value);
					while(currAttr != NULL && currAttr->type != SIZEVALUE) {
						currAttr = currAttr->next;
					}
					if (currAttr != NULL && currAttr->type == SIZEVALUE)
					{
						int size = getFontSize(currAttr->value);
						fprintf(file, " font-size:%dpt;", size);
					}
				}
				if(currAttr != NULL){
					currAttr = currAttr->next;
				}
			}
			fprintf(file, "\"");
		}
		else if (currAttr->type == SIZEVALUE)
		{
			fprintf(file, " style=\"");
			int size = getFontSize(currAttr->value);
			fprintf(file, "font-size:%dpt;", size);
			while(currAttr != NULL && (currAttr->type != POSITIONVALUE || currAttr->type != COLORVALUE)) {
				if (currAttr->type == POSITIONVALUE) {
					fprintf(file, " text-align:%s;", currAttr->value);
					while(currAttr != NULL && currAttr->type != COLORVALUE) {
						currAttr = currAttr->next;
					}
					if (currAttr != NULL && currAttr->type == COLORVALUE)
					{
						fprintf(file, " color:%s;", currAttr->value);
					}
				}
				else if (currAttr->type == COLORVALUE) {
					fprintf(file, " color:%s;", currAttr->value);
					while(currAttr != NULL && currAttr->type != POSITIONVALUE) {
						currAttr = currAttr->next;
					}
					if (currAttr != NULL && currAttr->type == POSITIONVALUE)
					{
						fprintf(file, " text-align:%s;", currAttr->value);
					}
				}
				if(currAttr != NULL){
					currAttr = currAttr->next;
				}
			}
			fprintf(file, "\"");
		}
		else if (currAttr->type == COLORVALUE)
		{
			fprintf(file, " style=\"");
			fprintf(file, "color:%s;", currAttr->value);
			while(currAttr != NULL && (currAttr->type != POSITIONVALUE || currAttr->type != SIZEVALUE)) {
				if (currAttr->type == POSITIONVALUE) {
					fprintf(file, " text-align:%s;", currAttr->value);
					while(currAttr != NULL && currAttr->type != SIZEVALUE) {
						currAttr = currAttr->next;
					}
					if (currAttr != NULL && currAttr->type == SIZEVALUE)
					{
						int size = getFontSize(currAttr->value);
						fprintf(file, " font-size:%dpt;", size);
					}
				}
				else if (currAttr->type == SIZEVALUE) {
					int size = getFontSize(currAttr->value);
					fprintf(file, " font-size:%dpt;", size);
					while(currAttr != NULL && currAttr->type != POSITIONVALUE) {
						currAttr = currAttr->next;
					}
					if (currAttr != NULL && currAttr->type == POSITIONVALUE)
					{
						fprintf(file, " text-align:%s;", currAttr->value);
					}
				}
				if(currAttr != NULL){
					currAttr = currAttr->next;
				}
			}
			fprintf(file, "\"");
		}
		if(currAttr != NULL){
			currAttr = currAttr->next;
		}
	}
}

void addText(tText *text)
{
	LogDebug("addText()");
	int bold = 0, italic = 0, underlined = 0;

	fprintf(file, "<p");

	if (text->attrs != NULL)
	{
		addTextStyle(text->attrs);

		tAttribute *current = text->attrs->first;

		while (current != NULL)
		{
			switch (current->type)
			{
			case IDVALUE:
				fprintf(file, " id=\"%s\"", current->value);
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

		tAttribute *current = link->attrs->first;
		
		while (current != NULL)
		{
			switch (current->type)
			{
			case SIZEVALUE:
				int size = getFontSize(current->value);
				fprintf(file, " style=\"font-size:%dpt;\"", size);
				break;
			case BOLDVALUE:
				bold = 1;
				break;
			case ITALICVALUE:
				italic = 1;
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

	fprintf(file, "%s", link->text);

	if (italic == 1)
		fprintf(file, "</i>");
	if (bold == 1)
		fprintf(file, "</b>");

	fprintf(file, "</a>\n");
}

int getImgSize(char * value)
{
	if (strcmp(value, "x-small") == 0)
	{
		return 100;
	}
	if (strcmp(value, "small") == 0)
	{
		return 200;
	}
	if (strcmp(value, "medium") == 0)
	{
		return 300;
	}
	if (strcmp(value, "large") == 0)
	{
		return 400;
	}
	if (strcmp(value, "x-large") == 0)
	{
		return 500;
	}
	if (strcmp(value, "xx-large") == 0)
	{
		return 600;
	}
	return 300;
}

void addImage(tImage *image)
{

	fprintf(file, "<img");

	if (image->attrs != NULL)
	{

		tAttribute *current = image->attrs->first;

		while (current != NULL)
		{
			switch (current->type)
			{
			case IDVALUE:
				fprintf(file, " id=\"%s\"", current->value);
				break;
			case SIZEVALUE:
				int size = getImgSize(current->value);
				fprintf(file, " height=\"%d\"", size);
				break;
			}
			current = current->next;
		}
	}

	fprintf(file, " src=\"%s\"", image->link);
	fprintf(file, " alt=\"%s\"", image->link);

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
	WebPage(container->content); // LO DE ADENTRO ES COMO UNA PAGINA
	fprintf(file, "</div>\n");
}

void addRowContent(tExprs *rowContent, int cols)
{
	tExpr *auxExpr = rowContent->first;
	tText * aux1 = (tText *)auxExpr->expr;
	LogDebug("NEXT CONTENT1: %s", aux1->content);
	for (int col = 0; col < cols; col++)
	{
		if (auxExpr != NULL)
		{
			fprintf(file, "\n\t<td>");
			addHTML(auxExpr);
			auxExpr = auxExpr->next;
		}
		else
		{
			fprintf(file, "\n\t<td>");
		}
		fprintf(file, "</td>\n");
	}
}

void addTable(tTable *table)
{
	fprintf(file, "<table style=\"border:1px solid black;\"");
	if(table->attrs->ID != NULL){
		fprintf(file, " id=\"%s\"", table->attrs->ID->value);
	}
	fprintf(file, ">\n");
	tRow *auxRow = table->firstRow->firstRow;
	for (int row = 0; row < table->attrs->rowxcol->rows; row++)
	{
		fprintf(file, "<tr>");
		if (auxRow != NULL)
		{
			addRowContent(auxRow->content, table->attrs->rowxcol->cols);
		}
		auxRow = auxRow->nextRow;
		fprintf(file, "</tr>\n");
	}
	fprintf(file, "</table>\n");
}

void addFont(tFont * font)
{
	if (font != NULL && font->content != NULL)
	{
		fprintf(file, "<style>\n");
		fprintf(file, "body { font-family: '%s'; }", font->content);
		fprintf(file, "</style>\n");
	}
}


void freeMemory(tExpr * expr) {
	if(expr == NULL){
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

void freeExpression(tExpr * expression) {
	switch(expression->type){
		case TITLEEXPR:
		{
			tTitle * aux = (tTitle *) expression->expr;
			free(aux->content);
			freeAttributes(aux->attrs->first);
			free(aux->attrs);
			free(aux);
			free(expression);
			return;
		}
		case IMGEXPR:
		{
			tImage * aux = (tImage *) expression->expr;
			free(aux->link);
			freeAttributes(aux->attrs->first);
			free(aux->attrs);
			free(aux);
			free(expression);
			return;
		}
		case LINKEXPR:
		{
			tLink * aux = (tLink *) expression->expr;
			free(aux->ref);
			free(aux->text);
			freeAttributes(aux->attrs->first);
			free(aux->attrs);
			free(aux);
			free(expression);
			return;
		}
		case TABLEEXPR:
		{
			tTable * aux = (tTable *) expression->expr;
			freeAttributes(aux->attrs->ID); 
			free(aux->attrs->rowxcol);
			free(aux->attrs);

			freeRows(aux->firstRow->firstRow);
			free(aux->firstRow);
			free(aux);
			free(expression);
			return;
		}
		case CONTAINEREXPR:
		{
			tContainer * aux = (tContainer *) expression->expr;
			freeAttributes(aux->attrs->first);
			freeExpression(aux->content->first);
			free(aux->content);
			free(aux);
			free(expression);
			return;
		}
		case TEXTEXPR:
		{
			tText * aux = (tText *) expression->expr;
			freeAttributes(aux->attrs->first);
			free(aux->content);
			free(aux->attrs);
			free(aux);
			free(expression);
			return;
		}
		case FONTEXPR:
			tFont * aux = (tFont *) expression->expr;
			free(aux->content);
			free(aux);
			free(expression);	
			return;
		default:
			free(expression);
			break;
	}
}

void freeAttributes(tAttribute * attr) {
	if(attr == NULL) {
		return;
	}
	else if(attr->next->next == NULL){
		free(attr->next->value);
		tAttribute * prev = attr->next;
		attr->next = NULL;
		free(prev);
		return;
	}
	else{
		freeAttributes(attr->next);
		free(attr->next->value);
		tAttribute * prev = attr->next;
		attr->next = NULL;
		free(prev);
		return;
	}
}

void freeRows(tRow * row) { 
	if(row == NULL){
		return;
	}
	else if (row->nextRow->nextRow == NULL)
	{
		freeExpression(row->nextRow->content->first);
		free(row->nextRow->content);
		tRow * aux = row->nextRow;
		row->content = NULL;
		free(aux);
		return;
	} else {
		freeRows(row->nextRow);
		freeExpression(row->nextRow->content->first);
		free(row->nextRow->content);
		tRow * aux = row->nextRow;
		row->content = NULL;
		free(aux);
		return;
	}
	
}