%{
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
int yylex();
int yyerror(char *s);
void prepareParse();
extern int yylineno;

int errorCount = 0;
FILE *yyin;
HashTable symbolTable;
char buf[2048] = {0};
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

%type <intData> identifier_list // 식별자 개수
%type <nodeData> subprogram_head // 함수 정보
%type <intData> parameter_list // 함수 호출 파라미터 개수
%type <intData> arguments // 함수 호출 파라미터 개수
%type <intData> actual_parameter_expression // 식 개수
%type <intData> expression_list // 식 개수
%type <nodeData> procedure_statement // 함수 정보

%code requires {
	#include "yynode.h"
}

%union {
	char name[1024];
	int intData;
	float floatData;
	struct YYNode nodeData;
}

%%

program:
	MAINPROG ID ';' declarations subprogram_declarations compound_statement {}
;


declarations:
	type identifier_list ';' declarations {}
	|
;
identifier_list:
	ID { $$ = 1; }
	| ID ',' identifier_list { $$ = $3 + 1; }
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
	subprogram_head declarations compound_statement {
		YYNode node = $1;
		if (!findFromHashTable(&symbolTable, node.sParam[0])) {
			insertToHashTable(&symbolTable, node.sParam[0], node);
		}
		else {
			sprintf(buf, "identifier \"%s\" is declared duplicately", node.sParam[0]);
			yyerror(buf);
		}
	}
;
subprogram_head:
	FUNCTION ID arguments ':' standard_type ';' {
		YYNode node;
		node.type = T_FUNCTION;
		node.iParam[0] = $3; // 인자 개수
		strcpy(node.sParam[0], $2); // 함수 이름
		$$ = node;
	}
	| PROCEDURE ID arguments ';' {
		YYNode node;
		node.type = T_PROCEDURE;
		node.iParam[0] = $3; // 인자 개수
		strcpy(node.sParam[0], $2); // 프로시저 이름
		$$ = node;
	}
;
arguments:
	'(' parameter_list ')' { $$ = $2; }
	| { $$ = 0; }
;
parameter_list:
	identifier_list ':' type { $$ = $1; }
	| identifier_list ':' type ';' parameter_list { $$ = $1 + $5; }
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
	ID '(' actual_parameter_expression ')' {
		YYNode *nodePtr = findFromHashTable(&symbolTable, $1);
		if (nodePtr == NULL) {
			sprintf(buf, "undeclared identifier \"%s\"", $1);
			yyerror(buf);
			$$.type = T_NONE;
		}
		else if (nodePtr->type != T_FUNCTION && nodePtr->type != T_PROCEDURE) {
			sprintf(buf, "\"%s\" is not function or procedure", $1);
			yyerror(buf);
			$$.type = T_NONE;
		}
		else if (nodePtr->iParam[0] != $3) {
			sprintf(buf, "\"%s\" expect %d parameter, but %d given", $1, nodePtr->iParam[0], $3);
			yyerror(buf);
			$$ = *nodePtr;
		}
		else {
			$$ = *nodePtr;
		}
	}
;
actual_parameter_expression:
	expression_list { $$ = $1; }
	| { $$ = 0; }
;
expression_list:
	expression { $$ = 1; }
	| expression ',' expression_list { $$ = $3 + 1; }
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
	| procedure_statement {
		YYNode node = $1;
		if (node.type != T_NONE && node.type != T_FUNCTION) {
			sprintf(buf, "\"%s\" is not function so it doesn't have return value", node.sParam[0]);
			yyerror(buf);
		}
	}
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
	printf("Error: %s at line %d\n", s, yylineno);
	errorCount++;
	return 0;
}

void prepareParse() {
	symbolTable = createHashTable();
}

int main(int argc, char *argv[]) {
	if (argc == 2) {
		yyin = fopen(argv[1], "r");
		if (yyin) {
			prepareParse();
			if (yyparse() == 0) {
				if (errorCount == 0) {
					printf("[Compile OK]\n");
				}
				else {
					printf("[Compile Fail]\n");
				}
			}
			else {
				printf("[Compile Fail]\n");
			}
			fclose(yyin);
		}
		else {
			printf("Error: Can't open the file (%s)\n", argv[1]);
		}
	}
	else if (argc > 2) {
		printf("Error: Please enter only one argument\n");
	}
	else {
		printf("Error: Please enter source file name as command line argument\n");
	}
	return 0;
}
