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
%x TABLE_SIZE

/* Patrones reutilizables. */
crlf			\r\n
size            (x-small|small|medium|large|x-large|xx-large)
color           (black|red|blue|yellow|green|orange|purple)
position        (left|center|right)
font            (Arial|Times|Calibri|Helvetica)
number          [0-9]+
id_attr         [A-Za-z][0-9]([A-Za-z]|[0-9])*
endline			\n
whitespace		[ \f\n\r\t\v]



%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"\""                                        { BEGIN(STRING); BeginStringPatternAction(); }
<STRING>[^\"]*                              { return StringPatternAttribute(yytext);}
<STRING>"\""                                { EndStringPatternAction(); BEGIN(INITIAL);}

"("                                        { BEGIN(TABLE_SIZE); BeginTableSizePatternAction(); }
<TABLE_SIZE>"x"                            { return XPatternTag(yytext);}
<TABLE_SIZE>{number}                       { return NumberPatternAttribute(yytext);}
<TABLE_SIZE>")"                            { EndTableSizePatternAction(); BEGIN(INITIAL);}

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

{size}                                      { return SizePatternAttribute(yytext); }
{color}                                     { return ColorPatternAttribute(yytext); }
{position}                                  { return PositionPatternAttribute(yytext); }
{font}                                      { return FontPatternAttribute(yytext); }
{id_attr}                                   { return IdPatternAttribute(yytext); }
{endline}                                   { EndlinePatternAttribute(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%
