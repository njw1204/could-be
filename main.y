%{
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
int yylex();
int yyerror(char *s);
int _yyerror(char *s, int yylineno);
void prepareParse();
extern int yylineno;

#define L_VALUE 1
#define R_VALUE 2

int errorCount = 0;
FILE *yyin;
HashTable symbolTable;
HashTable tempVarTable;
int debugVal = 0;
char buf[4096] = {0};
const YYNode ZERO_NODE = {0};
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

%type <nodeData> if_statement;
%type <nodeList> elif_statement;
%type <nodeData> while_statement;
%type <nodeData> for_statement;
%type <nodeData> print_statement;

%type <nodeData> variable;

%type <nodeList> actual_parameter_expression
%type <nodeList> expression_list
%type <nodeData> expression;
%type <nodeData> in_expression;
%type <nodeData> simple_expression;
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
		$$ = $2;
		for (ListNode *curr = $2; curr; curr = nextNode($2, curr)) {
			if ($1 == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = $1; // 배열 길이
			}
		}
		concatList(&($$), $4);
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
		strcpy(node.sParam[0], $1); // 식별자 이름
		appendToList(&($$), node);
	}
	| ID ',' identifier_list {
		$$ = createList();
		YYNode node = {0};
		node.type = T_ID;
		node.iParam[0] = yylineno;
		strcpy(node.sParam[0], $1); // 식별자 이름
		appendToList(&($$), node);
		concatList(&($$), $3);
	}
;


type:
	standard_type {
		$$ = T_VAR;
	}
	| standard_type '[' INTEGER ']' {
		$$ = $3;  // 배열 길이
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
		$$ = ZERO_NODE;
		$$.type = T_SUBPROGRAM_DECL;
		$$.iParam[0] = yylineno;

		if (!findFromHashTable(&symbolTable, $1.sParam[0])) {
			insertToHashTable(&symbolTable, $1.sParam[0], $1);
			$$.rParam[0] = malloc(sizeof(YYNode));
			$$.rParam[2] = malloc(sizeof(YYNode));

			*((YYNode*)$$.rParam[0]) = $1; // 함수 시그니처 (nodeData)
			$$.rParam[1] = $2; // 지역변수 목록 (nodeList)
			*((YYNode*)$$.rParam[2]) = $3; // compound_statement (nodeData)
		}
		else {
			sprintf(buf, "identifier \"%s\" is declared duplicately", $1.sParam[0]);
			_yyerror(buf, $1.iParam[0]);
		}
	}
;
subprogram_head:
	FUNCTION ID arguments ':' standard_type ';' {
		YYNode node;
		node.type = T_FUNCTION;
		node.iParam[0] = yylineno;
		node.iParam[1] = lengthOfList($3); // 매개변수 개수
		node.rParam[0] = $3; // 매개변수 목록 (nodeList)
		strcpy(node.sParam[0], $2); // 함수 이름
		$$ = node;
	}
	| PROCEDURE ID arguments ';' {
		YYNode node;
		node.type = T_PROCEDURE;
		node.iParam[0] = yylineno;
		node.iParam[1] = lengthOfList($3); // 매개변수 개수
		node.rParam[0] = $3; // 매개변수 목록 (nodeList)
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
		$$ = $1;
		for (ListNode *curr = $1; curr; curr = nextNode($1, curr)) {
			if ($3 == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = $3; // 배열 길이
			}
		}
	}
	| identifier_list ':' type ';' parameter_list {
		$$ = $1;
		for (ListNode *curr = $1; curr; curr = nextNode($1, curr)) {
			if ($3 == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = $3; // 배열 길이
			}
		}
		concatList(&($$), $5);
	}
;


compound_statement:
	BEGIN_BODY statement_list END_BODY {
		$$.type = T_COMPOUND;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = $2; // statement_list (nodeList)
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
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $1; // variable (nodeData)
		*((YYNode*)$$.rParam[1]) = $3; // expression (nodeData)
	}
	| print_statement {$$ = $1;}
	| procedure_statement {$$ = $1;}
	| compound_statement { $$ = $1; }
	| if_statement {$$ = $1;}
	| while_statement {$$ = $1;}
	| for_statement {$$ = $1;}
	| RETURN expression {
		$$.type = T_RETURN;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // expression (nodeData)
	}
	| NOP {
		$$.type = T_NONE;
		$$.iParam[0] = yylineno;
	}
;


