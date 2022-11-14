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
crlf			[\r\n]
size            (x-small|small|medium|large|x-large|xx-large)
color           (black|red|blue|yellow|green|orange|purple)
position        (left|center|right)
font            (Arial|Verdana|Cambria|Impact)
digit           [0-9]
id_attr         ([A-Za-z]|[0-9])*
endline			[\n]
whitespace		[ \f\n\r\t\v]

%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"\""                                        { BEGIN(STRING); BeginStringPatternAction(); }
<STRING>[^\"]*                              { return StringAttributeValue(yytext, yyleng);}
<STRING>"\""                                { EndStringPatternAction(); BEGIN(INITIAL);}

"("                                        { BEGIN(TABLE_SIZE); return BeginTableSizePatternAction(); }
<TABLE_SIZE>"x"                            { return XPatternTag();}
<TABLE_SIZE>{digit}+                       { return NumberAttributeValue(yytext, yyleng);}
<TABLE_SIZE>")"                            { BEGIN(INITIAL); return EndTableSizePatternAction(); }

"START"                                     { return StartPatternTag(); }
"END"                                       { return EndPatternTag(); }
"CONTAINER"                                 { return ContainerPatternTag(); }
"TITLE"                                     { return TitlePatternTag(); }
"TABLE"                                     { return TablePatternTag(); }
"IMG"                                       { return ImagePatternTag(); }
"LINK"                                      { return LinkPatternTag(); }
"ROW"                                       { return RowPatternTag(); }
"TEXT"                                      { return TextPatternTag(); }
"FONT"                                      { return FontPatternTag(); }

"id"                                        { return IdAttributeKey(); }
"style"                                     { return StyleAttributeKey(); }
"bold"                                      { return BoldAttributeValue(); }
"underlined"                                { return UnderlinedAttributeValue(); }
"italics"                                   { return ItalicsAttributeValue(); }
"size"                                      { return SizeAttributeKey(); }
"color"                                     { return ColorAttributeKey(); }
"position"                                  { return PositionAttributeKey(); }
"rowxcol"                                   { return TableSizeAttributeKey(); }

":"                                         { return ColonPatternTag(); } 
","                                         { return CommaPatternTag(); } 

{size}                                      { return SizeAttributeValue(yytext, yyleng); }
{color}                                     { return ColorAttributeValue(yytext, yyleng); }
{position}                                  { return PositionAttributeValue(yytext, yyleng); }
{font}                                      { return FontAttributeValue(yytext, yyleng); }
{id_attr}                                   { return IdAttributeValue(yytext, yyleng); }

{endline}                                   { EndlinePatternAttribute(yytext, yyleng); }
{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%
