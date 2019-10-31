%{
#include <stdio.h>
int yylex();
int yyerror(char *s);
%}

%token MAINPROG FUNCTION PROCEDURE BEGIN END IF THEN ELSE NOP WHILE RETURN PRINT IN ID INTEGER FLOAT OPERATOR DELIMITER OTHER

%type <name> ID
%type <intData> INTEGER
%type <floatData> FLOAT
%type <name> OPERATOR
%type <name> DELIMITER

%union {
	char name[1024];
	int intData;
	float floatData;
}

%%

program:
;

%%

int yyerror(char *s) {
	printf("Syntax Error at line %s\n", s);
	return 0;
}

int main() {
	yyparse();
	return 0;
}
