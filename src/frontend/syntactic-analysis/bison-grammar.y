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

	int integer;
	char * string;

	// No-terminales (frontend).
	int program;
	int expressions;
	int expression;
	char * title;
	char * text; 
	char * img;
	char * link;
	char * table;
	char * container;
	char * title_attr;
	char * img_attr;
	char * link_attr;
	char * table_attr;
	char * table_content;
	char * row_content;


	// Terminales.
	token token;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> START
%token <token> END
%token <token> CONTAINER
%token <token> END_CONTAINER
%token <token> TITLE
%token <token> TABLE
%token <token> END_TABLE
%token <token> IMG
%token <token> LINK
%token <token> ROW
%token <token> END_ROW
%token <token> TEXT

%token <token> COLON
%token <token> COMMA
%token <token> X

%token <string> ID
%token <string> STRING
%token <string> SIZE
%token <string> COLOR
%token <string> STYLE
%token <string> POSITION

%token <integer> NUMBER

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
%type <title_attr> title_attr 
%type <img_attr> img_attr
%type <link_attr> link_attr
%type <table_attr> table_attr  
%type <table_content> table_content
%type <row_content> row_content

// El símbolo inicial de la gramatica.
%start program

%%

program: START expressions END										{ $$ = ProgramGrammarAction($2); }
	;

expressions: expression 											{ }
		| expressions expression 									{ }
		;

expression: title													{ }
		| text														{ }
		| img														{ }
		| link														{ }
		| table														{ }
		| container													{ }
		;

title: TITLE title_attr STRING 										{ }
		| TITLE STRING 												{ } 
		;

text: TEXT title_attr STRING										{ }
		| TEXT STRING 												{ }
		 
title_attr: ID SIZE COLOR POSITION STYLE 							{ }
		| ID 														{ } 
		| SIZE														{ } 
		| COLOR														{ } 
		| POSITION													{ } 
		| STYLE 													{ } 
		;

img: IMG img_attr STRING											{ }
	 	| IMG STRING												{ }
		;

img_attr: ID SIZE POSITION											{ }
		| ID 														{ }
		| SIZE														{ }
		| POSITION													{ }
		;


link: LINK link_attr STRING COMMA STRING							{ }
		| LINK STRING COMMA STRING									{ }
		;		

link_attr: ID SIZE COLOR POSITION STYLE 							{ } 
		| ID  														{ } 
		| SIZE  													{ } 
		| COLOR  													{ }
		| POSITION  												{ }
		| STYLE  													{ } 
		;

table: TABLE table_attr table_content END_TABLE 					{ }
		;

table_attr: ID NUMBER X NUMBER 										{ } 
		| NUMBER X NUMBER 											{ }  
		;

table_content: row_content  										{ } 
		| table_content row_content  								{ } 
		;

row_content: ROW expression END_ROW 							 	{ } 
		;

container: CONTAINER expressions END_CONTAINER  					{ } 
		;

%%
