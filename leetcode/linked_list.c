#include <stdlib.h>
#include <stdbool.h>
#include "alg_linked_list.h"

/* Solution for leetcode problem: https://leetcode.cn/problems/partition-list/description/ */
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode headerSmall = {0}, headerBig = {0};
    struct ListNode *listSmall = &headerSmall, *listBig = &headerBig, *p = head;

    while (p != NULL) {
        if (p->val < x) {
            listSmall->next = p;
            listSmall = p;
            p = p->next;
            listSmall->next = NULL;
        } else {
            listBig->next = p;
            listBig = p;
            p = p->next;
            listBig->next = NULL;
        }
    }

    if (headerSmall.next == NULL) {
        return headerBig.next;
    } else {
        listSmall->next = headerBig.next;
        return headerSmall.next;
    }
}

/* Solution for leetcode problem: https://leetcode.cn/problems/merge-k-sorted-lists/description/
 * The time complexity is O(n * log(k)), n is the total number of nodes, k is the number of lists.
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    int center = listsSize / 2;
    struct ListNode* result = NULL, *left, *right;

    if (listsSize == 0) {
        return NULL;
    } else if (listsSize == 1) {
        return *lists;
    }

    left = mergeKLists(lists, center);    // Merge the left half of the lists, make it sorted.
    right = mergeKLists(&lists[center], listsSize - center);    // Merge the right half of the lists, make it sorted.
    result = mergeTwoLists(left, right);    // Merge the left and right half of the lists.

    return result;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/ */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode *target, *preTarget;

    preTarget = findNthFromEnd(head, n + 1);
    target = findNthFromEnd(head, n);

    if (target == NULL) {    // Doesn't find the target node, do nothing.
        return head;
    } else if (preTarget == NULL) {    // preTarget == NULL means the target is the head node.
        head = target->next;
    } else {
        preTarget->next = target->next;
    }

    target->next = NULL;
    free(target);
    return head;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/middle-of-the-linked-list/description/ */
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode* slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/linked-list-cycle/description/ */
bool hasCycle(struct ListNode *head) {
    struct ListNode* slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }

    return false;
}

/* Solution for leetcode problem: https://leetcode-cn.com/problems/linked-list-cycle-ii/description/ */
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode* slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            break;
    }

    if (fast == NULL || fast->next == NULL)
        return NULL;

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}