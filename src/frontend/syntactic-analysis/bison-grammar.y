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
%token <token> ID
%token <token> STRING
%token <token> SIZE
%token <token> COLOR
%token <token> STYLE
%token <token> POSITION
%token <token> NUMBER

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expressions> expressions
%type <expression> expression

// El símbolo inicial de la gramatica.
%start program

%%

program: START expressions END										{ $$ = ProgramGrammarAction($1); }
	;

expressions: expression 											{ $$ = ;}
		| expressions expression 									{ $$ = ;}
		;

expression: title													{ $$ = ;}
		| text														{ $$ = ;}
		| img														{ $$ = ;}
		| link														{ $$ = ;}
		| table														{ $$ = ;}
		| container													{ $$ = ;}
		;

title: TITLE title_attr STRING 										{ $$ = ; }
		| TITLE STRING 												{ $$ = ; } 
		;

text: TEXT title_attr STRING										{ $$ = ; }
		| TEXT STRING 												{ $$ = ; } 
		;	
		 
title_attr: id size color position style { $$ = ; }
		| id 														{ $$ = ; } 
		| size														{ $$ = ; } 
		| color														{ $$ = ; } 
		| position													{ $$ = ; } 
		| style 													{ $$ = ; } 
		;

img: IMG img_attr STRING											{ $$ = ; }
	 	| IMG STRING												{ $$ = ; }
		;

img_attr: id size position											{ $$ = ; }
		| id 														{ $$ = ; }
		| size														{ $$ = ; }
		| position													{ $$ = ; }
		;


link: LINK link_attrs STRING COMMA STRING									{ $$ = ; }
		| LINK STRING STRING										{ $$ = ; }
		;		

link_attr: id size color position style 							{ $$ = ; } 
		| id  														{ $$ = ; } 
		| size  													{ $$ = ; } 
		| color  													{ $$ = ; }
		| position  												{ $$ = ; }
		| style  													{ $$ = ; } 
		;

table: TABLE table_attr table_content END_TABLE 					{ $$ = ; }
		;

table_attr: id size  												{ $$ = ; } 
		| size  													{ $$ = ; }  
		;

table_content: row_content  										{ $$ = ; } 
		| table_content row_content  								{ $$ = ; } 
		;

row_content: ROW expression END_ROW 							 	{ $$ = ; } 
		;

container: CONTAINER expression END_CONTAINER  						{ $$ = ; } 
		| CONTAINER expression END_CONTAINER  						{ $$ = ; } 
		;

%%
