https://leetcode.com/problems/longest-increasing-path-in-a-matrix/submissions/1243944340/

#include <ranges>

std::vector<std::pair<int, int>> neighbours(const std::pair<int, int>& p, std::pair<int, int>& boundries)
{
    auto& [i, j] = p;
    std::vector<std::pair<int, int>> result{{i - 1, j}, {i, j - 1}, {i, j + 1}, {i + 1, j}};
    erase_if(result,
        [&boundries](const std::pair<int, int>& q)
        {
            return q.first < 0 or q.second < 0 or q.first >= boundries.first or q.second >= boundries.second;
        }
    );
    return result;
}

std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)> comparer(const std::vector<std::vector<int>>& tab)
{
    return
        [&tab](const std::pair<int, int>& l, const std::pair<int, int>& r)
        {
            auto [x1, y1] = l;
            auto [x2, y2] = r;
            return tab[x1][y1] < tab[x2][y2];
        };
}

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty()) { return 0; }
        if(matrix.size() == 1 and matrix.front().size() == 1) { return 1; }
        std::vector<std::vector<int>> paths(matrix);
        std::pair<int, int> boundries = std::make_pair(matrix.size(), matrix.front().size());
        std::vector<std::pair<int, int>> coordinates;
        for(int i = 0; i < matrix.size(); i++)
        {
            for(int j = 0; j < matrix.front().size(); j++)
            {
                coordinates.push_back({i, j});
                paths[i][j] = 0;
            }
        }
        auto matrix_comparer = comparer(matrix);
    
        std::sort(coordinates.begin(), coordinates.end(), matrix_comparer);
        for(const std::pair<int, int>& p : coordinates | std::views::reverse)
        {
            auto [x1, y1] = p;
            auto neighbours_ = neighbours(p, boundries);
            std::erase_if(neighbours_, [x1, y1, &matrix](const std::pair<int, int>& q){ return matrix[x1][y1] == matrix[q.first][q.second]; });
            neighbours_.push_back(p);
            auto [max_x, max_y] = *std::max_element(neighbours_.begin(), neighbours_.end(), comparer(paths));
            paths[x1][y1] = 1 + paths[max_x][max_y];
        }
        auto [max_x, max_y] = *std::max_element(coordinates.begin(), coordinates.end(), comparer(paths));
        return paths[max_x][max_y];
    }
};