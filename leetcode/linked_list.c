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

/* Solution for leetcode problem: https://leetcode.cn/problems/intersection-of-two-linked-lists/description/
 * Lets say the length of listA, listB, non-intersected part of listA, non-intersected part of listB and intersected part are m, n, a, b, and c respectively.
   If the two lists is intersected, p1 will reach the end of listA after m steps, and p2 will reach the end of listB after n steps.
   When p1 reaches the end of listA, it will start to move on listB. After b steps on listB, p1 will meet p2, which moves b steps on listA after reaching the end of listB.
   The number of steps p1 moves is m + b = a + c + b = b + c + a = n + a, which is the number of steps p2 moves.
   And if the two lists are not intersected, the number of steps p1 moves will be m + n, which is the same as the number of steps p2 moves.
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *p1 = headA, *p2 = headB;

    if (p1 == NULL || p2 == NULL) {
        return NULL;
    }

    while (p1 != p2) {
        p1 = (p1 == NULL) ? headB : p1->next;
        p2 = (p2 == NULL) ? headA : p2->next;
    }

    return p1;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/remove-duplicates-from-sorted-list/description/ */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *p = head, *q = NULL;

    while (p != NULL) {
        while (p->next != NULL && p->val == p->next->val) {
            p = p->next;
        }
        if (q == NULL) {
            q = p;
            head = q;
        } else {
            q->next = p;
            q = p;
        }
        p = p->next;
    }

    return head;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/palindrome-linked-list/description/ */
bool isPalindrome(struct ListNode* head) {
    struct ListNode *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    fast = head;
    slow = reverseList(slow);
    while (slow != NULL) {
        if (slow->val != fast->val) {
            return false;
        }
        slow = slow->next;
        fast = fast->next;
    }

    return true;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/add-two-numbers/description/ */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *p1 = NULL, *p2 = NULL, *q = NULL, header = {0};
    int carry = 0, sum = 0;

    header.next = l1;    // We choice l1 as the result list.
    p1 = l1;
    p2 = l2;
    q = &header;
    while (p1!= NULL && p2 != NULL) {
        sum = p1->val + p2->val + carry;
        carry = sum / 10;
        q->next->val = sum % 10;
        p1 = p1->next;
        p2 = p2->next;
        q = q->next;
        if (p1 == NULL) {
            q->next = p2;
        }
    }

    if (p1 == NULL) {
        while (p2 != NULL && carry != 0) {
            sum = p2->val + carry;
            carry = sum / 10;
            q->next->val = sum % 10;
            p2 = p2->next;
            q = q->next;
        }
    } else {
        while (p1 != NULL && carry != 0) {
            sum = p1->val + carry;
            carry = sum / 10;
            q->next->val = sum % 10;
            p1 = p1->next;
            q = q->next;
        }
    }

    if (carry != 0) {
        q->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        q->next->val = carry;
        q->next->next = NULL;
    }

    return l1;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/swap-nodes-in-pairs/description/ */
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode *p = head, *q = NULL, *prev = NULL, dummyHead = {0};

    if (head == NULL || head->next == NULL) {
        return head;
    }

    dummyHead.next = head;
    prev = &dummyHead;
    while (p != NULL && p->next != NULL) {
        q = p->next;
        p->next = q->next;
        q->next = p;
        prev->next = q;
        prev = p;
        p = p->next;
    }

    return dummyHead.next;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/reverse-nodes-in-k-group/ */
/* The time complexity is O(n), space complexity id O(1). */
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode *p = head, *q = NULL, *prev = NULL, dummyHead = {0};

    if (head == NULL || head->next == NULL || k == 1) {
        return head;
    }

    dummyHead.next = head;
    prev = &dummyHead;    // The last node of the reversed list. prev->next is the head node of the non-reversed list.
    while (p != NULL) {
        q = p;
        for (int i = 0; i < k - 1 && q != NULL; ++i){
            q = q->next;
        }
        if (q == NULL) {    // The rest of the list is less than k nodes.
            break;
        }

        p = q->next;    // The next group's head node.
        q->next = NULL;    // Cut the list into two parts.
        prev->next = reverseList(prev->next);    // Reverse the list and link it to the reversed list.
        while (prev->next != NULL) {
            prev = prev->next;
        }
        prev->next = p;    // Link the rest of the list to the reversed list, make sure the list is not broken.
    }

    return dummyHead.next;
}
