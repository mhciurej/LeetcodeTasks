//https://leetcode.com/problems/merge-k-sorted-lists/submissions/1268722488/

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

#include <queue>
#include <ranges>

struct Comparer
{
    bool operator()(ListNode* f, ListNode* s)
    {
        return f->val > s->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto filtered = std::views::all(lists) | std::views::filter([](auto x){ return x != nullptr; });
        std::priority_queue q(filtered.begin(), filtered.end(), Comparer());
        if(q.empty()) { return nullptr; }

        ListNode* result = q.top();
        ListNode* last = q.top();
        if(q.top() -> next) { q.push(q.top() -> next); }
        q.pop();
        last -> next = nullptr;
        while(!q.empty())
        {
            ListNode* bottom = q.top();
            ListNode* rest = bottom->next;
            q.pop();
            if(rest) { q.push(rest); }
            bottom -> next = nullptr;
            last -> next = bottom;
            last = bottom;
        }
        return result;
    }
};