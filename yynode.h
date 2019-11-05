#pragma once

typedef enum YYNodeType {
    T_NONE,
    T_FUNCTION = -70770770,
    T_PROCEDURE,
    T_VAR,
    T_ARRAY
} YYNodeType;

typedef struct YYNode {
    enum YYNodeType type;
    int iParam[8];
    char sParam[8][1024];
    void *rParam[8];
} YYNode;
