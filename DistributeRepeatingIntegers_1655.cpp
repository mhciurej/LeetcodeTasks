//https://leetcode.com/problems/distribute-repeating-integers/submissions/1268464870/

#include <span>

bool can_distribute(const std::span<int>& quantity, std::unordered_map<int, int>* map)
{
    if(quantity.empty()) { return true; }
    for(auto& [key, val] : *map)
    {
        if(val >= quantity.front())
        {
            (*map)[key] -= quantity.front();
            if(can_distribute(quantity.subspan(1, quantity.size() - 1), map)) { return true; }
            (*map)[key] += quantity.front();
        }
    }
    return false;
}

class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        std::unordered_map<int, int> counter;
        for(int n : nums) { counter[n]++; }
        std::sort(quantity.begin(), quantity.end(), std::greater{});
        return can_distribute(quantity, &counter);
    }
};