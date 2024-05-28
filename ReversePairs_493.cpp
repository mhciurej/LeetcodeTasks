https://leetcode.com/problems/reverse-pairs/submissions/1245290014/

class subvector
{
    const std::vector<int>& s;
    int begin_, end_;
public:
    subvector(const std::vector<int>& v, int b, int e) : s(v), begin_(b), end_(e) {}
    int at(int n) const { return s[begin_ + n]; }
    auto begin() const { return s.begin() + begin_; }
    auto end() const { return s.begin() + end_; }
    int size() const { return end_ - begin_; }
    subvector sub(int b, int e) const { return subvector(s, begin_ + b, begin_ + e); }
};

class Solution {
    int reversePairs(const subvector& s)
    {
        if(s.size() < 2) { return 0; }
        int result = 0;
        int middle = s.size()/2;
        subvector left = s.sub(0, middle);
        subvector right = s.sub(middle, s.size());
        std::multiset<long long int> left_set(left.begin(), left.end());
        std::multiset<long long int> right_set(right.begin(), right.end());
        int passed = 0;
        auto it = left_set.begin();
        for(long long int n : right_set)
        {
            while(it != left_set.end() and *it <= n * 2)
            {
                it++;
                passed++;
            }
            result += left_set.size() - passed;
        }
        result += reversePairs(left);
        result += reversePairs(right);
        return result;
    }
public:
    int reversePairs(vector<int>& nums) {
        return reversePairs(subvector(nums, 0, nums.size()));
    }
};