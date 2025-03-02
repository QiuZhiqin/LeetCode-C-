#ifndef __ALG_LINKED_LIST_H
#define __ALG_LINKED_LIST_H

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNodeStru;

void freeLinkedList(struct ListNode *list);
struct ListNode* constructLinkedList(int *data, int size);
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2);
struct ListNode* findNthFromEnd(struct ListNode* head, int n);

#endif