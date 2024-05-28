//https://leetcode.com/problems/max-points-on-a-line/description/

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int max = 0;
        for (int i = 0; i < points.size(); i++)
        {
            double x1 = points[i][0];
            double y1 = points[i][1];
            std::unordered_map<double, int> coefs_counter;
            
            for(int j = i + 1; j < points.size(); j++)
            {
                double x2 = points[j][0];
                double y2 = points[j][1];
                double coeff = x1 == x2 ? std::numeric_limits<double>::max() : (y1 - y2) / (x1 - x2);
                coefs_counter[coeff]++;
            }
            for(auto& [_, counter] : coefs_counter)
            {
                max = std::max(max, counter);
            }
        }
        return 1 + max;
    }
};