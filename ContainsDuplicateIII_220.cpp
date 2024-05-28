//https://leetcode.com/problems/contains-duplicate-iii/submissions/1229091929/

struct Interval
{
    int begin;
    int end;
    bool operator==(const Interval& to_compare) const
    {
        return begin == to_compare.begin;
    }
};

enum class choice
{
    alone,
    interval
};

class Both
{
    int alone;
    Interval q;
    choice version;
public:
    Both (int a) : alone(a), version(choice::alone) {}
    Both (Interval i) : q(i), version(choice::interval) {}
    std::partial_ordering operator<=>(const Both& to_compare) const
    {
        if(version == choice::alone)
        {
            if(to_compare.version == choice::alone)
            {
                return alone <=> to_compare.alone;
            }
            else
            {
                if(alone < to_compare.q.begin) { return std::partial_ordering::less; }
                if(alone > to_compare.q.end) { return std::partial_ordering::greater; }
                return std::partial_ordering::equivalent;
            }
        }
        else
        {
            if(to_compare.version == choice::alone)
            {
                if(to_compare.alone < q.begin) { return std::partial_ordering::greater; }
                if(to_compare.alone > q.end) { return std::partial_ordering::less; }
                return std::partial_ordering::equivalent;
            }
            else
            {
                throw std::runtime_error("Not allowed comparison!");
            }
        }
    }
    bool operator==(const Both&) const = default;
    void print()
    {
        std::cout << alone;
    }
};

class Solution {
public:
    bool containsNearbyAlmostDuplicate(const std::vector<int>& nums, int indexDiff, int valueDiff) const {
        std::set<Both> acc;
        for(int i = 0, left = -1 - indexDiff; i < nums.size(); i++, left++)
        {
            if(left >= 0) { acc.erase(Both(nums[left])); }
            if(acc.contains(Both({nums[i] - valueDiff, nums[i] + valueDiff}))) { return true; }
            acc.insert(Both(nums[i]));
        }
        return false;
    }
};