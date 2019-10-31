%{
#include <stdio.h>
int yylex();
int yyerror(char *s);
%}

%token MAINPROG FUNCTION PROCEDURE BEGIN_BODY END_BODY IF THEN ELIF ELSE NOP WHILE FOR RETURN PRINT IN ID INTEGER FLOAT OTHER
%token OP_PLUS OP_MINUS OP_MULT OP_DIV OP_LT OP_GT OP_NE OP_LE OP_GE OP_EQ OP_NOT
%token DE_SEMICOLON DE_COMMA DE_DOT DE_ASSIGN DE_LP DE_RP DE_LSB DE_RSB DE_COLON

%right DE_COLON ELIF ELSE
%left OP_LT OP_GT OP_NE OP_LE OP_GE OP_EQ IN
%left OP_PLUS OP_MINUS
%left OP_MULT OP_DIV

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
	MAINPROG ID DE_SEMICOLON declarations subprogram_declarations compound_statement { }
;


declarations:
	type identifier_list DE_SEMICOLON declarations {}
	|
;
identifier_list:
	ID {}
	| ID DE_COMMA identifier_list {}
;


type:
	standard_type {}
	| standard_type DE_LSB INTEGER DE_RSB {}
;
standard_type:
	INTEGER {}
	| FLOAT {}
;


subprogram_declarations:
	subprogram_declaration subprogram_declarations {}
	|
;
subprogram_declaration:
	subprogram_head declarations compound_statement {}
;
subprogram_head:
	FUNCTION ID arguments DE_COLON standard_type DE_SEMICOLON {}
	| PROCEDURE ID arguments DE_SEMICOLON {}
;
arguments:
	DE_LP parameter_list DE_RP {}
	|
;
parameter_list:
	identifier_list DE_COLON type {}
	| identifier_list DE_COLON type DE_SEMICOLON {}
;


compound_statement:
	BEGIN_BODY statement_list END_BODY {}
;
statement_list:
	statement {}
	| statement DE_SEMICOLON statement_list {}
;
statement:
	variable DE_ASSIGN expression {}
	| print_statement {}
	| procedure_statement {}
	| compound_statement {}
	| if_statement {}
	| while_statement {}
	| for_statement {}
	| RETURN expression
	| NOP
;


if_statement:
	IF expression DE_COLON statement {}
	| IF expression DE_COLON statement ELSE DE_COLON statement {}
	| IF expression DE_COLON statement elif_statement {}
	| IF expression DE_COLON statement elif_statement ELSE DE_COLON statement {}
;
elif_statement:
	ELIF expression DE_COLON statement elif_statement {}
	| ELIF expression DE_COLON statement {}
;


while_statement:
	WHILE expression DE_COLON statement {}
	| WHILE expression DE_COLON statement ELSE DE_COLON statement {}
;


for_statement:
	FOR in_expression DE_COLON statement {}
	| FOR in_expression DE_COLON statement ELSE DE_COLON statement {}
;


print_statement:
	PRINT {}
	| PRINT DE_LP expression DE_RP {}
;


variable:
	ID {}
	| ID DE_LSB expression DE_RSB {}
;


procedure_statement:
	ID DE_LP actual_parameter_expression DE_RP {}
;
actual_parameter_expression:
	expression_list {}
	|
;
expression_list:
	expression {}
	| expression DE_COMMA expression_list {}
;


expression:
	simple_expression {}
	| in_expression {}
	| simple_expression relop simple_expression {}
;
in_expression:
	simple_expression IN simple_expression {}
;
simple_expression:
	term {}
	| term addop simple_expression {}
;
term:
	factor {}
	| factor multop term {}
;
factor:
	INTEGER {}
	| FLOAT {}
	| variable {}
	| procedure_statement {}
	| OP_NOT factor {}
	| sign factor {}
;

sign:
	OP_PLUS {}
	| OP_MINUS {}
;
relop:
	OP_GT {}
	| OP_GE {}
	| OP_LT {}
	| OP_LE {}
	| OP_EQ {}
	| OP_NE {}
;
addop:
	OP_PLUS {}
	| OP_MINUS {}
;
multop:
	OP_MULT {}
	| OP_DIV {}
;
%%

int yyerror(char *s) {
	printf("Error: %s at line %d\n", s, yylineno);
	return 0;
}

int main() {
	yyparse();
	return 0;
}
