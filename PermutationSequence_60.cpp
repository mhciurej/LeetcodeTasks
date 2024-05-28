https://leetcode.com/problems/permutation-sequence/submissions/1218175605/

#include <unordered_map>

int factorial[10];

class Solution {
public:
    string getPermutation(int n, int k) {
        k--;
        factorial[0] = 1;
        for(int i = 1; i < 10; i++)
        {
            factorial[i] = factorial[i-1]*i;
        }
        std::vector<int> cost;
        for(int i = n; i > 0; i--)
        {
            cost.push_back(factorial[i - 1]);
        }
        std::vector<int> changes;
        for(int c : cost)
        {
            changes.push_back(k / c);
            k -= ((k / c ) * c);
        }
        std::vector<int> digits;
        for(int i = 1; i <= n; i++)
        {
            digits.push_back(i);
        }
        std::string result;
        for(int i : changes)
        {
            result += std::to_string(digits[i]);
            digits.erase(digits.begin() + i);
        }
        return result;
    }
};
