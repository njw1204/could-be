#pragma once

typedef enum YYNodeType {
    T_NONE = 0,
    T_FUNCTION,
    T_PROCEDURE
} YYNodeType;

typedef struct YYNode {
    enum YYNodeType type;
    int iParam[8];
    char sParam[8][1024];
} YYNode;
