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
		return NULL;
	}

	// Abriendo HTML tags
	fprintf(file, "<!DOCTYPE html>\n<html>\n\t<head>\n\t<meta charset=\"utf-8\">\n</head>\n<body>\n");

	WebPage(result->initial);

	// Cerrando HTML tags
	fprintf(file, "</body>\n</html>\n\n");

	// Cerrando archivo
	fclose(file);
	return NULL;
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
		return 20;
	}
	if (strcmp(currAttr->value, "medium"))
	{
		return 30;
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
		return 60;
	}
	return 30;
}

void addText(tText *text)
{
	int bold = 0, italic = 0, underlined = 0;

	// TODO: COMO MANEJAR EL SIZE --> TENEMOS QUE MAPEAR NUESTRAS PALABRAS RESERVADAS A UN NUMERO NUMERO DE FONT --> ENUM??

	fprintf(file, "<p");

	int size = 30;

	if (text->attrs != NULL)
	{

		tAttribute *current = text->attrs->first;
		size = getFontSize(text->attrs);

		// TODO: NO ESTA BIEN PERO PUEDE SER POR ACA Y SINO ES CON UN ARCHIVO CSS
		if (current != NULL)
		{
			if (current->type == POSITIONVALUE || current->type == SIZEVALUE)
			{
				fprintf(file, " style=\"");
				if (current->type == POSITIONVALUE)
				{
					fprintf(file, " text-align:%s;", current->value);
				}
				if (current->type == SIZEVALUE)
				{
					fprintf(file, " font-size:%spx;", size);
				}
				fprintf(file, " \"");
			}
		}

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
			// case POSITIONVALUE:
			// 	fprintf(file, " style=\"text-align:%s;\"", current->value);
			// 	break;
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

	// TODO: COMO MANEJAR EL SIZE --> TENEMOS QUE MAPEAR NUESTRAS PALABRAS RESERVADAS A UN NUMERO NUMERO DE FONT --> ENUM??

	fprintf(file, "<a");
	fprintf(file, " href=\"%s\"", link->ref);

	if (link->attrs != NULL)
	{
		tAttribute *current = link->attrs->first;
		while (current != NULL)
		{
			switch (current->type)
			{
			case COLORVALUE:
				fprintf(file, " color=%s", current->value);
				break;
			case POSITIONVALUE:
				fprintf(file, " style=\"text-align:%s;\"", current->value);
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

		// TODO: REVISAR
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
	fprintf(file, " alt=%s", "IMAGEN");

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
			for (int col = 0; col < table->attrs->rowxcol->cols; col++)
			{
				if (auxRow->content != NULL)
				{
					fprintf(file, "\n\t<td>");
					WebPage(auxRow->content);
				}else {
					fprintf(file, "\n\t<td>");
				}
				fprintf(file, "</td>\n");
			}
			auxRow = auxRow->nextRow;
		}
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

// TODO: TENEMOS QUE LIBERAR LA MEMORIA QUE ALOCAMOS