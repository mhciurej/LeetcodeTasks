//https://leetcode.com/problems/scramble-string/submissions/1238453952/

struct pair_
{
    std::string s1;
    std::string s2;
};

struct Hash
{
    size_t operator()(const pair_& p) const
    {
        return std::hash<std::string>()(p.s1) ^ std::hash<std::string>()(p.s2);
    }
};

struct KeyEqual
{
    bool operator()(const pair_& p1, const pair_& p2) const
    {
        return p1.s1 == p2.s1 and p1.s2 == p2.s2;
    }
};

unordered_map <pair_, bool, Hash, KeyEqual> central;

class Solution {
public:
    bool isScramble(const string& s1, const string& s2) {
        pair_ pair{s1, s2};
        if(central.contains(pair)) { return central[pair]; }
        if (s1 == s2) { return true; }
        unordered_map<char, int> counter1;
        unordered_map<char, int> counter2;
        unordered_map<char, int> counter11;
        unordered_map<char, int> counter22;
        for(int i = 0; i < s1.size() - 1; i++)
        {
            counter1[s1[i]]++;
            counter2[s2[i]]++;
            if(
                counter1[s1[i]] == counter2[s1[i]] 
                and
                counter1[s2[i]] == counter2[s2[i]]
                and
                counter1 == counter2)
            {
                if (
                    isScramble(s1.substr(0, i + 1), s2.substr(0, i + 1))
                    and
                    isScramble(s1.substr(i + 1), s2.substr(i + 1))
                )
                {
                    central[pair] = true;
                    return true;
                }
            }

            int back_pos = s2.size() - 1 - i;
            counter11[s1[i]]++;
            counter22[s2[back_pos]]++;
            if(
                counter11[s1[i]] == counter22[s1[i]]
                and
                counter11[s2[back_pos]] == counter22[s2[back_pos]]
                and
                counter11 == counter22)
            {
                if (
                    isScramble(s1.substr(0, i + 1), s2.substr(back_pos))
                    and
                    isScramble(s1.substr(i + 1), s2.substr(0, back_pos))
                )
                {
                    central[pair_{s1, s2}] = true;
                    return true;
                }
            }
        }
        central[pair] = false;
        return false;
    }
};