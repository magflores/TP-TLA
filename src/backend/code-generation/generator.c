#include "../support/logger.h"
#include "generator.h"

/**
 * Implementación de "generator.h".
 */

void Generator(tProgram * result) {
	LogInfo("El resultado de la expresion computada es: ");

	//Creando archivo
	file = fopen("webpage.html", "w+");

	if (result == NULL || result->initial == NULL){
		LogInfo("El resultado de la compilacion es nulo.");
		return NULL;
	}

	//Abriendo HTML tags
	fprintf(file, "<!DOCTYPE html>\n<html>\n\t<head>\n\t<meta charset=\"utf-8\">\n</head>\n<body>\n");

	WebPage(result->initial);

	//Cerrando HTML tags
	fprintf(file, "</body>\n</html>\n\n");

	//Cerrando archivo
	fclose(file);
	return NULL;
}

void WebPage(tExprs * expressions) {
	tExpr * current = expressions->first;
	while (current != NULL){
		addHTML(current);
		current = current->next;
	}
}

void addHTML(tExpr * result) {

	tExpr * current = result;

	switch (current->type) {
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

//TODO: MODULARIZAR??

void addTitle(tTitle * title) {
	int bold = 0, italic = 0, underlined = 0;

	int size = 6;

	//TODO: COMO MANEJAR EL SIZE --> TENEMOS QUE MAPEAR NUESTRAS PALABRAS RESERVADAS A UN NUMERO DE HTML (1-6) --> ENUM??
	//TODO: REVISAR BIEN QUE NUESTRAS PARALABRAS RESERVADAS COINCIDAN PARA HTML

	fprintf(file, "<h%d", size);

	if (title->attrs != NULL) {

		if (title->attrs->IDVALUE != NULL)
			fprintf(file, " id=\"%s\"", title->attrs->IDVALUE);
		
		tAttribute * currAttr = title->attrs->first;
		while (currAttr != NULL){
			switch (currAttr->type){
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

void addText(tText * text){
	int bold = 0, italic = 0, underlined = 0;

	//TODO: COMO MANEJAR EL SIZE --> TENEMOS QUE MAPEAR NUESTRAS PALABRAS RESERVADAS A UN NUMERO NUMERO DE FONT --> ENUM??
	//TODO: REVISAR BIEN QUE NUESTRAS PARALABRAS RESERVADAS COINCIDAN PARA HTML

	fprintf(file, "<p");

	if(text->attrs != NULL) {
		if (text->attrs->IDVALUE != NULL)
			fprintf(file, " id=\"%s\"", title->attrs->IDVALUE);

		tAttribute * current= text->attrs->first;
		while(current != NULL){
			switch (current->type){
				case COLORVALUE:
					fprintf(file, " color=\"%s\"", current->value);
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
	
	fprintf(file, "%s", text->content);
	
	if (underlined == 1)
		fprintf(file, "</u>");
	if (italic == 1)
		fprintf(file, "</i>");
	if (bold == 1)
		fprintf(file, "</b>");
	

	fprintf(file, "</p>\n");
}

void addLink(tLink * link) {
	int bold = 0, italic = 0, underlined = 0;

	//TODO: COMO MANEJAR EL SIZE --> TENEMOS QUE MAPEAR NUESTRAS PALABRAS RESERVADAS A UN NUMERO NUMERO DE FONT --> ENUM??
	//TODO: REVISAR BIEN QUE NUESTRAS PARALABRAS RESERVADAS COINCIDAN PARA HTML

	fprintf(file, "<a");
	fprintf(file, " href=\"%s\"", link->ref);
	
	if(link->attrs != NULL){
		tAttribute * current= link->attrs->first;
		while(current != NULL){
			switch (current->type){
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

void addImage(tImage* image){

	//TODO: COMO MANEJAR EL SIZE --> TENEMOS QUE MAPEAR NUESTRAS PALABRAS RESERVADAS A UNA WIDTH O HIGHT --> ENUM??
	//TODO: REVISAR BIEN QUE NUESTRAS PARALABRAS RESERVADAS COINCIDAN PARA HTML

	fprintf(file, "<img");
	fprintf(file, " %s", image->link);

	if(image->idref != NULL){
		fprintf(file, " %s", image->attrs->IDVALUE);
	}
	
	//PONEMOS UN TEXTO ALTERNATIVO??
	fprintf(file, " alt=%s", 'IMAGEN');

	fprintf(file, ">\n");
}

void addContainer(tContainer * container){
	fprintf(file, "<div>\n");
	WebPage(container->content); //LO DE ADENTRO EN COMO UNA PAGINA
	fprintf(file, "</div>\n");

	//TODO: HACE FALTA PASARLE ATRIBUTOS AL CONTAINER?? --> FONT?
}

//TODO: FUNCIONES PARA CONSTRUIR TABLAS
//TODO: BUSCAR COMO AGREGAR UNA FONT PARA TODO EL HTML O SI HAY Q AGREGARLO PARA TAG DE TEXTO POR DEFECTO
//TODO: TENEMOS QUE LIBERAR LA MEMORIA QUE ALOCAMOS