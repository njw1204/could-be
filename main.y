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
HashTable tempVarTable;
int debugVal = 0;
char buf[4096] = {0};
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

%type <nodeList> declarations // 선언한 변수 목록
%type <nodeList> identifier_list // 식별자 목록
%type <intData> type // 변수 자료형 (T_VAR or 배열 크기)
%type <nodeList> subprogram_declarations;
%type <nodeData> subprogram_declaration;
%type <nodeData> subprogram_head // 함수 정보
%type <nodeList> parameter_list // 함수 호출 파라미터 목록
%type <nodeList> arguments // 함수 호출 파라미터 목록
%type <nodeData> procedure_statement // 함수 정보

%type <nodeData> compound_statement;
%type <nodeList> statement_list;
%type <nodeData> statement;

%type <nodeData> variable;

%type <nodeList> actual_parameter_expression
%type <nodeList> expression_list
%type <nodeData> expression;
%type <nodeData> in_expression;
%type <nodeList> simple_expression;
%type <nodeList> term;
%type <nodeData> factor;

%code requires {
	#include "yynode.h"
	#include "linkedlist.h"
}

%union {
	char name[1024];
	int intData;
	float floatData;
	struct YYNode nodeData;
	List nodeList;
}

%%

program:
	MAINPROG ID ';' declarations subprogram_declarations compound_statement {
	}
;


declarations:
	type identifier_list ';' declarations {
		$$ = $4;
		ListNode *curr = $2;
		while (curr) {
			if ($1 == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = $1;
			}
			appendToList(&($$), curr->data);
			curr = nextNode($2, curr);
		}
	}
	| {
		$$ = createList();
	}
;
identifier_list:
	ID {
		$$ = createList();
		YYNode node = {0};
		node.type = T_ID;
		node.iParam[0] = yylineno;
		strcpy(node.sParam[0], $1);
		appendToList(&($$), node);
	}
	| ID ',' identifier_list {
		$$ = $3;
		YYNode node = {0};
		node.type = T_ID;
		node.iParam[0] = yylineno;
		strcpy(node.sParam[0], $1);
		appendToList(&($$), node);
	}
;


type:
	standard_type {
		$$ = T_VAR;
	}
	| standard_type '[' INTEGER ']' {
		$$ = $3;
		if ($3 < 1) {
			sprintf(buf, "array must have positive size");
			yyerror(buf);
		}
	}
;
standard_type:
	TYPE_INT | TYPE_FLOAT
;


subprogram_declarations:
	subprogram_declaration subprogram_declarations {
		$$ = createList();
		appendToList(&($$), $1);
		concatList(&($$), $2);
	}
	| { $$ = createList(); }
;
subprogram_declaration:
	subprogram_head declarations compound_statement {
		YYNode ret = {0};
		$$ = ret;
		$$.type = T_SUBPROGRAM_DECL;

		if (!findFromHashTable(&symbolTable, $1.sParam[0])) {
			insertToHashTable(&symbolTable, $1.sParam[0], $1);
			$$.rParam[0] = $2; // 지역변수 목록
			$$.rParam[1] = $1.rParam[0]; // 매개변수 목록
		}
		else {
			sprintf(buf, "identifier \"%s\" is declared duplicately", $1.sParam[0]);
			yyerror(buf);
		}
	}
;
subprogram_head:
	FUNCTION ID arguments ':' standard_type ';' {
		YYNode node;
		node.type = T_FUNCTION;
		node.iParam[0] = yylineno;
		node.iParam[1] = lengthOfList($3); // 인자 개수
		node.rParam[0] = $3; // 매개변수 목록
		strcpy(node.sParam[0], $2); // 함수 이름
		$$ = node;
	}
	| PROCEDURE ID arguments ';' {
		YYNode node;
		node.type = T_PROCEDURE;
		node.iParam[0] = yylineno;
		node.iParam[1] = lengthOfList($3); // 인자 개수
		node.rParam[0] = $3; // 매개변수 목록
		strcpy(node.sParam[0], $2); // 프로시저 이름
		$$ = node;
	}
;
arguments:
	'(' parameter_list ')' { $$ = $2; }
	| { $$ = createList(); }
;
parameter_list:
	identifier_list ':' type {
		ListNode *curr = $1;
		while (curr) {
			if ($3 == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = $3;
			}
			curr = nextNode($1, curr);
		}
		$$ = $1;
	}
	| identifier_list ':' type ';' parameter_list {
		ListNode *curr = $1;
		while (curr) {
			if ($3 == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = $3;
			}
			curr = nextNode($1, curr);
		}
		$$ = $1;
		concatList(&($$), $5);
	}
;


compound_statement:
	BEGIN_BODY statement_list END_BODY {
		$$.type = T_COMPOUND;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = $2;
	}
