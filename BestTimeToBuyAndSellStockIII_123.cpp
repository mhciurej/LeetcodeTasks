//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/submissions/1268721269/

#include <ranges>

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        std::vector<int> right_intervals, left_intervals;
        int right_max = prices.back(), left_min = prices.front();

        right_intervals.push_back(0);
        for (int n : prices | std::views::reverse | std::views::drop(1))
        {
            right_intervals.push_back(std::max(right_max - n, right_intervals.back()));
            right_max = std::max(right_max, n);
        }
        std::reverse(right_intervals.begin(), right_intervals.end());

        left_intervals.push_back(0);
        for(int n : prices | std::views::drop(1))
        {
            left_intervals.push_back(std::max(n - left_min, left_intervals.back()));
            left_min = std::min(left_min, n);
        }

        int max = *max_element(left_intervals.begin(), left_intervals.end());
        for(int i = 1; i < prices.size() - 1; i++)
        {
            max = std::max(max, left_intervals[i] + right_intervals[i+1]);
        }
        return max;
    }
};