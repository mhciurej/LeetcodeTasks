//https://leetcode.com/problems/maximum-score-of-a-good-subarray/submissions/1269278931/

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        std::vector<int> left_minimums{ k };
        std::vector<int> right_minimums{ k };
        for(int i = k - 1; i >= 0; i--)
        {
            if(nums[i] < nums[left_minimums.back()]) { left_minimums.push_back(i); }
        }
        for(int i = k + 1; i < nums.size(); i++)
        {
            if(nums[i] < nums[right_minimums.back()]) { right_minimums.push_back(i); }
        }

        int score = nums[k];
        int left = 1, right = 1;
        int current_minimum = nums[k];
        while (left < left_minimums.size() and right < right_minimums.size())
        {
            score = std::max(score, current_minimum * (right_minimums[right] - left_minimums[left] - 1));
            if(nums[left_minimums[left]] <= nums[right_minimums[right]])
            {
                current_minimum = nums[right_minimums[right]];
                right++;
            }
            else
            {
                current_minimum = nums[left_minimums[left]];
                left++;
            }
        }
        while (left < left_minimums.size())
        {
            score = std::max(score, current_minimum * static_cast<int>(nums.size() - left_minimums[left] - 1));
            current_minimum = nums[left_minimums[left]];
            left++;
        }
        while (right < right_minimums.size())
        {
            score = std::max(score, current_minimum * right_minimums[right]);
            current_minimum = nums[right_minimums[right]];
            right++;
        }
        return std::max(score, current_minimum * static_cast<int>(nums.size()));
    }
};
