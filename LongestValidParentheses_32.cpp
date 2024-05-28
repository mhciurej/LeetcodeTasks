//https://leetcode.com/problems/longest-valid-parentheses/submissions/1218650228/

bool isValidParenthesisString(const std::string& s, int beg, int end)
{
    if((end - beg) % 2 == 1) { return false; }
    int counter = 0;
    for(int i = beg; i < end; i++)
    {
        if(s[i] == '(')
        {
            counter++;
        }
        else
        {
            counter--;
        }
        if(counter < 0) { return false; }
    }
    return counter == 0;
}

int calculate_longest(std::vector<int>& shortest, int pos, int length)
{
    if(pos == shortest.size() or shortest[pos] == 0)
    {
        return length;
    }
    
    return calculate_longest(shortest, pos + shortest[pos], length + shortest[pos]);
}

class Solution {
public:
    int longestValidParentheses(string s) {
        if(s.empty()) { return 0; }
        std::vector<int> shortest;
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == ')')
            {
                shortest.push_back(0);
                continue;
            }
            bool ok = false;
            int counter = 0;
            for (int j = i+2; j <= s.size(); j += 2)
            {
                counter += s[j-2] == '(' ? 1 : -1;
                if(counter < 0) { break; }
                counter += s[j-1] == '(' ? 1 : -1;
                if(counter < 0) { break; }
                if(counter == 0 )
                {
                    shortest.push_back(j - i);
                    ok = true;
                    break;
                }
            }
            if(!ok) { shortest.push_back(0); }
        }

        for(auto i : shortest) {std::cout << i << " "; } std::cout << std::endl;

        std::vector<int> longest;
        for(int i = 0; i < shortest.size(); i++)
        {
            longest.push_back(calculate_longest(shortest, i, 0));
        }

        for(auto i : longest) {std::cout << i << " "; } std::cout << std::endl;

        return *std::max_element(longest.begin(), longest.end());
    }
};