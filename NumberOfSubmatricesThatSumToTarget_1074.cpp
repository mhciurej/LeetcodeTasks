//https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/submissions/1221478463/

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        //matrix cannnot be empty
        vector<vector<int>> sums(matrix);

        for(int i = sums.size() - 2; i >= 0; i--)
        {
            sums[i].back() += sums[i+1].back();
        }
        for(int i = sums.back().size() - 2; i >= 0; i--)
        {
            sums.back()[i] += sums.back()[i+1];
        }
        for(int i = sums.size() - 2; i>= 0; i--)
        {
            for(int j = sums.back().size() -2; j >= 0; j--)
            {
                sums[i][j] += sums[i+1][j] + sums[i][j+1] - sums[i+1][j+1];
            }
        }
        for(auto& i : sums)
        {
            i.push_back(0);
        }
        sums.push_back(std::vector<int>(sums.front().size(), 0));

        int counter = 0;
        for(int x1 = 0; x1 < matrix.front().size(); x1++)
        {
            for(int y1 = 0; y1 < matrix.size(); y1++)
            {
                for(int x2 = x1; x2 < matrix.front().size(); x2++)
                {
                    for(int y2 = y1; y2 < matrix.size(); y2++)
                    {
                        int sum = sums[y1][x1] - sums[y1][x2+1] - sums[y2+1][x1] + sums[y2+1][x2+1];
                        if(sum == target)
                        {
                            counter++;
                        }
                    }
                }
            }
        }
        return counter;
    }
};