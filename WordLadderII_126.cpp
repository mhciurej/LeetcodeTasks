//https://leetcode.com/problems/word-ladder-ii/submissions/1260896232/

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
    std::vector<std::vector<std::string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        std::unordered_map<std::string, int> distance;
        distance.insert({beginWord, 0});
        std::unordered_set<std::string> available(wordList.begin(), wordList.end());
        if(!available.contains(endWord)) { return {}; }
        available.erase(beginWord);
        std::unordered_set<std::string> layer; // can change to indices
        layer.insert(beginWord);
        
        for(int i = 1; available.contains(endWord) and !layer.empty(); i++)
        {
            std::unordered_set<std::string> to_remove; // can change to indices
            for (const std::string& l : layer)
            {
                for(const std::string& s : available)
                {
                    if(transformable(l, s))
                    {
                        to_remove.insert(s);
                    }
                }
            }
            for(const auto& s : to_remove) { available.erase(s); }
            for(const std::string& s : to_remove) { distance[s] = i; }
            std::swap(to_remove, layer);
        }
        if(!distance.contains(endWord)) { return {}; }

        std::unordered_map<int, std::vector<std::string>> by_distance;
        for (const auto& [str, dist] : distance) { by_distance[dist].push_back(str); }

        std::vector<std::vector<std::string>> results{{endWord}};
        while(results.back().back() != beginWord)
        {
            std::vector<std::vector<std::string>> temp;
            for(const auto& result : results)
            {
                const std::string& last = result.back();
                for(const auto& s : by_distance[distance[last] - 1])
                {
                    if(transformable(s, last))
                    {
                        auto to_insert(result);
                        to_insert.push_back(s);
                        temp.push_back(to_insert);
                    }
                }
            }
            std::swap(results, temp);
        }
        for (auto& r : results) { std::reverse(r.begin(), r.end()); }
        return results;
    }
};