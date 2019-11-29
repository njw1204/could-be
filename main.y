%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
int yylex();
int yyerror(char *s);
int _yyerror(char *s, int yylineno);
void prepareParse();
YYNode *findVariable(const char *name);
int checkUndeclaredVar(YYNode *_node);
int checkUndeclaredFunc(YYNode *_node);
void checkStatement(YYNode *_node, int allowCompound);
void checkExpression(YYNode *_node);
void checkSimpleExpression(YYNode *_node, int canArrayInExpr);
extern int yylineno;

#define L_VALUE 1
#define R_VALUE 2
const YYNode ZERO_NODE = {0}; // 0 초기화용 상수 노드

FILE *yyin; // 소스 파일을 입력받는 스트림
int errorCount = 0; // 에러 개수를 세는 변수
List errorList = NULL; // 에러 내용을 전부 저장하는 링크드 리스트
HashTable symbolTable; // 함수, 프로시저를 저장하는 해시테이블
HashTable globalVarTable; // 전역 변수를 저장하는 해시테이블
HashTable paramSymbolTable; // 매개 변수를 저장하는 해시테이블
HashTable localSymbolTable; // 지역 변수를 저장하는 해시테이블
int found_return = 0; // return문을 만나는 순간 1로 설정됨. (함수 내부에 return문 존재하나 체크하는 용도)
char buf[BUF_SIZE] = {0}; // 에러 출력용으로 사용하는 버퍼
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
		// 전역변수 선언
		List globalVarList = $4;
		for (ListNode *curr = globalVarList; curr; curr = nextNode(globalVarList, curr)) {
			if (curr->data.type == T_NONE) continue;

			if (curr->data.type == T_ARRAY && curr->data.iParam[1] < 1) {
				sprintf(buf, "array \"%s\" has zero size", curr->data.sParam[0]);
				_yyerror(buf, curr->data.iParam[0]);
				continue;
			}

			if (!findFromHashTable(&globalVarTable, curr->data.sParam[0])) {
				insertToHashTable(&globalVarTable, curr->data.sParam[0], curr->data);
			}
			else {
				// 중복 전역변수 선언 - 오류 처리
				sprintf(buf, "global variable \"%s\" is declared duplicately", curr->data.sParam[0]);
				_yyerror(buf, curr->data.iParam[0]);
			}
		}

		// 서브 루틴 선언
		List subProcList = $5;
		for (ListNode *curr = subProcList; curr; curr = nextNode(subProcList, curr)) {
			if (curr->data.type == T_NONE) continue;

			paramSymbolTable = createHashTable();
			localSymbolTable = createHashTable();

			YYNode sumProcHead = *((YYNode*)curr->data.rParam[0]);
			List paramVarList = sumProcHead.rParam[0];
			List localVarList = curr->data.rParam[1];
			YYNode compound = *((YYNode*)curr->data.rParam[2]);

			// 서브 루틴 이름 등록
			char *name = sumProcHead.sParam[0];
			if (!findFromHashTable(&globalVarTable, name)) {
				if (!findFromHashTable(&symbolTable, name)) {
					insertToHashTable(&symbolTable, name, sumProcHead);
				}
				else {
					// 중복 서브 루틴 선언 - 오류 처리
					sprintf(buf, "subprogram \"%s\" is declared duplicately", name);
					_yyerror(buf, sumProcHead.iParam[0]);
					continue;
				}
			}
			else {
				// 서브 루틴과 같은 이름의 전역변수 발견 - 오류 처리
				sprintf(buf, "subprogram \"%s\" has the same name as a declared global variable", name);
				_yyerror(buf, sumProcHead.iParam[0]);
				continue;
			}

			// 매개변수 처리
			for (ListNode *i = paramVarList; i; i = nextNode(paramVarList, i)) {
				if (i->data.type == T_NONE) continue;

				if (!findFromHashTable(&paramSymbolTable, i->data.sParam[0])) {
					insertToHashTable(&paramSymbolTable, i->data.sParam[0], i->data);
				}
				else {
					// 중복 매개변수 선언 - 오류 처리
					sprintf(buf, "param variable \"%s\" is declared duplicately", i->data.sParam[0]);
					_yyerror(buf, i->data.iParam[0]);
				}
			}

			// 지역변수 처리
			for (ListNode *i = localVarList; i; i = nextNode(localVarList, i)) {
				if (i->data.type == T_NONE) continue;

				if (!findFromHashTable(&localSymbolTable, i->data.sParam[0])) {
					insertToHashTable(&localSymbolTable, i->data.sParam[0], i->data);
				}
				else {
					// 중복 지역변수 선언 - 오류 처리
					sprintf(buf, "local variable \"%s\" is declared duplicately", i->data.sParam[0]);
					_yyerror(buf, i->data.iParam[0]);
				}
			}

			// 서브루틴 body 코드 검증
			List bodyStmtList = compound.rParam[0];
			found_return = 0;
			for (ListNode *i = bodyStmtList; i; i = nextNode(bodyStmtList, i)) {
				checkStatement(&(i->data), 0);
			}

			if (found_return == 0 && sumProcHead.type == T_FUNCTION) {
				// 함수인데 리턴문이 없는 오류 - 오류 처리
				sprintf(buf, "function \"%s\" doesn't have return statement", name);
				_yyerror(buf, sumProcHead.iParam[0]);
			}
			else if (found_return > 0 && sumProcHead.type == T_PROCEDURE) {
				// 프로시저인데 리턴문이 있는 오류 - 오류 처리
				sprintf(buf, "procedure \"%s\" has unexpected return statement", name);
				_yyerror(buf, sumProcHead.iParam[0]);
			}
		}

		// 프로그램 body 코드 검증
		paramSymbolTable = createHashTable();
		localSymbolTable = createHashTable();
		List bodyStmtList = $6.rParam[0];
		for (ListNode *curr = bodyStmtList; curr; curr = nextNode(bodyStmtList, curr)) {
			checkStatement(&(curr->data), 0);
		}
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
		node.sParam[0] = malloc(BUF_SIZE);
		strcpy(node.sParam[0], $1); // 식별자 이름
		appendToList(&($$), node);
	}
	| ID ',' identifier_list {
		$$ = createList();
		YYNode node = {0};
		node.type = T_ID;
		node.iParam[0] = yylineno;
		node.sParam[0] = malloc(BUF_SIZE);
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
		$$.rParam[0] = malloc(sizeof(YYNode));
		$$.rParam[2] = malloc(sizeof(YYNode));

		*((YYNode*)$$.rParam[0]) = $1; // 함수 시그니처 (nodeData)
		$$.rParam[1] = $2; // 지역변수 목록 (nodeList)
		*((YYNode*)$$.rParam[2]) = $3; // compound_statement (nodeData)
	}
