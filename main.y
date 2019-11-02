%{
#include <stdio.h>
int yylex();
int yyerror(char *s);
extern int yylineno;
%}

%error-verbose

%token TYPE_INT "int"
%token TYPE_FLOAT "float"

%token MAINPROG "mainprog"
%token FUNCTION "function"
%token PROCEDURE "procedure"
%token BEGIN_BODY "begin"
%token END_BODY "end"
%token IF "if"
%token THEN "then"
%token ELIF "elif"
%token ELSE "else"
%token NOP "nop"
%token WHILE "while"
%token FOR "for"
%token RETURN "return"
%token PRINT "print"
%token IN "in"

%token ID "identifier"
%token FLOAT "decimal number"
%token INTEGER "integer number"

%token OP_EQ "=="
%token OP_NE "!="
%token OP_LE "<="
%token OP_GE ">="
%token OP_LT "<"
%token OP_GT ">"

%right ':' ELIF ELSE

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
	MAINPROG ID ';' declarations subprogram_declarations compound_statement { }
;


declarations:
	type identifier_list ';' declarations {}
	|
;
identifier_list:
	ID {}
	| ID ',' identifier_list {}
;


type:
	standard_type {}
	| standard_type '[' INTEGER ']' {}
;
standard_type:
	TYPE_INT {}
	| TYPE_FLOAT {}
;


subprogram_declarations:
	subprogram_declaration subprogram_declarations {}
	|
;
subprogram_declaration:
	subprogram_head declarations compound_statement {}
;
subprogram_head:
	FUNCTION ID arguments ':' standard_type ';' {}
	| PROCEDURE ID arguments ';' {}
;
arguments:
	'(' parameter_list ')' {}
	|
;
parameter_list:
	identifier_list ':' type {}
	| identifier_list ':' type ';' parameter_list{}
;


compound_statement:
	BEGIN_BODY statement_list END_BODY {}
;
statement_list:
	statement {}
	| statement ';' statement_list {}
;
statement:
	variable '=' expression {}
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
	IF expression ':' statement {}
	| IF expression ':' statement ELSE ':' statement {}
	| IF expression ':' statement elif_statement {}
	| IF expression ':' statement elif_statement ELSE ':' statement {}
;
elif_statement:
	ELIF expression ':' statement elif_statement {}
	| ELIF expression ':' statement {}
;


while_statement:
	WHILE expression ':' statement {}
	| WHILE expression ':' statement ELSE ':' statement {}
;


for_statement:
	FOR in_expression ':' statement {}
	| FOR in_expression ':' statement ELSE ':' statement {}
;


print_statement:
	PRINT {}
	| PRINT '(' expression ')' {}
;


variable:
	ID {}
	| ID '[' expression ']' {}
;


procedure_statement:
	ID '(' actual_parameter_expression ')' {}
;
actual_parameter_expression:
	expression_list {}
	|
;
expression_list:
	expression {}
	| expression ',' expression_list {}
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
	| '!' factor {}
	| sign factor {}
;


sign:
	'+' {}
	| '-' {}
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
	'+' {}
	| '-' {}
;
multop:
	'*' {}
	| '/' {}
;

%%

int yyerror(char *s) {
	printf("Compile Fail: %s at line %d\n", s, yylineno);
	return 0;
}

int main() {
	if (yyparse() == 0) {
		printf("Compile OK\n");
	}
	return 0;
}
