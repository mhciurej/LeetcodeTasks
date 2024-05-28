//https://leetcode.com/problems/sudoku-solver/submissions/1232441047/

#include <ranges>

std::unordered_set<int> allowed(int y, int x, const std::vector<std::vector<char>>& board)
{
    std::unordered_set<int> result;
    for (int i = 1; i <= 9; i++) { result.insert('0' + i); }
    for (int i = 0; i < 9; i++)
    {
        result.erase(board[y][i]);
        result.erase(board[i][x]);
        result.erase(board[y/3*3 + i/3][x/3*3 + i%3]);
    }
    return result;
}

class Solution {
public:
    bool solveSudoku(vector<vector<char>>& board) {
        for(int i : std::views::iota(0, 9))
        {
            for(int j : std::views::iota(0, 9))
            {
                if(board[i][j] == '.')
                {
                    auto possibilities = allowed(i, j, board);
                    if(possibilities.empty()) { return false; }
                    for(char p : possibilities)
                    {
                        board[i][j] = p;
                        if(solveSudoku(board)) { return true; }
                    }
                    board[i][j] = '.';
                    return false;
                }
            }
        }
        return true;
    }
};