;
subprogram_head:
	FUNCTION ID arguments ':' standard_type ';' {
		YYNode node;
		node.type = T_FUNCTION;
		node.iParam[0] = yylineno;
		node.iParam[1] = lengthOfList($3); // 매개변수 개수
		node.rParam[0] = $3; // 매개변수 목록 (nodeList)
		node.sParam[0] = malloc(BUF_SIZE);
		strcpy(node.sParam[0], $2); // 함수 이름
		$$ = node;
	}
	| PROCEDURE ID arguments ';' {
		YYNode node;
		node.type = T_PROCEDURE;
		node.iParam[0] = yylineno;
		node.iParam[1] = lengthOfList($3); // 매개변수 개수
		node.rParam[0] = $3; // 매개변수 목록 (nodeList)
		node.sParam[0] = malloc(BUF_SIZE);
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
		$$ = ZERO_NODE;
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
	| print_statement { $$ = $1; }
	| procedure_statement { $$ = $1; }
	| compound_statement { $$ = $1; }
	| if_statement { $$ = $1; }
	| while_statement { $$ = $1; }
	| for_statement { $$ = $1; }
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
		$$.sParam[0] = malloc(BUF_SIZE);
		strcpy($$.sParam[0], $1); // 식별자 이름
	}
	| ID '[' expression ']' {
		$$.type = T_ARRAY_USING;
		$$.iParam[0] = yylineno;
		$$.sParam[0] = malloc(BUF_SIZE);
		strcpy($$.sParam[0], $1); // 식별자 이름
	}
;


