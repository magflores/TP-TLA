%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expressions expressions;
	Expression expression;
	...
	*/

	// No-terminales (frontend).
	int program;
	int expressions;
	int expression;
	int title;
	int text; 
	int img;
	int link;
	int table;
	int container;
	int title_attrs;
	int title_attr;
	int img_attrs;
	int img_attr;
	int container_attrs;
	int container_attr;
	int table_attr;
	int table_content;
	int row_content;

	int id;
	int size;
	int color;
	int position;
	int style;

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
%token <token> X

%token <token> ID_ATTR
%token <token> SIZE_ATTR
%token <token> COLOR_ATTR
%token <token> POSITION_ATTR
%token <token> FONT_ATTR
%token <token> STRING
%token <token> ENDLINE

%token <token> NUMBER

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expressions> expressions
%type <expression> expression
%type <title> title 
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

// El símbolo inicial de la gramatica.
%start program

%%

program: START expressions END										{ $$ = ProgramGrammarAction($2); }
		;

expressions: expression expressions 								{ }
		| expression 												{ }
		;

expression: title													{ }
		| text														{ }
		| img														{ }
		| link														{ }
		| table														{ }
		| container													{ }
		;

title: TITLE title_attrs STRING 									{ }
		| TITLE STRING 												{ } 
		;

text: TEXT title_attrs STRING										{ }
		| TEXT STRING 												{ }
		;

img: IMG img_attrs STRING											{ }
	 	| IMG STRING												{ }
		;

link: LINK title_attrs STRING COMMA STRING							{ }
		| LINK STRING COMMA STRING									{ }
		;	

table: TABLE table_attr table_content END TABLE 					{ }
		;

container: CONTAINER container_attrs expressions END CONTAINER  	{ } 
		| CONTAINER expressions END CONTAINER						{ }
		;

title_attrs: title_attr title_attrs									{ }
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

container_attrs: img_attr img_attrs									{ }
		| img_attr													{ }
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

table_attr: id NUMBER X NUMBER 										{ } 
		| NUMBER X NUMBER 											{ }  
		;

table_content: row_content table_content  							{ } 
		| row_content  												{ } 
		;

row_content: ROW expression END ROW 							 	{ } 
		;

%%