;
statement_list:
	statement {
		$$ = createList();
		appendToList(&($$), $1);
	}
	| statement ';' statement_list {
		$$ = createList();
		appendToList(&($$), $1);
		concatList(&($$), $3);
	}
;
statement:
	variable '=' expression {
		$$.type = T_ASSIGN;
		$$.iParam[0] = yylineno;

		List tempList = createList();
		appendToList(&tempList, $1);
		$$.rParam[0] = tempList;
		tempList = createList();
		appendToList(&tempList, $3);
		$$.rParam[1] = tempList;
	}
	| print_statement {}
	| procedure_statement {}
	| compound_statement { $$ = $1; }
	| if_statement {}
	| while_statement {}
	| for_statement {}
	| RETURN expression {
		$$.type = T_RETURN;
		$$.iParam[0] = yylineno;

		List tempList = createList();
		appendToList(&tempList, $2);
		$$.rParam[0] = tempList;
	}
	| NOP { $$.type = T_NONE; }
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
	ID {
		$$.type = T_VAR;
		$$.iParam[0] = yylineno;
		strcpy($$.sParam[0], $1);
	}
	| ID '[' expression ']' {
		$$.type = T_ARRAY;
		$$.iParam[0] = yylineno;
		strcpy($$.sParam[0], $1);
	}
;


procedure_statement:
	ID '(' actual_parameter_expression ')' {
		YYNode *nodePtr = findFromHashTable(&symbolTable, $1);
		int paraLen = lengthOfList($3);

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
		else if (nodePtr->iParam[1] != paraLen) {
			sprintf(buf, "\"%s\" expect %d parameter, but %d given", $1, nodePtr->iParam[1], paraLen);
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
	| { $$ = createList(); }
;
expression_list:
	expression {
		$$ = createList();
		appendToList(&($$), $1);
	}
	| expression ',' expression_list {
		$$ = createList();
		appendToList(&($$), $1);
		concatList(&($$), $3);
	}
;


expression:
	simple_expression {
		$$.type = T_SIMPLE_EXPR;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = $1;
	}
	| in_expression { $$ = $1; }
	| simple_expression relop simple_expression {
		$$.type = T_RELOP_EXPR;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = $1;
		$$.rParam[1] = $3;
	}
;
in_expression:
	simple_expression IN simple_expression {
		int llistLen = lengthOfList($1), rlistLen = lengthOfList($3);
		if (rlistLen > 1) {
			sprintf(buf, "expect l-value on the right side of \"in\", but r-value given");
			yyerror(buf);
		}
		else {
			ListNode rNode = *($3);
			if (rNode.data.type != T_VAR) {
				sprintf(buf, "expect l-value on the right side of \"in\", but r-value given");
				yyerror(buf);
			}
		}

		$$.type = T_IN_EXPR;
		$$.iParam[0] = yylineno;

		if (llistLen > 1) {
			$$.iParam[1] = 2; // left r-value
		}
		else {
			ListNode lNode = *($1);
			if (lNode.data.type == T_VAR || lNode.data.type == T_ARRAY) {
				$$.iParam[1] = 1; // left l-value
			}
			else {
				$$.iParam[1] = 2; // left r-value
			}
		}

		$$.rParam[0] = $1; // left list
		$$.rParam[1] = $3; // right list
	}
;
simple_expression:
	term { $$ = $1; }
	| term addop simple_expression {
		$$ = $1;
		concatList(&($$), $3);
	}
;
term:
	factor {
		$$ = createList();
		appendToList(&($$), $1);
	}
	| factor multop term {
		$$ = createList();
		appendToList(&($$), $1);
		concatList(&($$), $3);
	}
;
factor:
	INTEGER {
		$$.type = T_CONST;
		$$.iParam[0] = yylineno;
		$$.iParam[1] = $1;
	}
	| FLOAT {
		$$.type = T_CONST;
		$$.iParam[0] = yylineno;
		$$.iParam[1] = $1;
	}
	| variable {
		$$ = $1;
	}
	| procedure_statement {
		YYNode node = $1;
		if (node.type != T_NONE && node.type != T_FUNCTION) {
			sprintf(buf, "\"%s\" is not function so it doesn't have return value", node.sParam[0]);
			yyerror(buf);
		}
		$$.type = T_OTHER;
		$$.iParam[0] = yylineno;
	}
	| '!' factor {
		$$.iParam[0] = yylineno;
		if ($2.type == T_CONST) {
			$$.type = T_CONST;
			if ($2.iParam[1]) {
				$$.iParam[1] = 0;
			}
			else {
				$$.iParam[1] = 1;
			}
		}
		else {
			$$.type = T_OTHER;
		}
	}
	| sign factor {
		$$.iParam[0] = yylineno;
		if ($2.type == T_CONST) {
			$$.type = T_CONST;
			$$.iParam[1] = -$2.iParam[1];
		}
		else {
			$$.type = T_OTHER;
		}
	}
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
