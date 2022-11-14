%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {

	// No-terminales.
	tProgram * program;
	tExprs * expressions;
	tExpr * expression;
	tTitle * title;
	tImage * img;
	tLink * link;
	tTable * table;
	tFont *  font;
	tText * text; 
	tContainer * container;
	tAttributes * title_attrs;
	tAttributes * title_attr;
	tAttributes * img_attrs;
	tAttributes * img_attr;
	tAttributes * container_attrs;
	tAttributes * container_attr;
	tTableAttrs * table_attr;
	tRows * table_content;
	tRow * row_content;

	tAttribute * id;
	tAttribute * size;
	tAttribute * color;
	tAttribute * position;
	tAttributes * style;
	tRowxColAttr * rowxcol;

	tAttributes * properties;
	tAttribute * property;

	// Terminales.
	token token;
	char * token_string;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> START
%token <token> END
%token <token> CONTAINER
%token <token> TITLE
%token <token> TABLE
%token <token> IMG
%token <token> LINK
%token <token> ROW
%token <token> TEXT
%token <token> STYLE
%token <token> ID
%token <token> SIZE
%token <token> COLOR
%token <token> POSITION
%token <token> FONT

%token <token> COLON
%token <token> COMMA
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> X

%token <token_string> ID_ATTR
%token <token_string> SIZE_ATTR
%token <token_string> COLOR_ATTR
%token <token_string> POSITION_ATTR
%token <token_string> FONT_ATTR
%token <token_string> STRING
%token <token_string> BOLD
%token <token_string> UNDERLINED
%token <token_string> ITALICS

%token <token> ENDLINE
%token <token> ROWXCOL

%token <int> NUMBER

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expressions> expressions
%type <expression> expression
%type <title> title 
%type <font> font
%type <text> text
%type <img> img
%type <link> link
%type <table> table
%type <container> container
%type <title_attrs> title_attrs 
%type <title_attr> title_attr 
%type <img_attrs> img_attrs
%type <img_attr> img_attr
%type <container_attr> container_attrs
%type <container_attr> container_attr
%type <table_attr> table_attr  
%type <table_content> table_content
%type <row_content> row_content
%type <id> id
%type <size> size
%type <color> color
%type <position> position
%type <style> style
%type <properties> properties
%type <property> property
%type <rowxcol> rowxcol

// El símbolo inicial de la gramatica.
%start program

%%

program: START expressions END										{ $$ = ProgramGrammarAction($2); }
		| START /*lambda*/ END										{ $$ = EmptyExprAction(); }
		;

expressions: expression expressions 								{ $$ = ExprsAction($1, $2); }
		| expression 												{ $$ = ExprAction($1); }
		;

expression: title													{ $$ = TitleExprAction($1); }
		| font														{ $$ = FontExprAction($1); }
		| text														{ $$ = TextExprAction($1); }
		| img														{ $$ = ImgExprAction($1); }
		| link														{ $$ = LinkExprAction($1); }
		| table														{ $$ = TableExprAction($1); }
		| container													{ $$ = ContainerExprAction($1); }
		;

title: TITLE title_attrs STRING 									{ $$ = TitleWithAttrsGrammarAction($2, $3); }
		| TITLE STRING 												{ $$ = TitleWithoutAttrsGrammarAction($2); } 
		;

font: FONT FONT_ATTR												{ $$ = FontGrammarAction($2); }
		;

text: TEXT title_attrs STRING										{ $$ = TextWithAttrsGrammarAction($2, $3); }
		| TEXT STRING 												{ $$ = TextWithoutAttrsGrammarAction($2); }
		;

img: IMG img_attrs STRING											{ $$ = ImgWithAttrsGrammarAction($2, $3); }
	 	| IMG STRING												{ $$ = ImgWithoutAttrsGrammarAction($2); }
		;

link: LINK title_attrs STRING COMMA STRING							{ $$ = LinkWithAttrsGrammarAction($2, $3, $5); }
		| LINK STRING COMMA STRING									{ $$ = LinkWithoutAttrsGrammarAction($2, $4); }
		;	

table: TABLE table_attr table_content END TABLE 					{ $$ = TableGrammarAction($2, $3); }
		;

container: CONTAINER container_attrs expressions END CONTAINER  	{ $$ = ContainerWithAttrsGrammarAction($2, $3); } 
		| CONTAINER expressions END CONTAINER						{ $$ = ContainerWithoutAttrsGrammarAction($2); }
		;

title_attrs: title_attr title_attrs									{ $$ = AttrsAction($1, $2); }
		| title_attr												{ $$ = AttrAction($1); }
		;

title_attr: id														{ $$ = IdAttrPatternAction($1); }
		| size 														{ $$ = SizeAttrPatternAction($1); } 
		| color 													{ $$ = ColorAttrPatternAction($1); } 
		| position 													{ $$ = PositionAttrPatternAction($1); }
		| style 													{ $$ = StyleAttrPatternAction($1); }
		;

img_attrs: img_attr img_attrs										{ $$ = AttrsAction($1, $2); }
		| img_attr													{ $$ = AttrAction($1); }
		;

img_attr: id														{ $$ = IdAttrPatternAction($1); }
		| size 														{ $$ = SizeAttrPatternAction($1); } 
		| position 													{ $$ = PositionAttrPatternAction($1); }
		;

container_attrs: container_attr container_attrs						{ $$ = AttrsAction($1, $2); }
		| container_attr											{ $$ = AttrAction($1); }
		;

container_attr: id													{ $$ = IdAttrPatternAction($1); }
		| position 													{ $$ = PositionAttrPatternAction($1); }
		;

id: ID COLON ID_ATTR												{ $$ = IdAttrAction($3); }
		;

size: SIZE COLON SIZE_ATTR											{ $$ = SizeAttrAction($3); }
		;

color: COLOR COLON COLOR_ATTR 										{ $$ = ColorAttrAction($3); }
		;

position: POSITION COLON POSITION_ATTR								{ $$ = PositionAttrAction($3); }
		;

style: STYLE COLON properties 										{ $$ = PropertiesAttrPaternAction($3); }
		;

properties: property COMMA properties 								{ $$ = PropertiesListAction($1, $3); }
		| property 													{ $$ = PropertyAttrAction($1); }
		;

property: BOLD 														{ $$ = BoldAttrAction($1); } 
		| UNDERLINED 												{ $$ = UnderlinedAttrAction($1); } 
		| ITALICS 													{ $$ = ItalicsAttrAction($1); }
		; 	

table_attr: id rowxcol												{ $$ = IdAndRowxColAttrPaternAction($1, $2); } 
		| rowxcol		 											{ $$ = RowxColAttrPatternAction($1); }  
		;

rowxcol: ROWXCOL COLON OPEN_PARENTHESIS NUMBER X NUMBER CLOSE_PARENTHESIS			{ $$ = RowxColAttrAction($4, $6); }
		;

table_content: row_content table_content  							{ $$ = TableAndRowContentAction($1, $2); } 
		| row_content  												{ $$ = RowContentAction($1); } 
		;

row_content: ROW expressions END ROW 							 	{ $$ = RowExpressionsAction($2); } 
		;

%%