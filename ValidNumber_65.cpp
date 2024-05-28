https://leetcode.com/problems/valid-number/submissions/1217964923/

#include <ranges>
#include <algorithm>

bool is_valid_integer(const std::string& s_)
{
    const std::string s = ((s_[0] == '+' or s_[0] == '-') ? s_.substr(1) : s_);
    if(s.empty()) { return false; }
    return std::all_of(s.begin(), s.end(), [](char c) { return isdigit(c); });
}

bool is_valid_decimal(const std::string& s_)
{
    const std::string s = ((s_[0] == '+' or s_[0] == '-') ? s_.substr(1) : s_);
    if(s.empty()) { return false; }
    auto dot = std::find(s.begin(), s.end(), '.');
    if(dot == s.end()) { return false; }
    if(s == ".") { return false; }
    for(auto i : std::ranges::iota_view(s.begin(), s.end()))
    {
        if (i != dot and !isdigit(*i))
        {
            return false;
        }
    }
    return true;
}

bool is_scientific_notation(const std::string& s)
{
    int e_pos = std::find_if(s.begin(), s.end(), [](char c){ return c == 'e' or c == 'E'; }) - s.begin();
    if(e_pos == s.size()) { return false; }
    std::string s1 = s.substr(0, e_pos);
    std::string s2 = s.substr(e_pos + 1);
    return (is_valid_integer(s1) or is_valid_decimal(s1)) and is_valid_integer(s2);
}

class Solution {
public:
    bool isNumber(string s) {
        return is_valid_integer(s) or is_valid_decimal(s) or is_scientific_notation(s);
    }
};
