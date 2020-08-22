// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> adj[n];
    db(n);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        db(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int m;
    cin >> m;
    db(m);
    vector<ll> vecc(m);
    for (auto &x : vecc)
        cin >> x;
    sort(all(vecc));
    while (vecc.size() >= n)
    {
        auto temp = vecc.back();
        vecc.pop_back();
        vecc.back() = (vecc.back() * temp) % MOD;
    }
    ll res = 0;
    vector<int> subTreeSize(n);
    vector<ll> edgeContribution;
    function<void(int, int)> dfs = [&](int node, int par) -> void {
        auto &sz = subTreeSize[node];
        sz++;
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            dfs(x, node);
            ll down = subTreeSize[x];
            ll up = n - down;
            sz += down;
            edgeContribution.pb(up * down);
        }
        db(node, par, sz);
    };
    dfs(0, 0);
    sort(all(edgeContribution));
    db(edgeContribution);
    db(vecc);
    while (edgeContribution.size() && vecc.size())
    {
        res = (res + edgeContribution.back() * vecc.back() % MOD) % MOD;
        edgeContribution.pop_back();
        vecc.pop_back();
    }
    while (edgeContribution.size())
    {
        res = (res + edgeContribution.back()) % MOD;
        edgeContribution.pop_back();
    }
    cout << res << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
