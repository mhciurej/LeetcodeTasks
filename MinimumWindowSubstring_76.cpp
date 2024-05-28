//https://leetcode.com/problems/minimum-window-substring/submissions/1268718433/

#include <unordered_map>
#include <algorithm>
#include <ranges>

bool contains(const unordered_map<char, int>& p, const unordered_map<char, int>& q)
{
    for(const auto& [key, val] : q)
    {
        if(!p.contains(key) or p.at(key) < val)
        {
            return false;
        }
    }
    return true;
}

class Solution {
public:
    string minWindow(string s, string t) {
        std::unordered_map<char, int> tmap;
        for(char c : std::views::all(t))
        {
            tmap[c]++;
        }

        std::unordered_map<char, int> substr;
        bool found = false;
        for (char c : s)
        {
            substr[c]++;
            if(contains(substr, tmap))// to optimize
            {
                found = true;
                break;
            }
        }

        if(!found) { return ""; }
        std::vector<int> ends;
        int elements = 0;
        for (const auto& [_, val] : substr)
        {
            elements += val;
        }
        ends.push_back(elements);

        for(int i = 1; i < s.size(); i++)
        {
            char before = s[i - 1];
            substr[before]--;
            if(substr[before] >= tmap[before])
            {
                ends.push_back(ends.back());
                continue;
            }
            else
            {
                found = false;
                for (int j = ends.back(); j < s.size(); j++)
                {
                    char c = s[j];
                    substr[c]++;
                    if(c == before)
                    {
                        found = true;
                        ends.push_back(j + 1);
                        break;
                    }
                }
                if(!found)
                {
                    break;
                }

            }
        }
        int pos = 0;
        for(int i = 1; i < ends.size(); i++)
        {
            if(ends[i] - i < ends[pos] - pos)
            {
                pos = i;
            }
        }

        return s.substr(pos, ends[pos] - pos);
    }
};