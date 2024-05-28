//https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/submissions/1270183967/

#include <ranges>

class UnionFind
{
    struct node
    {
        int representative;
        int size;
        node() : size(1) {}
    };
    std::vector<node> v;
    int get_representative(int x)
    {
        if(v[x].representative == x) { return x; }
        int rep = get_representative(v[x].representative);
        v[x].representative = rep;
        return rep;
    }
public:
    UnionFind(int N) : v(N+1)
    {
        for(int i = 0; node& n : v) { n.representative = i++; }    
    }
    bool are_joined(int x, int y)
    {
        return get_representative(x) == get_representative(y);
    }
    void join(int x, int y)
    {
        if(are_joined(x, y)) { return; }
        node& X = v[get_representative(x)];
        node& Y = v[get_representative(y)];
        if(X.size >= Y.size)
        {
            Y.representative = get_representative(x);
            X.size += Y.size;
        }
        else
        {
            X.representative = get_representative(y);
            Y.size += X.size;
        }
    }
};

struct stru
{
    int start;
    int end;
    int value;
    bool operator<(const stru& e) const { return value < e.value; }
    stru(const std::vector<int>& v) : start(v[0]), end(v[1]), value(v[2]) {}
};

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries_) {
        std::vector<stru> edges;
        for(auto& e : edgeList) { edges.push_back(e); }
        std::vector<std::pair<stru, int>> queries;
        for(int i = 0; auto& q : queries_) { queries.push_back({q, i++}); }
        std::sort(edges.begin(), edges.end());
        edges.push_back(std::vector<int>{0, 0, std::numeric_limits<int>::max()});
        std::sort(queries.begin(), queries.end());
        UnionFind u(n);
        std::vector<bool> result(queries.size(), false);

        int edges_i = 0, queries_i = 0;
        while(queries_i < queries.size())
        {
            if(edges[edges_i].value < queries[queries_i].first.value)
            {
                u.join(edges[edges_i].start, edges[edges_i].end);
                edges_i++;
            }
            else
            {
                result[queries[queries_i].second] = u.are_joined(queries[queries_i].first.start, queries[queries_i].first.end);
                queries_i++;
            }
        }
        return result;
    }
};