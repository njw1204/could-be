%{
#include <stdio.h>
#include <string.h>
#include "main.tab.h"
void showError();
%}

letter			[a-zA-Z]
digit			[0-9]
id				{letter}({letter}|{digit})*
integer			{digit}+
float			{digit}*\.{digit}+

%%

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
{integer}			{yylval.intData = atoi(yytext); return (INTEGER);}
{float}				{yylval.floatData = atof(yytext); return (FLOAT);}

"+"                 {return (OP_PLUS);}
"-"					{return (OP_MINUS);}
"*"					{return (OP_MULT);}
"/"					{return (OP_DIV);}
"<"					{return (OP_LT);}
">"					{return (OP_GT);}
"!="				{return (OP_NE);}
"<="				{return (OP_LE);}
">="				{return (OP_GE);}
"=="				{return (OP_EQ);}
"!"					{return (OP_NOT);}

";"					{return (DE_SEMICOLON);}
","					{return (DE_COMMA);}
"."					{return (DE_DOT);}
"="					{return (DE_ASSIGN);}
"("					{return (DE_LP);}
")"					{return (DE_RP);}
"["					{return (DE_LSB);}
"]"					{return (DE_RSB);}
":"					{return (DE_COLON);}

[ \t\n\r]+			{}
.					{showError(); return (OTHER);}

%%

void showError() {
	printf("Unexpected character");
}
