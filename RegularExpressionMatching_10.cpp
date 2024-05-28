//https://leetcode.com/problems/regular-expression-matching/submissions/1232304208/

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

void print(const token& t)
{
    std::cout << t.letter << " : " << (t.q == quantity::one ? "one" : "many") << std::endl;
}

bool letters_match(char a, char symbol)
{
    return symbol == '.' or a == symbol;
}

bool match(const std::string& s, const std::vector<token>& tokens)
{
    std::vector<std::vector<bool>> tab(s.size() + 1);
    for(auto& i : tab)
    { 
        i.reserve(tokens.size() + 1);
        i.resize(tokens.size() + 1);
    }
    tab.back().back() = true;
    for(int i = tab.back().size() - 2; i >= 0; i--)
    {
        tab.back()[i] = 
            tab.back()[i + 1] and 
            tokens[i].q == quantity::many;
    }

    for(int i = tab.size() - 2; i >= 0; i--)
    {
        for(int j = tab.front().size() - 2; j >= 0; j--)
        {
            switch(tokens[j].q)
            {
                case quantity::one:
                    tab[i][j] = tab[i + 1][j + 1] and letters_match(s[i], tokens[j].letter);
                    break;
                case quantity::many:
                    if(tokens[j].letter == '.')
                    {
                        for(int k = i; k < tab.size(); k++)
                        {
                            if(tab[k][j + 1])
                            { 
                                tab[i][j] = true;
                                break;
                            }
                        }
                    }
                    else
                    {
                        if(tab[i][j+1])
                        {
                            tab[i][j] = true;
                            break;
                        }
                        for(int k = i; k < s.size() and s[k] == tokens[j].letter; k++)
                        {
                            if(tab[k + 1][j + 1])
                            {
                                tab[i][j] = true;
                                break;
                            }
                        }
                    }
                    break;
            }
        }
    }
    return tab.front().front();
}

class Solution {
public:
    bool isMatch(const string& s, const string& p) {
        std::vector<token> tokens;
        for(int i = 0; i < p.size(); i++)
        {
            char current = p[i];
            if(i < p.size() - 1)
            {
                char next = p[i+1];
                if(next == '*')
                {
                    i++;
                    tokens.push_back({current, quantity::many});
                }
                else
                {
                    tokens.push_back({current, quantity::one});
                }
            }
            else
            {
                tokens.push_back({current, quantity::one});
            }
        }
        return match(s, tokens);
    }
};