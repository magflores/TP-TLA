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
title_size      (x-small|small|medium|large|x-large|xx-large)
/* agregar color white si dejamos que el usuario cambie el color del background */
color           (black|red|blue|yellow|green|orange|purple)
position        (left|center|right)
number          [0-9]+
content         \".*\"
endline			\n
whitespace		[ \f\n\r\t\v]

%%
/* Que pasa si dentro de un string o dentro de cualquier tag tratan de escribir un comentario? */
"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"bold"                                      { return BoldTokenPattern(yytext); }
"italic"                                    { return ItalicTokenPattern(yytext); }
"underlined"                                { return UnderlinedTokenPattern(yytext); }

"+"											{ return AdditionOperatorPatternAction(yytext); }
"-"											{ return SubtractionOperatorPatternAction(yytext); }
"*"											{ return MultiplicationOperatorPatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }
"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
