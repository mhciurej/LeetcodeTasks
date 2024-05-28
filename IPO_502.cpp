//https://leetcode.com/problems/ipo/submissions/1268741742/

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        std::multiset<int> available;
        std::multiset<std::pair<int, int>> unaffordable;
        for(int i = 0; i < profits.size(); i++)
        {
            if(capital[i] <= w)
            {
                available.insert(profits[i]);
            }
            else
            {
                unaffordable.insert({capital[i], profits[i]});
            }
        }
        while(k--)
        {
            if(available.empty()) { return w; }
            auto last = --available.end();
            w += *last;
            available.erase(last);
            while(!unaffordable.empty())
            {
                auto [c, p] = *unaffordable.begin();
                if(c > w) { break; }
                available.insert(p);
                unaffordable.erase(unaffordable.begin());
            }
        }
        return w;
    }
};