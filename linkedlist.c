#include <stdio.h>
#include <stdlib.h>
#include "yynode.h"
#include "linkedlist.h"

List createList() {
    return NULL;
}

void concatList(List *dest, List addList) {
    ListNode *curr = addList;
    while (curr) {
        appendToList(dest, curr->data);
        curr = nextNode(addList, curr);
    }
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

void sortList(List L) {
    if (L == NULL) return;

    int len = lengthOfList(L);
    for (int i = len - 1; i >= 1; i--) {
        ListNode* prev = L;
        for (int j = 0; j < i; j++) {
            ListNode* next = prev->next;

            if (prev->data.iParam[0] > next->data.iParam[0]) {
                // swap data
                ListNode temp = *prev;
                prev->data = next->data;
                next->data = temp.data;
            }

            prev = next;
            next = next->next;
        }
    }
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
