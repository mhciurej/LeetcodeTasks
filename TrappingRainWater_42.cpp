//https://leetcode.com/problems/trapping-rain-water/submissions/1268496454/

class Solution {
public:
    int trap(vector<int>& height) {
        if(height.size() <= 2) {return 0;}
        const int SIZE = height.size();
        std::vector<int> left, right;
        left.reserve(SIZE);
        left.resize(SIZE);
        right.reserve(SIZE);
        right.resize(SIZE);
        left[0] = 0;
        left[1] = height.front();
        for(int i = 2; i < SIZE; i++)
        {
            left[i] = std::max(height[i-1], left[i-1]);
        }
        right[SIZE - 1] = 0;
        right[SIZE - 2] = height.back();
        for(int i = SIZE - 3; i >= 0; i--)
        {
            right[i] = std::max(height[i+1], right[i+1]);
        }
        int counter = 0;
        for(int i = 0; i < SIZE; i++)
        {
            counter += std::max(std::min(left[i], right[i]) - height[i], 0);
        }
        return counter;
    }
};