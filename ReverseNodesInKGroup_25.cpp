//https://leetcode.com/problems/reverse-nodes-in-k-group/submissions/1268719964/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

std::pair<ListNode*, bool> advance_k(ListNode* head, int k)
{
    if(!head) { return std::make_pair(nullptr, false); }
    if(k == 1)
    {
        ListNode* next = head->next;
        head -> next = nullptr;
        return std::make_pair(next, true);        
    }
    return advance_k(head -> next, k - 1);
}

ListNode* reverse(ListNode* head, ListNode* acc)
{
    if(!head) { return acc; }
    ListNode* tail = head -> next;
    head -> next = acc;
    return reverse(tail, head);
}

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        auto [ptr, flag] = advance_k(head, k);
        if(!flag) { return head; }
        ListNode* next = reverseKGroup(ptr, k);
        return reverse(head, next);
    }
};