#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

//Add Dummy Comment
//https://github.com/Shahraaz/CP/blob/master/SCC.cpp

typedef vector<int> _vi;
typedef vector<_vi> _graph;
int getConj(int x)
{
    return x ^ 1;
}

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

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<int> prev;
    set<pair<int, int>> ss;
    set<int> certains, uncertains;
    for (size_t i = 0; i < n; i++)
    {
        int sz;
        cin >> sz;
        vector<int> now(sz);
        for (auto &x : now)
        {
            cin >> x;
            --x;
        }
        if (i > 0)
        {
            int j = 0;
            bool ok = false;
            db(prev);
            db(now);
            for (; j < min(now.size(), prev.size()); j++)
            {
                if (prev[j] != now[j])
                {
                    if (prev[j] < now[j])
                        ss.insert({now[j], prev[j]});
                    else
                    {
                        certains.insert(prev[j]);
                        uncertains.insert(now[j]);
                    }
                    ok = true;
                    break;
                }
            }
            if (!ok)
                if (prev.size() > now.size())
                {
                    cout << "No\n";
                    return;
                }
        }
        prev = now;
    }
    vector<vector<int>> adj(2 * m);

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

    for (auto x : certains)
        addOr(2 * x, 2 * x);
    for (auto x : uncertains)
        addOr(2 * x + 1, 2 * x + 1);
    for (auto &x : ss)
        addOr(2 * x.first + 1, 2 * x.second);

    SCC scc(adj);
    auto assignments = scc.GetScc().second;
    vector<int> res(m);
    for (size_t i = 0; i < 2 * m; i += 2)
    {
        db(i, assignments[i], assignments[i + 1]);
        if (assignments[i] == assignments[i + 1])
        {
            cout << "No\n";
            return;
        }
        res[i / 2] = assignments[i] > assignments[i + 1];
    }
    db(res);
    cout << "Yes\n";
    cout << count(all(res), 1) << '\n';
    for (size_t i = 0; i < m; i++)
        if (res[i])
            cout << i + 1 << ' ';
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}