procedure_statement:
	ID '(' actual_parameter_expression ')' {
		$$ = ZERO_NODE;
		$$.type = T_CALL;

		int paraLen = lengthOfList($3);
		$$.iParam[0] = yylineno;
		$$.iParam[1] = paraLen;
		$$.sParam[0] = malloc(BUF_SIZE);
		strcpy($$.sParam[0], $1);
		$$.rParam[0] = $3;
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
		$$ = ZERO_NODE;
		$$.iParam[2] = L_VALUE; // right l-value

		int llistLen = lengthOfList($1.rParam[0]), rlistLen = lengthOfList($3.rParam[0]);
		if (rlistLen > 1) {
			// IN 우항은 무조건 l-value(배열) - 오류 처리
			sprintf(buf, "expect an array on the right side of \"in\", but an expression given");
			yyerror(buf);
			$$.iParam[2] = R_VALUE;
		}
		else {
			ListNode rNode = *((ListNode*)$3.rParam[0]);
			if (rNode.data.type != T_VAR_USING) {
				// IN 우항은 무조건 l-value(배열) - 오류 처리
				sprintf(buf, "expect an array on the right side of \"in\"");
				yyerror(buf);
				$$.iParam[2] = R_VALUE;
			}
		}

		$$.type = T_IN_EXPR;
		$$.iParam[0] = yylineno;

		if (llistLen > 1) {
			$$.iParam[1] = R_VALUE; // left r-value
		}
		else {
			ListNode lNode = *((ListNode*)$1.rParam[0]);
			if (lNode.data.type == T_VAR_USING || lNode.data.type == T_ARRAY_USING) {
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
		$$ = $1;
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
			$$ = $2;
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
			$$ = $2;
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

YYNode *findVariable(const char *name) {
	// 지역변수 -> 매개변수 -> 전역변수 순으로 찾는다
	YYNode *result = NULL;

	if ((result = findFromHashTable(&localSymbolTable, name)) ||
		(result = findFromHashTable(&paramSymbolTable, name)) ||
		(result = findFromHashTable(&globalVarTable, name))) {
		return result;
	}

	return NULL; // 선언하지 않은 변수
}

int checkUndeclaredVar(YYNode *_node) {
	if (!findVariable(_node->sParam[0])) {
		YYNode *temp = NULL;
		if (!(temp = findFromHashTable(&symbolTable, _node->sParam[0]))) {
			// 선언되지 않은 변수 - 오류 처리
			sprintf(buf, "undeclared variable \"%s\"", _node->sParam[0]);
			_yyerror(buf, _node->iParam[0]);
		}
		else {
			// 해당 식별자가 함수나 프로시저인 경우의 오류 (변수가 와야함) - 오류 처리
			if (temp->type == T_FUNCTION) {
				sprintf(buf, "\"%s\" is a function, not a variable", _node->sParam[0]);
				_yyerror(buf, _node->iParam[0]);
			}
			else {
				sprintf(buf, "\"%s\" is a procedure, not a variable", _node->sParam[0]);
				_yyerror(buf, _node->iParam[0]);
			}
		}
		return 0;
	}
	return 1;
}

int checkUndeclaredFunc(YYNode *_node) {
	if (!findFromHashTable(&symbolTable, _node->sParam[0])) {
		// 선언되지 않은 서브 루틴 - 오류 처리
		sprintf(buf, "undeclared subprogram \"%s\"", _node->sParam[0]);
		_yyerror(buf, _node->iParam[0]);
		return 0;
	}
	return 1;
}

void checkStatement(YYNode *_node, int allowCompound) {
	YYNode data = *_node;

	YYNode left, right, begin, end;
	List list;

	switch (data.type) {
	case T_ASSIGN:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);

		checkUndeclaredVar(&left);
		checkExpression(&right);

		YYNode *declLeft = findVariable(left.sParam[0]);
		if (declLeft) {
			if (left.type == T_VAR_USING && declLeft->type == T_ARRAY) {
				// 배열 전체에 직접 대입 - 오류 처리
				sprintf(buf, "can't assign data directly/entirely to the array \"%s\". please use an index", left.sParam[0]);
				_yyerror(buf, left.iParam[0]);
			}
			else if (left.type == T_ARRAY_USING && declLeft->type == T_VAR) {
				// 단일 변수에 배열처럼 인덱스 참조 - 오류 처리
				sprintf(buf, "can't indexing the single variable \"%s\"", left.sParam[0]);
				_yyerror(buf, left.iParam[0]);
			}
		}

		break;

	case T_IF:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);
		checkExpression(&left);
		checkStatement(&right, 1);
		break;

	case T_IF_ELSE:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);
		end = *((YYNode*)data.rParam[2]);
		checkExpression(&left);
		checkStatement(&right, 1);
		checkStatement(&end, 1);
		break;

	case T_IF_ELIF:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);
		list = data.rParam[2];
		checkExpression(&left);
		checkStatement(&right, 1);

		for (ListNode *curr = list; curr; curr = nextNode(list, curr)) {
			checkExpression(curr->data.rParam[0]);
			checkStatement(curr->data.rParam[1], 1);
		}
		break;

	case T_IF_ELIF_ELSE:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);
		list = data.rParam[2];
		end = *((YYNode*)data.rParam[3]);
		checkExpression(&left);
		checkStatement(&right, 1);

		for (ListNode *curr = list; curr; curr = nextNode(list, curr)) {
			checkExpression(curr->data.rParam[0]);
			checkStatement(curr->data.rParam[1], 1);
		}
		checkStatement(&end, 1);
		break;

	case T_WHILE_STMT:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);
		checkExpression(&left);
		checkStatement(&right, 1);
		break;

	case T_WHILE_ELSE_STMT:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);
		end = *((YYNode*)data.rParam[2]);
		checkExpression(&left);
		checkStatement(&right, 1);
		checkStatement(&end, 1);
		break;

	case T_FOR_STMT:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);
		checkExpression(&left);

		if (left.iParam[1] != L_VALUE) {
			// for 루프에서 쓰이는 in 문에서는 좌항에 L-Value가 필수임 - 오류 처리
			sprintf(buf, "expect l-value on the left side of \"in\" within for-loop, but r-value given");
			_yyerror(buf, left.iParam[0]);
		}

		checkStatement(&right, 1);
		break;

	case T_FOR_ELSE_STMT:
		left = *((YYNode*)data.rParam[0]);
		right = *((YYNode*)data.rParam[1]);
		end = *((YYNode*)data.rParam[2]);
		checkExpression(&left);

		if (left.iParam[1] != L_VALUE) {
			// for 루프에서 쓰이는 in 문에서는 좌항에 L-Value가 필수임 - 오류 처리
			sprintf(buf, "expect l-value on the left side of \"in\" within for-loop, but r-value given");
			_yyerror(buf, left.iParam[0]);
		}

		checkStatement(&right, 1);
		checkStatement(&end, 1);
		break;

	case T_PRINT_STMT:
		left = *((YYNode*)data.rParam[0]);
		checkExpression(&left);
		break;

	case T_RETURN:
		found_return = 1;
		left = *((YYNode*)data.rParam[0]);
		checkExpression(&left);
		break;

	case T_COMPOUND:
		if (!allowCompound) {
			// BEGIN~END문은 연속 중첩 불가능 (if, for문 등의 아래에 나와야 함) - 오류 처리
			sprintf(buf, "begin~end statement can't be nested directly under another begin~end statement");
			_yyerror(buf, data.iParam[0]);
		}

		list = data.rParam[0];
		for (ListNode *curr = list; curr; curr = nextNode(list, curr)) {
			checkStatement(&(curr->data), 0);
		}
		break;

	case T_CALL:
		if (!checkUndeclaredFunc(&data)) {
			break;
		}

		YYNode *declFunc = findFromHashTable(&symbolTable, data.sParam[0]);
		if (data.iParam[1] != declFunc->iParam[1]) {
			// 인자 개수 다름 - 오류 처리
			sprintf(buf, "\"%s\" expect %d parameter, but %d given", data.sParam[0], declFunc->iParam[1], data.iParam[1]);
			_yyerror(buf, data.iParam[0]);
		}
		break;

	}
}

