#pragma once

typedef enum YYNodeType {
    T_NONE,
    T_ID,
    T_FUNCTION = -70770770,
    T_PROCEDURE,
    T_SUBPROGRAM_DECL,
    T_FUNCTION_CALL,
    T_VAR,
    T_ARRAY,
    T_CONST,
    T_COMPOUND,
    T_ASSIGN,
    T_RETURN,
    T_IN_EXPR,
    T_SIMPLE_EXPR,
    T_RELOP_EXPR,
    T_OTHER
} YYNodeType;

typedef struct YYNode {
    enum YYNodeType type;
    int iParam[8];
    char sParam[8][1024];
    void *rParam[8];
} YYNode;
