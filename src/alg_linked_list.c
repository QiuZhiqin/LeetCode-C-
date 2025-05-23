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

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* pre = NULL, *cur = head, *next = NULL;
    if (head == NULL || head->next == NULL) {
        return head;
    }

    while (cur != NULL) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }

    return pre;
}

struct ListNode* sortList(struct ListNode* head) {
    struct ListNode *p = head, *q = NULL, dummyHead = {0}, *prev = NULL, *cur = NULL, *next = NULL;
    int len = 0, subLen = 1;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    while (p != NULL) {
        len++;
        p = p->next;
    }

    dummyHead.next = head;
    /* Merge two list with length of subLen each time, after reaverse the whole list, double subLen.
     * Repeat the above process until subLen is greater than or equal to len.
     */
    while (subLen < len) {
        cur = dummyHead.next;
        prev = &dummyHead;    // prev is the tail of the list that already merged.
        while (cur != NULL) {
            p = cur;    // p is the head of the first list.
            for (int i = 1; i < subLen && cur->next != NULL; i++) {    // Find the tail of the first list.
                cur = cur->next;
            }

            q = cur->next;    // q is the head of the second list.
            cur->next = NULL;    // Cut the first list out.
            cur = q;    // Move cur to the head of the second list.
            /* Find the tail of the second list */
            for (int i = 1; i < subLen && cur != NULL && cur->next != NULL; i++) {
                cur = cur->next;
            }

            next = NULL;
            if (cur != NULL) {
                next = cur->next;    // next is the head of the list that is waiting to merge in next loop.
                cur->next = NULL;
            }

            prev->next = mergeTwoLists(p, q);
            while (prev->next != NULL) {
                prev = prev->next;
            }
            cur = next;
        }
        subLen <<= 1;    // Double the subLen.
    }

    return dummyHead.next;
}