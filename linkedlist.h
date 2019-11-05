#pragma once

#include <stdio.h>
#include "yynode.h"

typedef struct ListNode {
    YYNode data;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef ListNode *List;

List createList();
void concatList(List *dest, List addList);
void appendToList(List *L, YYNode tdata);
void removeFromList(List *L, ListNode *node);
ListNode *nextNode(List L, ListNode *currentNode);
ListNode *prevNode(List L, ListNode *currentNode);
size_t lengthOfList(List L);
