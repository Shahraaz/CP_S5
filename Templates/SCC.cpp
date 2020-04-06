//Add Dummy Comment
//https://github.com/Shahraaz/CP/blob/master/SCC.cpp

typedef vector<int> _vi;
typedef vector<_vi> _graph;
int getConj(int x)
{
    return x ^ 1;
}
auto add = [&](int a, int b) {
    adj[a].pb(b);
    adj[getConj(b)].pb(getConj(a));
};
auto addXor = [&](int a, int b) {
    add(a, getConj(b));
    add(getConj(a), b);
};
auto addOr = [&](int a, int b) {
    add(getConj(a), b);
};

auto addand = [&](int u, int v) {
    add(getConj(u), u);
    add(getConj(v), v);
};

class SCC
{
public:
    int _n, _m, CompC;
    _graph G, RevG, SccG;
    stack<int> St;
    _vi Vis, Comp;
    SCC()
    {
    }
    void fillOrder(int i)
    {
        Vis[i] = true;
        for (int x : G[i])
            if (!Vis[x])
                fillOrder(x);
        St.push(i);
    }
    void Dfs(int u, int c)
    {
        Vis[u] = true;
        Comp[u] = c;
        for (int x : RevG[u])
            if (!Vis[x])
                Dfs(x, c);
    }
    void MakeScc()
    {
        for (int i = 0; i < _n; ++i)
            if (!Vis[i])
                fillOrder(i);
        fill(Vis.begin(), Vis.end(), false);
        CompC = 0;
        while (!St.empty())
        {
            auto v = St.top();
            St.pop();
            if (!Vis[v])
                Dfs(v, CompC++);
        }
        SccG.resize(CompC);
        for (int i = 0; i < _n; ++i)
            for (auto y : G[i])
                if (Comp[i] != Comp[y])
                    SccG[Comp[i]].pb(Comp[y]);
        for (int i = 0; i < CompC; ++i)
        {
            sort(SccG[i].begin(), SccG[i].end());
            SccG[i].erase(unique(SccG[i].begin(), SccG[i].end()), SccG[i].end());
        }
    }
    SCC(_graph _G)
    {
        G = _G;
        _n = G.size();
        _m = 0;
        Vis.resize(_n);
        Comp.resize(_n);
        RevG.resize(_n);
        for (int i = 0; i < _n; ++i)
            for (auto y : G[i])
            {
                _m++;
                RevG[y].pb(i);
            }
        MakeScc();
    }
    pair<_graph, _vi> GetScc()
    {
        return {SccG, Comp};
    }
};
