%{
#include <stdio.h>
#include <string.h>
#include "main.tab.h"
void showError();
%}

letter			[a-zA-Z]
digit			[0-9]
operator		\+|\-|\*|/|\<|\<\=|\>\=|\>|\=\=|\!\=|\!
delimiter		;|\.|,|\=|\(|\)|\[|\]|:
id				{letter}({letter}|{digit})*
integer			{digit}+
float			{digit}*\.{digit}+

%%

"mainprog"			{return (MAINPROG);}
"function"			{return (FUNCTION);}
"procedure"			{return (PROCEDURE);}
"begin"				{return (BEGIN);}
"end"				{return (END);}
"if"				{return (IF);}
"then"				{return (THEN);}
"else"				{return (ELSE);}
"nop"				{return (NOP);}
"while"				{return (WHILE);}
"return"			{return (RETURN);}
"print"				{return (PRINT);}
"in"				{return (IN);}
{id}				{sscanf(yytext, "%s", yylval.name); return (ID);}
{integer}			{yylval.intData = atoi(yytext); return (INTEGER);}
{float}				{yylval.floatData = atof(yytext); return (FLOAT);}
{operator}			{sscanf(yytext, "%s", yylval.name); return (OPERATOR);}
{delimiter}			{sscanf(yytext, "%s", yylval.name); return (DELIMITER);}
[ \t\n\r]+			{}
.					{showError(); return(OTHER);}

%%

void showError() {
	printf("Unexpected character");
}
