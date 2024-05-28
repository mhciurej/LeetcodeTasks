//https://leetcode.com/problems/n-queens/submissions/1261114555/

std::vector<std::vector<int>> backtrack(std::vector<std::unordered_set<int>>& possibilities, int currentRow, std::vector<int>& startingBoard)
{
    if(currentRow == possibilities.size()) { return { startingBoard }; }
    std::vector<std::vector<int>> result;
    for(int p : possibilities[currentRow])
    {
        startingBoard.push_back(p);
        std::set<std::pair<int, int>> removed; // should be unordered
        for (int i = currentRow + 1; i < possibilities.size(); i++)
        {
            if(possibilities[i].contains(p))
            {
                removed.insert({i, p});
                possibilities[i].erase(p);
            }
            int left = p - i + currentRow;
            if(possibilities[i].contains(left))
            {
                removed.insert({i, left});
                possibilities[i].erase(left);
            }
            int right = p + i - currentRow;
            if(possibilities[i].contains(right))
            {
                removed.insert({i, right});
                possibilities[i].erase(right);
            }
        }

        std::vector<std::vector<int>> recursive_call = backtrack(possibilities, currentRow + 1, startingBoard);
        for(auto& v : recursive_call)
        {
            result.push_back(std::move(v));
        }

        for(auto& [i, j] : removed)
        {
            possibilities[i].insert(j);
        }
        startingBoard.pop_back();
    }
    return result;
}

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        std::vector<std::unordered_set<int>> possibilities;
        for(int i = 0; i < n; i++)
        {
            std::unordered_set<int> starting;
            for(int j = 0; j < n; j++)
            {
                starting.insert(j);
            }
            possibilities.push_back(std::move(starting));
        }
        std::vector<int> board;
        std::vector<std::vector<int>> answer = backtrack(possibilities, 0, board);
        std::vector<std::vector<std::string>> result;
        for(const auto& vec : answer)
        {
            std::vector<std::string> v;
            for(int i : vec)
            {
                std::string s(n, '.');
                s[i] = 'Q';
                v.push_back(std::move(s));
            }
            result.push_back(std::move(v));
        }
        return result;
    }
};

