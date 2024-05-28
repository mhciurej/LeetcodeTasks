https://leetcode.com/problems/text-justification/submissions/1268719580/

class Line
{
    std::vector<std::string> line;
    int size;
public:
    Line() : size(0) {}
    void push(const std::string& s)
    {
        line.push_back(s);
        size += s.size();
    }
    std::string to_string()
    {
        std::string result;
        for(const auto& i : line)
        {
            result += i;
        }
        return result;
    }
    void clear()
    {
        line.clear();
        size = 0;
    }
    int length()
    {
        return size;
    }
    Line& justify(int width)
    {
        if(line.size() == 1) { push(std::string(width - size, ' ')); }
        if(length() == width) { return *this; }
        for(auto& s : line)
        {
            if(s.front() == ' ' and length() < width)
            {
                s.push_back(' ');
                size++;
            }
        }
        return justify(width);
    }
};

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, const int maxWidth) {
        std::vector<std::string> lines;
        Line line;
        line.push(std::string(maxWidth, ' '));
        for(auto& i : words)
        {
            if (line.length() + 1 + i.size() <= maxWidth)
            {
                line.push(" ");
            }
            else
            {
                lines.push_back((line.justify(maxWidth)).to_string());
                line.clear();
            }
            line.push(std::move(i));
        }
        lines.push_back((line.justify(maxWidth)).to_string());
        std::string last_line(maxWidth, ' ');
        for(int pos = 0; char i : lines.back())
        {
            if(i != ' ' or last_line[pos - 1] != ' ')
            {
                last_line[pos++] = i;
            }
        }
        lines.pop_back();
        lines.erase(lines.begin());
        lines.push_back(last_line);
        return lines;
    }
};

