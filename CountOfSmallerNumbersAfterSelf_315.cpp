//https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/

#include <span>

template <typename T>
void merge(const std::span<T>& left, const std::span<T>& right) {
    std::vector<T> result;
    int i = 0, j = 0;
    while(i < left.size() and j < right.size()) {
        if(left[i] <= right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    while(i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while(j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
    for (int k = 0; k < left.size(); k++) { left[k] = result[k]; }
    for (int k = 0; k < right.size(); k++) { right[k] = result[left.size() + k]; }
}

void print(const std::span<std::tuple<int, int, int>>& s)
{
    for (auto& [num, pos, amount] : s)
    {
        std::cout << "{" << num << ", " << pos << ", " << amount << "}, ";
    }
    std::cout << std::endl;
}

void perform(const std::span<std::tuple<int, int, int>>& s) {
    if(s.size() <= 1) { return; }
    int middle = s.size() / 2;
    auto left_struct = s.subspan(0, middle);
    auto right_struct = s.subspan(middle, s.size() - middle);
    perform(left_struct);
    perform(right_struct);

    int left = 0, right = 0;
    while(left < left_struct.size() and right < right_struct.size()) {
        if(get<0>(left_struct[left]) > get<0>(right_struct[right])) {
            right++;
            continue;
        }
        get<2>(left_struct[left]) += right;
        left++;
    }
    while(left < middle)
    {
        get<2>(left_struct[left]) += right;
        left++;
    }
    merge(left_struct, right_struct);
}

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        std::vector<std::tuple<int, int, int>> copy;
        for(int i = 0; i < nums.size(); i++) { copy.emplace_back(nums[i], i, 0); }
        perform(std::span(copy.begin(), copy.size()));
        std::vector<int> result(nums);
        for(auto& [_, pos, amount] : copy) { result[pos] = amount; }
        return result;
    }
};