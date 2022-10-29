#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
void ProgramGrammarAction(tExprs * value);

tExprs * ExprAction(tExpr * exp);

tExprs * ExprsAction(tExprs * exps, tExpr * exp);

void EmptyExprAction();

tExpr * TitleExprAction(tTitle * title);

tExpr *  FontExprAction(tFont * font);

tExpr * TextExprAction(tText * text);

tExpr * ImgExpressionAction(tImage * img);

tExpr * LinkExprAction(tLink * link);

tExpr * TableExprAction(tTable * table);

tExpr * ContainerExprAction(tContainer * div);

tTitle * TitleWithoutAttrsGrammarAction(char * content);

tTitle * TitleWithAttrsGrammarAction(tAttributes * attrs, char * content);

tFont * FontGrammarAction(char * content);

tText * TextWithoutAttrsGrammarAction(char * content);

tText * TextWithAttrsGrammarAction(tAttributes * attrs, char * content);

tImage * ImgWithAttrsGrammarAction(tAttributes * attrs, char * link);

tImage * ImgWithoutAttrsGrammarAction(char * link);

tLink * LinkWithAttrsGrammarAction(tAttributes * attrs, char * ref, char * text);

tLink * LinkWithoutAttrsGrammarAction(char * ref, char * text);

tTable * TableGrammarAction(tTableAttrs * attrs, tRows * rows);

tContainer * ContainerWithAttrsGrammarAction(tAttributes * attrs, tExprs * exprs);

tContainer * ContainerWithoutAttrsGrammarAction(tExprs * exprs);
#endif
