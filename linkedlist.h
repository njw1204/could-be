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
void appendToList(List *L, YYNode tdata);
ListNode *nextNode(List L, ListNode *currentNode);
ListNode *prevNode(List L, ListNode *currentNode);
size_t lengthOfList(List L);
