#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include <stdlib.h>
// #include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
tProgram * ProgramGrammarAction(tExprs * value);

tExprs * ExprAction(tExpr * exp);

tExprs * ExprsAction(tExpr * exp, tExprs * exps);

tProgram * EmptyExprAction();

tExpr * TitleExprAction(tTitle * title);

tExpr *  FontExprAction(tFont * font);

tExpr * TextExprAction(tText * text);

tExpr * ImgExprAction(tImage * img);

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

tAttributes * AttrAction(tAttributes * attr);

tAttributes * AttrsAction(tAttributes * attr, tAttributes * attrs);

tAttributes * IdAttrPatternAction(tAttribute * id);

tAttributes * SizeAttrPatternAction(tAttribute * size);

tAttributes * ColorAttrPatternAction(tAttribute * color);

tAttributes * PositionAttrPatternAction(tAttribute * position);

tAttributes * StyleAttrPatternAction(tAttributes * style);

tAttributes * PropertiesAttrPaternAction(tAttributes * properties);

tAttributes * PropertiesListAction(tAttribute * property, tAttributes * properties);

tAttributes * PropertyAttrAction(tAttribute * property);

tAttribute * IdAttrAction(char * ID);

tAttribute * SizeAttrAction(char * Size);

tAttribute * ColorAttrAction(char * Color);

tAttribute * PositionAttrAction(char * Position);

tAttribute * BoldAttrAction(char * Bold);

tAttribute * UnderlinedAttrAction(char * Underlined);

tAttribute * ItalicsAttrAction(char * Italics);

tTableAttrs * IdAndRowxColAttrPaternAction(tAttribute * id, tRowxColAttr * rowxcol);

tTableAttrs * RowxColAttrPatternAction(tRowxColAttr * rowxcol);

tRowxColAttr * RowxColAttrAction(int cols, int rows); //FIXME: PUEDE SER QUE NO LE LLEGUEN int?

tRows * TableAndRowContentAction(tRow * row_content, tRows * table_content);

tRows * RowContentAction(tRow * row_content);

tRow * RowExpressionsAction(tExprs * content);
#endif
