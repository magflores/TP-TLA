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
	tAttribute * title_attr;
	tAttributes * img_attrs;
	tAttribute * img_attr;
	tAttributes * container_attrs;
	tAttribute * container_attr;
	tAttribute * table_attr;
	tRows * table_content;
	tRow * row_content;

	int id;
	int size;
	int color;
	int position;
	int style;
	int rowxcol;

	int properties;
	int property;

	// Terminales.
	token token;
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
%token <token> BOLD
%token <token> UNDERLINED
%token <token> ITALICS
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

%token <token> ID_ATTR
%token <token> SIZE_ATTR
%token <token> COLOR_ATTR
%token <token> POSITION_ATTR
%token <token> FONT_ATTR
%token <token> STRING

%token <token> ENDLINE
%token <token> ROWXCOL

%token <token> NUMBER

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

program: START expressions END										{ ProgramGrammarAction($2); }
		;

expressions: expression expressions 								{ $$ = ExprsAction($1, $2); }
		| expression 												{ $$ = ExprAction($1); }
		| /*lambda*/												{ EmptyExprAction(); }
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
		| CONTAINER expressions END CONTAINER						{ $$ = ContainerWithoutAttrsGrammarAction($3); }
		;

title_attrs: title_attr title_attrs									{  }
		| title_attr												{ }
		;

title_attr: id														{ }
		| size 														{ } 
		| color 													{ } 
		| position 													{ }
		| style 													{ }
		;

img_attrs: img_attr img_attrs										{ }
		| img_attr													{ }
		;

img_attr: id														{ }
		| size 														{ } 
		| position 													{ }
		;

container_attrs: container_attr container_attrs						{ }
		| container_attr											{ }
		;

container_attr: id													{ }
		| position 													{ }
		;

id: ID COLON ID_ATTR												{ }
		;

size: SIZE COLON SIZE_ATTR											{ }
		;

color: COLOR COLON COLOR_ATTR 										{ }
		;

position: POSITION COLON POSITION_ATTR								{ }
		;

style: STYLE COLON properties 										{ }
		;

properties: property COMMA properties 								{ }
		| property 													{ }
		;

property: BOLD 														{ } 
		| UNDERLINED 												{ } 
		| ITALICS 													{ }
		; 	

table_attr: id rowxcol												{ } 
		| rowxcol		 											{ }  
		;

rowxcol: ROWXCOL COLON 
		 OPEN_PARENTHESIS NUMBER X NUMBER CLOSE_PARENTHESIS			{ }
		;

table_content: row_content table_content  							{ } 
		| row_content  												{ } 
		;

row_content: ROW expressions END ROW 							 	{ } 
		;

%%