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

"START"                                     { StartPatternTag(const char * lexeme); }
"END"                                       { EndPatternTag(const char * lexeme); }
"CONTAINER"                                 { ContainerPatternTag(const char * lexeme); }
"END CONTAINER"                             { EndContainerPatternTag(const char * lexeme); }
"TITLE"                                     { TitlePatternTag(const char * lexeme, const int length); }
"TABLE"                                     { TablePatternTag(const char * lexeme); }
"END TABLE"                                 { EndTablePatternTag(const char * lexeme); }
"IMG"                                       { ImagePatternTag(const char * lexeme); }
"LINK"                                      { LinkPatternTag(const char * lexeme); }
"ROW"                                       { RowPatternTag(const char * lexeme); }
"END ROW"                                   { EndRowPatternTag(const char * lexeme); }
"TEXT"                                      { TextPatternTag(const char * lexeme); }
":"                                         { ColonPatternTag(const char * lexeme); }
","                                         { CommaPatternTag(const char * lexeme); }

{id}                                        { IdPatternAttribute(const char * lexeme); }
{string}                                    { StringPatternAttribute(const char * lexeme); }
{size}                                      { SizePatternAttribute(const char * lexeme); }
{color}                                     { ColorPatternAttribute(const char * lexeme); }
{style}                                     { StylePatternAttribute(const char * lexeme); }
{position}                                  { PositionPatternAttribute(const char * lexeme); }
{number}                                    { NumberPatternAttribute(const char * lexeme); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext); }

%%
