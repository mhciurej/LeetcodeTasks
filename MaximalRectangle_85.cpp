https://leetcode.com/problems/maximal-rectangle/submissions/1260756954/


#include <ranges>

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        vector<vector<int>> heights;
        std::vector<int> first;
        for(char c : matrix.front())
        {
            first.push_back(c - '0');
        }
        heights.push_back(std::move(first));
        int max = 0;
        int current_max = 0;
        for(int n : heights.front())
        {
            current_max = (n ? current_max + 1 : 0);
            max = std::max(max, current_max);
        }
        for (const auto& v : matrix | std::views::drop(1))
        {
            std::vector<int> temp;
            for(int i = 0; i < heights.back().size(); i++)
            {
                int current = v[i] - '0';
                temp.push_back(heights.back()[i] * current + current);
            }
            
            std::stack<std::pair<int, int>> right, left;
            std::vector<int> right_maxes, left_maxes;
            right.push({std::numeric_limits<int>::min(), temp.size()});
            for (int i = temp.size() - 1; i >= 0; i--)
            {
                int current = temp[i];
                while(current <= right.top().first) { right.pop(); }
                right_maxes.push_back(current * (right.top().second - i));
                right.push({current, i});
            }
            std::reverse(right_maxes.begin(), right_maxes.end());
            left.push({std::numeric_limits<int>::min(), -1});
            for (int i = 0; i < temp.size(); i++)
            {
                int current = temp[i];
                while(current <= left.top().first) { left.pop(); }
                left_maxes.push_back(current * (i - left.top().second));
                left.push({current, i});
            }
            for(int i = 0; i < temp.size(); i++)
            {
                max = std::max(max, right_maxes[i] + left_maxes[i] - temp[i]);
            }
            heights.push_back(std::move(temp));
        }
        return max;
    }
};

