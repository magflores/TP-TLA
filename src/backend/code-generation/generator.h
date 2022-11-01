#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include <string.h>
#include "../support/shared.h"

#define BLOCK 200

void Generator(tProgram * result);
void WebPage(tExprs * expressions);
void addHTML(tExpr * result);
void addTitle(tTitle * title);
void addText(tText * text);
void addLink(tLink * link);
void addImage(tImage* image);
void addContainer(tContainer * container);

#endif
