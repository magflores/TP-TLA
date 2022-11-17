#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include <string.h>
#include <stdlib.h>
#include "../support/shared.h"

#define BLOCK 200

void Generator(tProgram * result);
void WebPage(tExprs * expressions);
void addHTML(tExpr * result);
void addTitle(tTitle * title);
void addStyle(tAttributes * attrs);
void addText(tText * text);
void addLink(tLink * link);
void addImage(tImage* image);
void addContainer(tContainer * container);
void addTable(tTable * table);
void addFont(tFont * font);
void addRowContent(tExprs *rowContent, int cols);

int getTitleSize(tAttributes * attrs);
int getFontSize(char * value);
int getImgSize(char * value);

void freeMemory(tExpr * expr);
void freeExpression(tExpr * expr);
void freeAttributes(tAttribute * attrs);
void freeRows(tRow * row);

#endif
