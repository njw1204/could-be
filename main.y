%{
#include <stdio.h>
int yylex();
int yyerror(char *s);
%}

%token MAINPROG FUNCTION PROCEDURE BEGIN END IF THEN ELSE NOP WHILE RETURN PRINT IN ID INTEGER FLOAT OTHER
%token OP_PLUS OP_MINUS OP_MULT OP_DIV OP_LT OP_GT OP_NE OP_LE OP_GE OP_EQ OP_NOT
%token DE_SEMICOLON DE_COMMA DE_DOT DE_EQUAL DE_LP DE_RP DE_LSB DE_RSB DE_COLON


%type <name> ID
%type <intData> INTEGER
%type <floatData> FLOAT

%union {
	char name[1024];
	int intData;
	float floatData;
}

%%

program:
	MAINPROG ID DE_SEMICOLON declarations subprogram_declarations compound_statement
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
