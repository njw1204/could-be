#pragma once

typedef enum YYNodeType {
    T_NONE,
    T_ID,
    T_FUNCTION = -70770770,
    T_PROCEDURE,
    T_SUBPROGRAM_DECL,
    T_FUNCTION_CALL,
    T_PROCEDURE_CALL,
    T_VAR,
    T_ARRAY,
    T_CONST_INTEGER,
    T_CONST_FLOAT,
    T_COMPOUND,
    T_IF,
    T_IF_ELSE,
    T_IF_ELIF,
    T_IF_ELIF_ELSE,
    T_ELIF,
    T_ASSIGN,
    T_RETURN,
    T_IN_EXPR,
    T_SIMPLE_EXPR,
    T_RELOP_EXPR,
    T_VAR_USING,
    T_ARRAY_USING,
    T_DYNAMIC_FACTOR,
    T_OTHER
} YYNodeType;

typedef struct YYNode {
    enum YYNodeType type;
    int iParam[8];
    float fParam[8];
    char sParam[8][1024];
    void *rParam[8];
} YYNode;
