//https://leetcode.com/problems/distinct-subsequences/submissions/1228026445/

class Solution {
public:
    int numDistinct(string s, string t) {
        std::ios::sync_with_stdio(false);
        std::vector<std::vector<unsigned long long int>> tab;
        tab.reserve(t.size() + 1);
        tab.resize(t.size() + 1);
        for(auto& i : tab)
        {
            i.reserve(s.size() + 1);
            i.resize(s.size() + 1);
        }
        for(auto& i : tab.back()) { i = 1; }
        tab.back().back() = 1;

        for (int i = tab.size() - 2; i >= 0; i--)
        {
            for(int j = tab.front().size() - 2; j >= 0; j--)
            {
                tab[i][j] = tab[i][j + 1];
                if(s[j] == t[i])
                {
                    tab[i][j] += tab[i + 1][j + 1];
                }

                
            }

        }

        return tab.front().front();
    }
};