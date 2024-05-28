//https://leetcode.com/problems/reducing-dishes/submissions/

class Solution {
public:
    int maxSatisfaction(std::vector<int>& satisfaction) {
        if(satisfaction.empty()) { return 0; }
        std::sort(satisfaction.begin(), satisfaction.end());
        std::vector<int> sums;
        sums.reserve(satisfaction.size());
        sums.resize(satisfaction.size());
        sums.back() = satisfaction.back();
        for(int i = satisfaction.size() - 2; i >= 0; i--)
        {
            sums[i] = sums[i + 1] + satisfaction[i];
        }

        std::vector<int> coefficients;
        coefficients.reserve(satisfaction.size());
        coefficients.resize(satisfaction.size());
        coefficients.back() = sums.back();
        for(int i = satisfaction.size() - 2; i >= 0; i--)
        {
            coefficients[i] = coefficients[i + 1] + sums[i];
        }

        return std::max(*std::max_element(coefficients.begin(), coefficients.end()), 0);
    }
};