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
const int NAX = 3e5 + 5, MOD = 1000000007;

int n, k, c, v, ans = 0, dsu[NAX];
char s[NAX];
vector<int> adj[NAX];

struct node
{
    int l, r, xo;
    node(int _l = 0, int _r = 0, int _xo = 0) : l(_l), r(_r), xo(_xo) {}

    int get() { return min(l, r); }

    void operator+=(node rhs)
    {
        l = min(MOD, l + rhs.l);
        r = min(MOD, r + rhs.r);
    }

} val[NAX];

pair<int, int> trace(int u)
{
    if (dsu[u] < 0)
        return {u, 0};
    auto temp = trace(dsu[u]);
    dsu[u] = temp.first;
    val[u].xo ^= temp.second;
    return {dsu[u], val[u].xo};
}

void solveCase()
{
    cin >> n >> k >> (s + 1);
    for (size_t i = 1; i <= k; i++)
    {
        dsu[i] = -1;
        val[i] = node(1, 0, 0);
        cin >> c;
        while (c--)
        {
            cin >> v;
            adj[v].pb(i);
        }
    }
    for (size_t i = 1; i <= n; i++)
    {
        int typ = (s[i] - '0') ^ 1;
        db(i, typ, ans, adj[i]);
        if (ans != -1)
        {
            if (adj[i].size() == 1)
            {
                pair<int, int> u = trace(adj[i][0]);
                db(u, val[u.first].l, val[u.first].r, val[u.first].xo);
                ans -= val[u.first].get();
                val[u.first] += node((u.second == typ) * MOD, (u.second != typ) * MOD);
                ans += val[u.first].get();
            }
            else if (adj[i].size() == 2)
            {
                pair<int, int> u = trace(adj[i][0]);
                pair<int, int> v = trace(adj[i][1]);
                db(u, val[u.first].l, val[u.first].r, val[u.first].xo);
                db(v, val[v.first].l, val[v.first].r, val[v.first].xo);
                if (u.first != v.first)
                {
                    ans -= val[u.first].get() + val[v.first].get();
                    if (dsu[u.first] > dsu[v.first])
                        swap(u, v);
                    if (u.second ^ v.second ^ typ)
                    {
                        swap(val[v.first].l, val[v.first].r);
                        val[v.first].xo = 1;
                    }
                    dsu[u.first] += dsu[v.first];
                    dsu[v.first] = u.first;
                    val[u.first] += val[v.first];
                    ans += val[u.first].get();
                }
            }
        }
        cout << ans << '\n';
    }
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