void checkExpression(YYNode *_node) {
	if (_node->type == T_SIMPLE_EXPR) {
		checkSimpleExpression(_node, 0);
	}
	else if (_node->type == T_RELOP_EXPR || _node->type == T_IN_EXPR) {
		checkSimpleExpression(_node->rParam[0], 0);
		if (_node->type == T_RELOP_EXPR) {
			checkSimpleExpression(_node->rParam[1], 0);
		}
		else {
			checkSimpleExpression(_node->rParam[1], 1);
		}

		if (_node->type == T_IN_EXPR && _node->iParam[2] == L_VALUE) {
			ListNode rNode = *((ListNode*)_node->rParam[1]);
			YYNode *declVar = findVariable(rNode.data.sParam[0]);
			if (declVar && declVar->type == T_VAR) {
				// IN 오른쪽에 단일 변수 사용한 오류 (배열만 사용 가능) - 오류 처리
				sprintf(buf, "expect an array on the right side of \"in\", but a single variable \"%s\" given", rNode.data.sParam[0]);
				_yyerror(buf, rNode.data.iParam[0]);
			}
		}
	}
}

void checkSimpleExpression(YYNode *_node, int canArrayInExpr) {
	List terms = _node->rParam[0];
	for (ListNode *curr = terms; curr; curr = nextNode(terms, curr)) {
		YYNode *data = &(curr->data);
		YYNode *declVar;

		switch (data->type) {
		case T_VAR_USING:
			if (!checkUndeclaredVar(data)) {
				break;
			}

			declVar = findVariable(data->sParam[0]);
			if (!canArrayInExpr && declVar->type == T_ARRAY) {
				// 배열 전체를 인덱스 참조 없이 단일 변수처럼 사용한 오류 - 오류 처리
				sprintf(buf, "can't reference the array \"%s\" directly/entirely here. please use an index", data->sParam[0]);
				_yyerror(buf, data->iParam[0]);
			}
			break;

		case T_ARRAY_USING:
			if (!checkUndeclaredVar(data)) {
				break;
			}

			declVar = findVariable(data->sParam[0]);
			if (declVar->type == T_VAR) {
				// 단일 변수를 배열처럼 인덱스 참조한 오류 - 오류 처리
				sprintf(buf, "can't indexing the single variable \"%s\"", data->sParam[0]);
				_yyerror(buf, data->iParam[0]);
			}
			break;

		case T_CALL:
			if (!checkUndeclaredFunc(data)) {
				break;
			}

			YYNode *declFunc = findFromHashTable(&symbolTable, data->sParam[0]);
			if (declFunc->type != T_FUNCTION) {
				// function이 아님. 리턴값이 없어 expression에서 사용 불가능 - 오류 처리
				sprintf(buf, "\"%s\" is not function so it doesn't have return value", data->sParam[0]);
				_yyerror(buf, data->iParam[0]);
			}

			if (data->iParam[1] != declFunc->iParam[1]) {
				// 인자 개수 다름 - 오류 처리
				sprintf(buf, "\"%s\" expect %d parameter, but %d given", data->sParam[0], declFunc->iParam[1], data->iParam[1]);
				_yyerror(buf, data->iParam[0]);
			}
			break;
		}
	}
}

