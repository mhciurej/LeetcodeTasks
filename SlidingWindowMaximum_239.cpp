//https://leetcode.com/problems/sliding-window-maximum/description/

#include <deque>

class local_max
{
    std::deque<std::pair<int, int>> maxs;
    int k;
    int pos;
public:
    local_max(int k) : k(k) {}
    bool empty() { return maxs.empty(); }
    void push(const std::pair<int, int>& p)
    {
        if(empty())
        {
            maxs.push_back(p);
            return;
        }
        if(maxs.back().second + k <= p.second or maxs.back().first <= p.first)
        {
            maxs.pop_back();
            push(p);
        }
        else
        {
            maxs.push_back(p);
        }
    }
    void pop() { maxs.pop_front(); }
    std::pair<int, int> top(){ return maxs.front(); }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        local_max maxs(k);
        std::vector<int> result;
        for(int i = 0; i < k; i++) { maxs.push({nums[i], i}); }
        result.push_back(maxs.top().first);
        for (int i = k; i < nums.size(); i++)
        {
            maxs.push(std::make_pair(nums[i], i));
            while (maxs.top().second + k <= i) { maxs.pop(); }
            result.push_back(maxs.top().first);
        }
        return result;
    }
};
