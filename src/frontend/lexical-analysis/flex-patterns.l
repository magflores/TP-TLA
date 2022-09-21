%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT

/* Patrones reutilizables. */
crlf			\r\n
id              id:[0-9]+
size            (x-small|small|medium|large|x-large|xx-large)
color           (black|red|blue|yellow|green|orange|purple)
style           (bold|italics|underlined)
position        (left|center|right)
font            (arial|times|calibri|courier new|helvetica)
number          [0-9]+
string          \".*\"
endline			\n
whitespace		[ \f\n\r\t\v]


%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"start"                                     {}
"end"                                       {}
"begincontainer"                            {}
"endcontainer"                              {}
"title"                                     {}
"table"                                     {}
"endtable"                                  {}
"img"                                       {}
"link"                                      {}
"row"                                       {}
"endrow"                                    {}
"text"                                      {}
":"                                         {}
","                                         {}

{id}                                        {}
{string}                                    {}
{size}                                      {}
{color}                                     {}
{style}                                     {}
{position}                                  {}
{number}                                    {}

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext); }

%%
