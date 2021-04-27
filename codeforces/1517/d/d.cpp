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

void solveCase()
{
    int n = 500, m = 500, k = 20;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> adj(n * m);
    auto getidx = [&](int i, int j) -> int {
        return i * m + j;
    };
    auto getp = [&](int idx) -> pair<int, int> {
        return make_pair(idx / m, idx % m);
    };
    auto d = [&](pair<int, int> a, pair<int, int> b) -> int {
        return abs(a.first - b.first) + abs(a.second - b.second);
    };
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j + 1 < m; j++)
        {
            int x = rand() % NAX;
            cin >> x;
            adj[getidx(i, j)].pb({getidx(i, j + 1), x});
            adj[getidx(i, j + 1)].pb({getidx(i, j), x});
        }
    }
    for (size_t i = 0; i + 1 < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            int x = rand() % NAX;
            cin >> x;
            adj[getidx(i, j)].pb({getidx(i + 1, j), x});
            adj[getidx(i + 1, j)].pb({getidx(i, j), x});
        }
    }
    db(n, m, k);
    if (k & 1)
    {
        for (size_t i = 0; i < n; i++)
        {
            // cerr << i << '\n';
            for (size_t j = 0; j < m; j++)
            {
                cout << -1 << ' ';
            }
            cout << '\n';
        }
        return;
    }
    k /= 2;
    vector<int> ways(n * m);
    for (int k1 = 0; k1 < k; ++k1)
    {
        vector<int> ways2(n * m, MOD);
        for (size_t i = 0; i < n * m; i++)
            for (auto &x : adj[i])
                ways2[x.first] = min(ways2[x.first], ways[i] + x.second);
        ways.swap(ways2);
    }
    for (size_t i = 0; i < n * m; i++)
    {
        cout << 2 * ways[i] << ' ';
        if ((i + 1) % m == 0)
            cout << '\n';
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