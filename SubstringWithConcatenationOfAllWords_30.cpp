//https://leetcode.com/problems/substring-with-concatenation-of-all-words/submissions/1268721316/

std::unordered_map<std::string, int> counting_map(const std::vector<std::string>& words)
{
    std::unordered_map<std::string, int> result;
    for(const auto& w : words)
    {
        result[w]++;
    }
    return result;
}

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        const int wordLength = words[0].size();
        const int concatenatedLenght = wordLength * words.size();
        if(concatenatedLenght > s.size()) { return {}; }
        std::vector<int> result;
        const auto map_original = counting_map(words);
        for(int i = 0; i + concatenatedLenght <= s.size(); i++)
        {
            auto map(map_original);
            bool ok = true;
            for (int j = 0; j < concatenatedLenght; j += wordLength)
            {
                std::string sub = s.substr(i + j, wordLength); // to optimize
                map[sub]--;
                if(map[sub] < 0)
                {
                    ok = false;
                    break;
                }
            }
            if(ok) { result.push_back(i); }
        }
        return result;
    }
};