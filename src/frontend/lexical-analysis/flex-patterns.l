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
/* Son atributos unicos, los que van en formato de lista son los styles */
color           (black|red|blue|yellow|green|orange|purple)
position        (left|center|right)
font            (Arial|Times|Calibri|Helvetica)
number          [0-9]+
id_attr         ([A-Za-z]|[0-9])*
endline			\n
whitespace		[ \f\n\r\t\v]



%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"\""                                        { BEGIN(STRING); BeginStringPatternAction(); }
<STRING>[^\"]*                              { return StringPatternAttribute(yytext, yyleng);}
<STRING>"\""                                { EndStringPatternAction(); BEGIN(INITIAL);}

"("                                        { BEGIN(TABLE_SIZE); return BeginTableSizePatternAction(yytext); }
<TABLE_SIZE>"x"                            { return XPatternTag(yytext);}
<TABLE_SIZE>{number}                       { return NumberPatternAttribute(yytext, yyleng);}
<TABLE_SIZE>")"                            { BEGIN(INITIAL); return EndTableSizePatternAction(yytext); }

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

{size}                                      { return SizePatternAttribute(yytext, yyleng); }
{color}                                     { return ColorPatternAttribute(yytext, yyleng); }
{position}                                  { return PositionPatternAttribute(yytext, yyleng); }
{font}                                      { return FontPatternAttribute(yytext, yyleng); }
{id_attr}                                   { return IdPatternAttribute(yytext, yyleng); }

{endline}                                   { EndlinePatternAttribute(yytext, yyleng); }
{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%