int yyerror(char *s) {
	return _yyerror(s, yylineno);
}

int _yyerror(char *s, int yylineno) {
	YYNode node = {0};
	node.type = T_ERROR;
	node.iParam[0] = yylineno;
	node.sParam[0] = malloc(BUF_SIZE);
	strcpy(node.sParam[0], s);
	appendToList(&(errorList), node);
	errorCount++;
	return 0;
}

void printAllError() {
	sortList(errorList);
	ListNode *curr = errorList;

	while (curr) {
		if (curr->data.type == T_ERROR) {
			if (strstr(curr->data.sParam[0], "$undefined")) {
				printf("Error (line %d) : syntax error, found unknown character while parsing\n", curr->data.iParam[0]);
			}
			else if (strstr(curr->data.sParam[0], "$end")) {
				printf("Error (line %d) : syntax error, reached end of file while parsing\n", curr->data.iParam[0]);
			}
			else {
				printf("Error (line %d) : %s\n", curr->data.iParam[0], curr->data.sParam[0]);
			}
		}

		ListNode *temp = curr;
		curr = nextNode(errorList, curr);
		removeFromList(&(errorList), temp);
	}
}

void prepareParse() {
	symbolTable = createHashTable();
	globalVarTable = createHashTable();
	paramSymbolTable = createHashTable();
	localSymbolTable = createHashTable();
}

int main(int argc, char *argv[]) {
	if (argc == 2) {
		yyin = fopen(argv[1], "r");
		if (yyin) {
			prepareParse();
			int parsed = yyparse();
			printAllError();
			if (parsed == 0) {
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
