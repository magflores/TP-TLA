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
%x STRING

/* Patrones reutilizables. */
crlf			\r\n
id_attr         [A-Za-z][0-9]([A-Za-z]|[0-9])*
size            (x-small|small|medium|large|x-large|xx-large)
color           (black|red|blue|yellow|green|orange|purple)
position        (left|center|right)
font            (Arial|Times|Calibri|Helvetica)
number          [0-9]+
source          \'.*\'
string          \".*\"
endline			\n
whitespace		[ \f\n\r\t\v]

/*"\""                                        { BEGIN(STRING); BeginStringPatternAction(); }*/
/*<STRING>{string}                            { return StringPatternAttribute(yytext);}*/
/*<STRING>"\""                                { EndStringPatternAction(); BEGIN(INITIAL);}*/

%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"START"                                     { return StartPatternTag(yytext); }
"END"                                       { return EndPatternTag(yytext); }
"CONTAINER"                                 { return ContainerPatternTag(yytext); }
"TITLE"                                     { return TitlePatternTag(yytext); }
"TABLE"                                     { return TablePatternTag(yytext); }
"IMG"                                       { return ImagePatternTag(yytext); }
"LINK"                                      { return LinkPatternTag(yytext); }
"ROW"                                       { return RowPatternTag(yytext); }
"TEXT"                                      { return TextPatternTag(yytext); }
"FONT"                                      { return FontPatternTag(yytext); }

"id"                                        { return IdPatternTag(yytext); }
"style"                                     { return StylePatternTag(yytext); }
"bold"                                      { return BoldPatternTag(yytext); }
"underlined"                                { return UnderlinedPatternTag(yytext); }
"italics"                                   { return ItalicsPatternTag(yytext); }
"size"                                      { return SizePatternTag(yytext); }
"color"                                     { return ColorPatternTag(yytext); }
"position"                                  { return PositionPatternTag(yytext); }
"rowxcol"                                   { return TableSizePatternTag(yytext); }

":"                                         { return ColonPatternTag(yytext); }
","                                         { return CommaPatternTag(yytext); }
"x"                                         { return XPatternTag(yytext); }

{id_attr}                                   { return IdPatternAttribute(yytext); }
{size}                                      { return SizePatternAttribute(yytext); }
{color}                                     { return ColorPatternAttribute(yytext); }
{position}                                  { return PositionPatternAttribute(yytext); }
{string}                                    { return StringPatternAttribute(yytext); }
{source}                                    { return SourcePatternAttribute(yytext);}
{number}                                    { return NumberPatternAttribute(yytext); }
{font}                                      { return FontPatternAttribute(yytext); }
{endline}                                   { EndlinePatternAttribute(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%
