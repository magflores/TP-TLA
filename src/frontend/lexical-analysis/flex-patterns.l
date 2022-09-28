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
id              [A-Za-z][0-9]([A-Za-z]|[0-9])*
size            (x-small|small|medium|large|x-large|xx-large)
color           (black|red|blue|yellow|green|orange|purple)
position        (left|center|right)
font            (arial|times|calibri|helvetica)
number          [0-9]+
string          \".*\"
endline			\n
whitespace		[ \f\n\r\t\v]


%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"START"                                     { StartPatternTag(yytext); }
"END"                                       { EndPatternTag(yytext); }
"CONTAINER"                                 { ContainerPatternTag(yytext); }
"TITLE"                                     { TitlePatternTag(yytext); }
"TABLE"                                     { TablePatternTag(yytext); }
"BOLD"                                      { BoldPatternTag(yytext); }
"UNDERLINED"                                { UnderlinedPatternTag(yytext); }
"ITALICS"                                   { ItalicsPatternTag(yytext); }
"IMG"                                       { ImagePatternTag(yytext); }
"LINK"                                      { LinkPatternTag(yytext); }
"ROW"                                       { RowPatternTag(yytext); }
"TEXT"                                      { TextPatternTag(yytext); }
"FONT"                                      { FontPatternTag(yytext); }

"id"                                        { IdPatternTag(yytext); }
"style"                                     { StylePatternTag(yytext); }
"size"                                      { SizePatternTag(yytext); }
"color"                                     { ColorPatternTag(yytext); }
"position"                                  { PositionPatternTag(yytext); }

":"                                         { ColonPatternTag(yytext); }
","                                         { CommaPatternTag(yytext); }
"x"                                         { XPatternTag(yytext); }


{id}                                        { IdPatternAttribute(yytext); }
{string}                                    { StringPatternAttribute(yytext); }
{size}                                      { SizePatternAttribute(yytext); }
{color}                                     { ColorPatternAttribute(yytext); }
{position}                                  { PositionPatternAttribute(yytext); }
{number}                                    { NumberPatternAttribute(yytext); }
{font}                                      { FontPatternAttribute(yytext); }
{endline}                                   { EndlinePatternAttribute(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%
