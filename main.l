%{
#include <stdio.h>
#include <string.h>
#include "main.tab.h"
%}

%option	yylineno

letter			[a-zA-Z]
digit			[0-9]
id				{letter}({letter}|{digit})*
integer			{digit}+
float			{digit}*\.{digit}+

%%

"int"				{return (TYPE_INT);}
"float"				{return (TYPE_FLOAT);}

"mainprog"			{return (MAINPROG);}
"function"			{return (FUNCTION);}
"procedure"			{return (PROCEDURE);}
"begin"				{return (BEGIN_BODY);}
"end"				{return (END_BODY);}
"if"				{return (IF);}
"then"				{return (THEN);}
"elif"				{return (ELIF);}
"else"				{return (ELSE);}
"nop"				{return (NOP);}
"while"				{return (WHILE);}
"for"				{return (FOR);}
"return"			{return (RETURN);}
"print"				{return (PRINT);}
"in"				{return (IN);}

{id}				{sscanf(yytext, "%s", yylval.name); return (ID);}
{float}				{yylval.floatData = atof(yytext); return (FLOAT);}
{integer}			{yylval.intData = atoi(yytext); return (INTEGER);}

"=="				{return (OP_EQ);}
"!="				{return (OP_NE);}
"<="				{return (OP_LE);}
">="				{return (OP_GE);}
"<"					{return (OP_LT);}
">"					{return (OP_GT);}

[ \t\r\n]+			{}
.					{return *yytext;}

%%
