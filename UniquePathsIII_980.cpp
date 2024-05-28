//https://leetcode.com/problems/unique-paths-iii/submissions/1221410505/

#include <unordered_set>

struct Pos
{
    int x;
    int y;
    Pos() : x(0), y(0) {}
    Pos(int x, int y) : x(x), y(y) {} 
    Pos operator+(const Pos& to_add) const
    {
        return { x + to_add.x, y + to_add.y };
    }
    bool operator==(const Pos& to_compare) const
    {
        return x == to_compare.x and y == to_compare.y;
    }
};

struct Hash
{
    int operator()(const Pos& p) const 
    {
        return 100 * p.x + p.y;
    }
};

struct KeyEqual
{
    bool operator()(const Pos& p1, const Pos& p2) const
    {
        return p1 == p2;
    }
};

void solutions(vector<vector<int>>& grid, int* counter, const Pos start, const Pos end, unordered_set<Pos, Hash, KeyEqual>& visited, unordered_set<Pos, Hash, KeyEqual>& not_visited)
{
    auto is_neighbour_valid = [&grid](Pos& neighbour)
    {
        return (neighbour.x >= 0 and neighbour.x < grid.front().size())
            and (neighbour.y >= 0 and neighbour.y < grid.size());
    };

    visited.insert(start);
    not_visited.erase(start);
    if(start == end)
    {
        if(not_visited.empty())
        {
            (*counter)++;
        }
    }
    else
    {
        Pos tab[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (const Pos& i : tab)
        {
            Pos neighbour = start + i;
            if(is_neighbour_valid(neighbour) and !visited.contains(neighbour)) 
            {
                solutions(grid, counter, neighbour, end, visited, not_visited);
            }
        }
    }
    
    visited.erase(start);
    not_visited.insert(start);
}

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        if(grid.empty() or grid.front().empty()) { return 0; }
        int counter = 0;
        Pos start, end;
        std::unordered_set<Pos, Hash, KeyEqual> visited(400, Hash(), KeyEqual());
        std::unordered_set<Pos, Hash, KeyEqual> not_visited(400, Hash(), KeyEqual());
        for(int i = 0; i < grid.size(); i++)
        {
            for(int j = 0; j < grid.front().size(); j++)
            {
                Pos current{j, i};
                switch (grid[i][j])
                {
                    case 0:
                        not_visited.insert(current);
                        break;

                    case -1:
                        visited.insert(current);
                        break;
                    
                    case 1:
                        start = current;
                        break;

                    case 2:
                        end = current;
                        break;
                }
            }
        }
        solutions(grid, &counter, start, end, visited, not_visited);
        return counter;
    }
};