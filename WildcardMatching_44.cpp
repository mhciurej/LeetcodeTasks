//https://leetcode.com/problems/wildcard-matching/submissions/

#include <ranges>

enum class quantity
{
    one,
    many
};

struct token
{
    char letter;
    quantity q;
};

bool characterMatch(char c, token t)
{
    return t.letter == '?' or t.letter == c;
}

enum class match
{
    nothing,
    yes,
    no
};

std::string optimize_pattern(const std::string& p)
{   
    std::string pattern;
    pattern.push_back(p[0]);
    for(char c : std::views::all(p) | std::views::drop(1))
    {
        if(c == '*' and pattern.back() == '*')
        {
            continue;
        }
        pattern.push_back(c);
    }
    return pattern;
}

class Solution {
public:
    bool isMatch(const std::string& s, const std::string& p)
    {
        if(s.empty() and p.empty()) { return true; }
        if(p.empty()) { return false; }
        std::string pattern = optimize_pattern(p);
        std::vector<token> tokens;
        for(char i : pattern)
        {
            token t;
            switch (i)
            {
                case '*':
                    t.letter = '?';
                    t.q = quantity::many;
                    break;
                case '?':
                default:
                    t.letter = i;
                    t.q = quantity::one;
                    break;
            }
            tokens.push_back(t);
        }

        std::vector<std::vector<match>> tab;
        tab.reserve(tokens.size() + 1);
        tab.resize(tokens.size() + 1);
        for(auto& v : tab)
        {
            v.reserve(s.size() + 1);
            v.resize(s.size() + 1);
        }
        for(auto& i : tab)
        {
            i.front() = match::no;
        }
        for(auto& i : tab.front())
        {
            i = match::no;
        }
        tab.front().front() = match::yes;
        tab[1].front() = (tokens[0].q == quantity::many ? match::yes : match::no);

        for(int i = 1; i < tab.size(); i++)
        {
            for(int j = 1; j < tab.front().size(); j++)
            {
                char letter = s[j-1];
                token currentToken = tokens[i - 1];
                switch (currentToken.q)
                {
                    case quantity::many:
                        tab[i][j] = match::no;
                        for(int k = 0; k <= j; k++)
                        {
                            if(tab[i - 1][k] == match::yes)
                            {
                                tab[i][j] = match::yes;
                                break;
                            }
                        }
                        break;
                    case quantity::one:
                        tab[i][j] = (characterMatch(letter, currentToken) ? tab[i-1][j-1] : match::no);
                }
            }
        }

        return tab.back().back() == match::yes;
    }
};