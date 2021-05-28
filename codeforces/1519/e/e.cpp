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

struct Line
{
    int a, b, c, d;
    Line(int _a = 0, int _b = 0, int _c = 0, int _d = 0) : a(_a), b(_b), c(_c), d(_d) {}
    pair<ll, ll> up()
    {

        ll num = (c + d) * 1LL * b;
        ll den = a * 1LL * d;
        auto g = __gcd(num, den);
        return {num / g, den / g};
    }
    pair<ll, ll> right()
    {
        ll num = c * 1LL * b;
        ll den = (a + b) * 1LL * d;
        auto g = __gcd(num, den);
        return {num / g, den / g};
    }
};

void solveCase()
{
    int n;
    cin >> n;
    vector<Line> lines(n);
    map<pair<ll, ll>, int> ss;

    vector<vector<pair<int, int>>> adj(2 * n);
    int ctr = 0;

    for (size_t i = 0; i < n; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        lines[i] = Line(a, b, c, d);

        auto u = lines[i].up();
        if (ss.count(u) == 0)
            ss[u] = ctr++;

        auto r = lines[i].right();
        if (ss.count(r) == 0)
            ss[r] = ctr++;

        adj[ss[u]].pb({ss[r], i});
        adj[ss[r]].pb({ss[u], i});
    }
    vector<int> vis(ctr);
    // vector<int> used(n);
    vector<pair<int, int>> ret;
    function<int(int, int)> dfs = [&](int node, int par) -> int {
        db(node, par, adj[node]);
        int curr = -1;
        vis[node] = 1;
        for (auto &x : adj[node])
        {
            if (x.first == par || vis[x.first] == 1)
                continue;
            int nw = x.second;
            if (vis[x.first] == 0)
            {
                int tmp = dfs(x.first, node);
                if (tmp != -1)
                {
                    ret.pb({nw, tmp});
                    nw = -1;
                }
            }
            if (nw != -1)
            {
                if (curr != -1)
                {
                    ret.pb({nw, curr});
                    curr = -1;
                }
                else
                    curr = nw;
            }
        }
        vis[node] = 2;
        return curr;
    };
    for (size_t i = 0; i < ctr; i++)
        if (vis[i] == 0)
            dfs(i, i);
    cout << ret.size() << '\n';
    for (auto &x : ret)
        cout << x.first + 1 << ' ' << x.second + 1 << '\n';
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