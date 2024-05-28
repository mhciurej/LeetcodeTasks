//https://leetcode.com/problems/count-subarrays-with-fixed-bounds/submissions/

long long int subarrays(const std::vector<int>& nums, int begin, int last, int minK, int maxK)
{
    std::vector<int> maxes;
    std::vector<int> mines;
    for(int i = last; i >= begin; i--) { if(nums[i] == maxK) maxes.push_back(i); }
    for(int i = last; i >= begin; i--) { if(nums[i] == minK) mines.push_back(i); }

    long long counter = 0;
    for(int i = begin; i <= last; i++)
    {
        while(!mines.empty() and mines.back() < i) { mines.pop_back(); }
        while(!maxes.empty() and maxes.back() < i) { maxes.pop_back(); }
        if(mines.empty() or maxes.empty()) { break; }
        counter += (1 + last - std::max(maxes.back(), mines.back()));
    }
    return counter;
}

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        std::vector<int> splitters;
        splitters.push_back(-1);
        for(int i = 0; i < nums.size(); i++)
        {
            if((nums[i] < minK) or (nums[i] > maxK))
            {
                splitters.push_back(i);
            }
        }
        splitters.push_back(nums.size());

        long long int result = 0;
        for(int i = 0; i + 1 < splitters.size(); i++)
        {
            if(splitters[i+1] - splitters[i] <= 1) { continue; }
            result += subarrays(nums, splitters[i] + 1, splitters[i+1] - 1, minK, maxK);
        }
        return result;
    }
};