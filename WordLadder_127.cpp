https://leetcode.com/problems/word-ladder/submissions/1268741075/

#include <ranges>

bool transformable(const std::string& p, const std::string& q)
{
    int counter = 0;
    for(int i : std::views::iota(0, static_cast<int>(p.size())))
    {
        if(p[i] != q[i]) { counter++; } // optimize
    }
    return counter == 1;
}

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        std::unordered_map<std::string, std::unordered_set<std::string>> children;
        for(auto& i : wordList)
        { 
            if(transformable(beginWord, i)) { children[beginWord].insert(i); }
        }  
        for(auto& i : wordList)
        {
            for(auto& j : wordList)
            {
                if(transformable(i, j)) { children[i].insert(j); } // optimize 
            }
        }

        std::unordered_set<std::string> reserved;
        std::unordered_set<std::string> just_taken;
        std::queue<std::vector<std::string>> q;
        q.push({ beginWord });
        q.push({});
        while (q.size() > 1)
        {
            std::vector<std::string> current(std::move(q.front()));
            q.pop();
            if(current.size() == 0)
            { 
                q.push({});
                for(auto i : just_taken)
                {
                    reserved.insert(i);
                }
                just_taken.clear();
                continue;
            }
            auto& layer = children[current.back()];
            for(const auto& i : layer)
            {
                if(!reserved.contains(i))
                {
                    std::vector<std::string> next(current);
                    next.push_back(i);
                    reserved.insert(i);
                    if(next.back() == endWord) { return next.size(); }
                    q.push(std::move(next));
                }
            }
        }
        return 0;
    }
};