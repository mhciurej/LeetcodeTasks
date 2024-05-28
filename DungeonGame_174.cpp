https://leetcode.com/problems/dungeon-game/description/

#include <ranges>

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        vector<vector<int>> needs(dungeon);
        for(auto& i : needs)
        {
            for(auto& j : i) { j = 0; }
        }
        needs.back().back() = std::max(1, -dungeon.back().back() + 1);
        for(int i : std::views::iota(0, static_cast<int>(needs.back().size()))
            | std::views::reverse
            | std::views::drop(1))
        {
            needs.back()[i] = std::max(1, needs.back()[i + 1] - dungeon.back()[i]);
        }
        for(int i : std::views::iota(0, static_cast<int>(needs.size()))
            | std::views::reverse
            | std::views::drop(1))
        {
            needs[i].back() = std::max(1, needs[i + 1].back() - dungeon[i].back());
        }
        for(int i : std::views::iota(0, static_cast<int>(needs.size()))
            | std::views::reverse
            | std::views::drop(1))
        {
            for(int j : std::views::iota(0, static_cast<int>(needs.front().size()))
                | std::views::reverse
                | std::views::drop(1))
            {
                needs[i][j] = std::min(
                    std::max(1, needs[i + 1][j] - dungeon[i][j]),
                    std::max(1, needs[i][j + 1] - dungeon[i][j])
                );
            }
        }
        return needs.front().front();
    }
};