if_statement:
	IF expression ':' statement {
		$$ = ZERO_NODE;
		$$.type = T_IF;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // expression (nodeData)
		*((YYNode*)$$.rParam[1]) = $4; // statement (nodeData)
	}
	| IF expression ':' statement ELSE ':' statement {
		$$ = ZERO_NODE;
		$$.type = T_IF_ELSE;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));
		$$.rParam[2] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // expression (nodeData)
		*((YYNode*)$$.rParam[1]) = $4; // statement (nodeData)
		*((YYNode*)$$.rParam[2]) = $7; // else statement (nodeData)
	}
	| IF expression ':' statement elif_statement {
		$$ = ZERO_NODE;
		$$.type = T_IF_ELIF;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // expression (nodeData)
		*((YYNode*)$$.rParam[1]) = $4; // statement (nodeData)
		$$.rParam[2] = $5; // elif statement list (nodeList)
	}
	| IF expression ':' statement elif_statement ELSE ':' statement {
		$$ = ZERO_NODE;
		$$.type = T_IF_ELIF_ELSE;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));
		$$.rParam[3] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // expression (nodeData)
		*((YYNode*)$$.rParam[1]) = $4; // statement (nodeData)
		$$.rParam[2] = $5; // elif statement list (nodeList)
		*((YYNode*)$$.rParam[3]) = $8; // else statement (nodeData)
	}
;
elif_statement:
	ELIF expression ':' statement elif_statement {
		$$ = createList();

		YYNode node = {0};
		node.type = T_ELIF;
		node.iParam[0] = yylineno;
		node.rParam[0] = malloc(sizeof(YYNode));
		node.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)node.rParam[0]) = $2;
		*((YYNode*)node.rParam[1]) = $4;

		appendToList(&($$), node);
		concatList(&($$), $5);
	}
	| ELIF expression ':' statement {
		$$ = createList();

		YYNode node = {0};
		node.type = T_ELIF;
		node.iParam[0] = yylineno;
		node.rParam[0] = malloc(sizeof(YYNode));
		node.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)node.rParam[0]) = $2;
		*((YYNode*)node.rParam[1]) = $4;

		appendToList(&($$), node);
	}
;


while_statement:
	WHILE expression ':' statement {
		$$ = ZERO_NODE;
		$$.type = T_WHILE_STMT;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // expression (nodeData)
		*((YYNode*)$$.rParam[1]) = $4; // statement (nodeData)

	}
	| WHILE expression ':' statement ELSE ':' statement {
		$$ = ZERO_NODE;
		$$.type = T_WHILE_ELSE_STMT;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));
		$$.rParam[2] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // expression (nodeData)
		*((YYNode*)$$.rParam[1]) = $4; // statement (nodeData)
		*((YYNode*)$$.rParam[2]) = $7; // else statement (nodeData)
	}
;


for_statement:
	FOR in_expression ':' statement {
		$$ = ZERO_NODE;
		$$.type = T_FOR_STMT;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // in_expression (nodeData)
		*((YYNode*)$$.rParam[1]) = $4; // statement (nodeData)
	}
	| FOR in_expression ':' statement ELSE ':' statement {
		$$ = ZERO_NODE;
		$$.type = T_FOR_ELSE_STMT;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));
		$$.rParam[2] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $2; // expression (nodeData)
		*((YYNode*)$$.rParam[1]) = $4; // statement (nodeData)
		*((YYNode*)$$.rParam[2]) = $7; // else statement (nodeData)
	}
;


print_statement:
	PRINT {
		$$ = ZERO_NODE;
		$$.type = T_NONE;
		$$.iParam[0] = yylineno;
	}
	| PRINT '(' expression ')' {
		$$ = $3;
		$$.type = T_PRINT_STMT;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $3; // expression (nodeData)
	}
;


variable:
	ID {
		$$.type = T_VAR_USING;
		$$.iParam[0] = yylineno;
		strcpy($$.sParam[0], $1); // 식별자 이름
	}
	| ID '[' expression ']' {
		$$.type = T_ARRAY_USING;
		$$.iParam[0] = yylineno;
		strcpy($$.sParam[0], $1); // 식별자 이름
	}
;


