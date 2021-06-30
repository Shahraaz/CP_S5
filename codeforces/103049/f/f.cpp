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

#define int ll

struct interaction
{
    int dx, dv;
    int a, b;
    interaction(int x, int v, int id1, int id2)
    {
        a = id1;
        b = id2;
        assert(a < b);
        assert(x > 0 && v > 0);
        // int g = __gcd(x, v);
        dx = x;
        dv = v;
    }
    bool operator<(const interaction &rhs) const
    {
        if (dx * 1LL * rhs.dv == rhs.dx * 1LL * dv)
            return a == rhs.a ? a < rhs.a : b < rhs.b;
        return dx * 1LL * rhs.dv > rhs.dx * 1LL * dv;
    }
};

ostream &operator<<(ostream &os, const interaction &rhs)
{
    os << "interaction " << rhs.dx << ' ' << rhs.dv << ' ' << rhs.a << ' ' << rhs.b << ' ';
    return os;
}

void solveCase()
{
    int n;
    cin >> n;
    set<pair<int, pair<int, int>>> ss;
    vector<int> xcord(n), vcord(n);
    for (size_t i = 0; i < n; i++)
    {
        int x, v;
        cin >> x >> v;
        xcord[i] = x;
        vcord[i] = v;
        ss.insert({x, {v, i}});
    }
    vector<bool> vis(n);
    priority_queue<interaction> adj_drones;
    db(xcord);
    db(ss);
    for (auto it = ss.begin(); next(it) != ss.end(); it = next(it))
    {
        int dv = it->second.first - next(it)->second.first;
        db(dv);
        if (dv > 0)
            adj_drones.push(interaction(next(it)->first - it->first, dv, it->second.second, next(it)->second.second));
    }
    // db(adj_drones);
    while (adj_drones.size())
    {
        // db(adj_drones);

        
        db(ss);
        auto top = (adj_drones.top());
        adj_drones.pop();
        if (vis[top.a] || vis[top.b])
            continue;
        vis[top.a] = vis[top.b] = true;
        int xa = xcord[top.a];
        int xb = xcord[top.b];
        auto a_it = ss.lower_bound({xa, {-MOD, -MOD}});
        auto b_it = ss.lower_bound({xb, {-MOD, -MOD}});
        assert(a_it->first == xa);
        assert(b_it->first == xb);
        if (a_it != ss.begin() && next(b_it) != ss.end())
        {
            auto prev_a = prev(a_it);
            auto next_b = next(b_it);
            int dv = prev_a->second.first - next_b->second.first;
            if (dv > 0)
                adj_drones.push(interaction(next_b->first - prev_a->first, dv, prev_a->second.second, next_b->second.second));
        }
        ss.erase(a_it);
        ss.erase(b_it);
    }
    db(ss);
    cout << count(all(vis), false) << '\n';
    vector<int> speeds;
    for (size_t i = 0; i < n; i++)
    {
        if (vis[i] == false)
        {
            cout << i + 1 << ' ';
            speeds.pb(vcord[i]);
        }
    }
    if (speeds.size())
        assert(is_sorted(all(speeds)));
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