//https://leetcode.com/problems/first-missing-positive/submissions/1217766750/

int find(const int pos, std::vector<int>& v)
{
    if(pos == v.size()) { return v.size() + 1; }
    int& current = v[pos];
    if(current == pos + 1)
    {
        return find(pos + 1, v);
    }
    else
    {
        if(current <= pos or current > v.size())
        {
            std::swap(current, v.back());
            v.pop_back();
        }
        else
        {
            if(current == v[current - 1])
            {
                std::swap(current, v.back());
                v.pop_back();
            }
            else
            {
                std::swap(current, v[current - 1]);
            }
        }
        return find(pos, v);
    }
}

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        return find(0, nums);
    }
};