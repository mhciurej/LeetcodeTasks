https://leetcode.com/problems/word-break-ii/submissions/1241057623/

#include <memory>
#include <vector>
#include <ranges>

class Node
{
    std::array<std::shared_ptr<Node>, 1 + 'z' - 'a'> tab;
    std::shared_ptr<Node>& at(char c) { return tab[c - 'a']; }
    std::shared_ptr<Node>& at(int c) { throw "int shouldn't be used here"; }
public:
    bool end;
    int depth;
    Node() : end(false), depth(0) {}
    std::shared_ptr<Node> operator[](char c) const { return tab[c - 'a']; }
    std::shared_ptr<Node> add_letter(char c)
    {
        if(!at(c))
        {
            at(c) = std::make_shared<Node>();
            at(c)->depth = depth + 1;
        }
        return at(c);
    }
};

class Tree
{
    std::shared_ptr<Node> root;
public:
    Tree(const std::vector<std::string>& v) : root(std::make_shared<Node>())
    {
        for(const auto& i : v)
        {
            add_word(i);
        }
    }
    void add_word(const std::string& s)
    {
        std::shared_ptr<Node> current = root;
        for(char c : s)
        {
            current = current -> add_letter(c);
        }
        current -> end = true;
    }
    std::vector<int> possible_words(const std::string& s)
    {
        std::vector<int> result;
        std::shared_ptr<Node> current = root;
        for(char c : s)
        {
            current = (*current)[c];
            if(!current)
            {
                break;
            }
            if(current -> end) { result.push_back(current -> depth); }
        }
        return result;
    }
};

std::pair<std::string, std::string> divide_string(const std::string& s, int lenFirst)
{
    return std::make_pair(s.substr(0, lenFirst), s.substr(lenFirst, s.size() - lenFirst));
}

class Solution {
public:
    std::vector<std::string> wordBreak(const std::string& s, const std::vector<std::string>& wordDict) {
        std::vector<std::vector<std::vector<std::string>>> results;
        results.reserve(s.size() + 1);
        results.resize(s.size() + 1);
        results.back().push_back({""});

        Tree dict(wordDict);
        for (int i : std::views::iota(0, static_cast<int>(s.size())) | std::views::reverse)
        {
            std::string suffix = s.substr(i, s.size() - i);
            std::vector<std::vector<std::string>> result;
            std::vector<int> lengths = dict.possible_words(suffix);
            std::vector<std::string> words;
            for(int n : lengths)
            {
                words.push_back(suffix.substr(0, n));
            }
            std::vector<std::vector<std::string>> to_add;
            for(const auto& w : words)
            {
                for(const auto& v : results[i + w.size()])
                {
                    to_add.push_back(v);
                    to_add.back().push_back(w);
                }
            }
            results[i] = std::move(to_add);
        }
        std::vector<std::string> result;
        auto& sentences = results.front();
        for(auto& vec : sentences)
        {
            std::string sentence;
            for(auto& word : vec | std::views::reverse)
            {
                sentence += word;
                sentence += " ";
            }
            sentence.pop_back();
            sentence.pop_back();
            result.push_back(std::move(sentence));
        }
        return result;
    }
    
};