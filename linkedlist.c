#include <stdio.h>
#include <stdlib.h>
#include "yynode.h"
#include "linkedlist.h"

List createList() {
    return NULL;
}

void appendToList(List *L, YYNode tdata) {
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = tdata;

    if (*L == NULL) {
        newNode->prev = newNode;
        newNode->next = newNode;
        *L = newNode;
    }
    else {
        (*L)->prev->next = newNode;
        newNode->prev = (*L)->prev;
        newNode->next = *L;
        (*L)->prev = newNode;
    }
}

void removeFromList(List *L, ListNode *node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    if (*L == node) {
        if (*L == node->next) *L = NULL;
        else *L = node->next;
    }
    free(node);
}

ListNode *nextNode(List L, ListNode *currentNode) {
    if (!currentNode || currentNode->next == L) {
        return NULL;
    }
    return currentNode->next;
}

ListNode *prevNode(List L, ListNode *currentNode) {
    if (!currentNode || currentNode == L) {
        return NULL;
    }
    return currentNode->prev;
}

size_t lengthOfList(List L) {
    size_t result = 0;
    List head = L;

    if (L == NULL) {
        return 0;
    }

    do {
        L = L->next;
        result++;
    } while (L != head);

    return result;
}
