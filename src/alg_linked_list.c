#include <stdlib.h>
#include "alg_linked_list.h"

void freeLinkedList(struct ListNode* list)
{
    struct ListNode *p = list, *q = NULL;

    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
}

struct ListNode* constructLinkedList(int *data, int size)
{
    struct ListNode header = {0}, *p = NULL;

    if (data == NULL || size == 0) {
        return NULL;
    }

    p = &header;
    for (int i = 0; i < size; ++i) {
        p->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        if (p->next == NULL) {
            freeLinkedList(header.next);
            return NULL;
        }
        p = p->next;
        p->val = data[i];
        p->next = NULL;
    }

    return header.next;
}

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
    struct ListNode *p1 = list1, *p2 = list2;
    struct ListNode header = {0}, *p = NULL;

    p = &header;
    if (list1 == NULL && list2 == NULL) {
        return NULL;
    }

    if (list1 == NULL) {
        return list2;
    } else if (list2 == NULL) {
        return list1;
    }

    while (p1 != NULL && p2 != NULL) {
        if (p1->val < p2->val) {
            p->next = p1;
            p = p1;
            p1 = p1->next;
        } else {
            p->next = p2;
            p = p2;
            p2 = p2->next;
        }
    }

    if (p1 == NULL) {
        p->next = p2;
    } else {
        p->next = p1;
    }

    return header.next;
}

struct ListNode* findNthFromEnd(struct ListNode* head, int n)
{
    struct ListNode *p1 = head, *p2 = head;

    if (n < 0) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        if (p1 == NULL) {
            return NULL;
        }
        p1 = p1->next;
    }

    while (p1 != NULL) {
        p1 = p1->next;
        p2 = p2->next;
    }

    return p2;
}