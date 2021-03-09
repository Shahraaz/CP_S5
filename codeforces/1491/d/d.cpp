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
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<set<int>> ss(n);
    for (int i = 1; i < n; i++)
    {
        for (int s = i; s; s = i & (s - 1))
        {
            if (i + s < n)
            {
                adj[i + s].pb(i);
                ss[i + s].insert(i);
            }
            // db(i, s, i + s, bitset<10>(i), bitset<10>(i + s));
        }
        for (auto &x : adj[i])
            for (auto &y : ss[x])
                ss[i].insert(y);
        // db(i, adj[i], ss[i]);
        // db(i, ss[i]);
        // db(i, adj[i]);
        if (i & 1)
            continue;
        cout << bitset<6>(i) << ": ";
        for (auto &x : ss[i])
            cout << bitset<6>(x) << ' ';
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