//https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/1232537390/

#include <ranges>

struct field
{
    int pos;
    int val;
};

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        std::vector<int> lowest_on_the_right;
        std::stack<field> s;
        s.push({static_cast<int>(heights.size()), -1});
        for(int h : heights | std::views::reverse)
        {
            while(h <= s.top().val)
            {
                s.pop();
            }
            lowest_on_the_right.push_back(s.top().pos);
            s.push({static_cast<int>(static_cast<int>(heights.size()) - lowest_on_the_right.size()), h});
        }
        std::reverse(lowest_on_the_right.begin(), lowest_on_the_right.end());

        std::vector<int> lowest_on_the_left;
        std::stack<field> g;
        g.push({-1, -1});
        for(int h : heights)
        {
            while(h <= g.top().val)
            {
                g.pop();
            }
            lowest_on_the_left.push_back(g.top().pos);
            g.push({static_cast<int>(- 1 + lowest_on_the_left.size()), h});
        }

        for(int i : std::views::iota(0, static_cast<int>(heights.size())))
        {
            heights[i] *= (lowest_on_the_right[i] - lowest_on_the_left[i] - 1);
        }
        return *std::max_element(heights.begin(), heights.end());
    }
};