procedure_statement:
	ID '(' actual_parameter_expression ')' {
		YYNode *nodePtr = findFromHashTable(&symbolTable, $1);
		int paraLen = lengthOfList($3);
		$$.iParam[0] = yylineno;

		if (nodePtr == NULL) {
			sprintf(buf, "undeclared identifier \"%s\"", $1);
			yyerror(buf);
			$$.type = T_FUNCTION_CALL;
		}
		else if (nodePtr->type != T_FUNCTION && nodePtr->type != T_PROCEDURE) {
			sprintf(buf, "\"%s\" is not function or procedure", $1);
			yyerror(buf);
			$$.type = T_FUNCTION_CALL;
		}
		else if (nodePtr->iParam[1] != paraLen) {
			sprintf(buf, "\"%s\" expect %d parameter, but %d given", $1, nodePtr->iParam[1], paraLen);
			yyerror(buf);
			$$.type = T_FUNCTION_CALL;
		}
		else {
			if (nodePtr->type == T_FUNCTION) $$.type = T_FUNCTION_CALL;
			else $$.type = T_PROCEDURE_CALL;
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
		$$ = $1;

		// $$.type = T_SIMPLE_EXPR;
		// $$.iParam[0] = yylineno;
		// $$.rParam[0] = $1;
	}
	| in_expression { $$ = $1; }
	| simple_expression relop simple_expression {
		$$.type = T_RELOP_EXPR;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $1; // left simple_expression
		*((YYNode*)$$.rParam[1]) = $3; // right simple_expression

		// $$.rParam[0] = $1;
		// $$.rParam[1] = $3;
	}
;
in_expression:
	simple_expression IN simple_expression {
		int llistLen = lengthOfList($1.rParam[0]), rlistLen = lengthOfList($3.rParam[0]);
		if (rlistLen > 1) {
			sprintf(buf, "expect l-value on the right side of \"in\", but r-value given");
			yyerror(buf);
		}
		else {
			ListNode rNode = *((ListNode*)$3.rParam[0]);
			if (rNode.data.type != T_VAR_USING) {
				sprintf(buf, "expect l-value on the right side of \"in\", but r-value given");
				yyerror(buf);
			}
		}

		$$.type = T_IN_EXPR;
		$$.iParam[0] = yylineno;

		if (llistLen > 1) {
			$$.iParam[1] = R_VALUE; // left r-value
		}
		else {
			ListNode lNode = *((ListNode*)$1.rParam[0]);
			if (lNode.data.type == T_VAR || lNode.data.type == T_ARRAY) {
				$$.iParam[1] = L_VALUE; // left l-value
			}
			else {
				$$.iParam[1] = R_VALUE; // left r-value
			}
		}

		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[1] = malloc(sizeof(YYNode));
		*((YYNode*)$$.rParam[0]) = $1; // simple_expression, left node
		*((YYNode*)$$.rParam[1]) = $3; // simple_expression, right node
	}
;
simple_expression:
	term {
		$$.type = T_SIMPLE_EXPR;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = $1; // term (nodeList)
	}
	| term addop simple_expression {
		$$.type = T_SIMPLE_EXPR;
		$$.iParam[0] = yylineno;
		$$.rParam[0] = $1; // term (only include operands, nodeList)

		List temp = $$.rParam[0];
		concatList(&temp, $3.rParam[0]); // append another term (nodeList)
		$$.rParam[0] = temp;
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
		$$ = ZERO_NODE;
		$$.type = T_CONST_INTEGER;
		$$.iParam[0] = yylineno;
		$$.iParam[1] = $1; // value
	}
	| FLOAT {
		$$ = ZERO_NODE;
		$$.type = T_CONST_FLOAT;
		$$.iParam[0] = yylineno;
		$$.fParam[1] = $1; // value
	}
	| variable {
		$$ = $1; // variable (nodeData, type : T_VAR_USING or T_ARRAY_USING)
	}
	| procedure_statement {
		if ($1.type == T_PROCEDURE_CALL) {
			sprintf(buf, "\"%s\" is not function so it doesn't have return value", $1.sParam[0]);
			yyerror(buf);
		}
		$$.type = T_DYNAMIC_FACTOR;
		$$.iParam[0] = yylineno;
	}
	| '!' factor {
		$$.iParam[0] = yylineno;
		if ($2.type == T_CONST_INTEGER || $2.type == T_CONST_FLOAT) {
			$$.type = $2.type;

			if ($2.iParam[1]) $$.iParam[1] = 0;
			else $$.iParam[1] = 1;

			if ($2.fParam[1]) $$.fParam[1] = 0;
			else $$.fParam[1] = 1;
		}
		else {
			$$.type = T_DYNAMIC_FACTOR;
		}
	}
	| sign factor {
		$$.iParam[0] = yylineno;
		if ($2.type == T_CONST_INTEGER || $2.type == T_CONST_FLOAT) {
			$$.type = $2.type;
			$$.iParam[1] = -$2.iParam[1];
			$$.fParam[1] = -$2.fParam[1];
		}
		else {
			$$.type = T_DYNAMIC_FACTOR;
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
	_yyerror(s, yylineno);
}

int _yyerror(char *s, int yylineno) {
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
