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

const int NAX_PRIME = 2e5 + 5;
bool is_composite[NAX_PRIME];
vector<int> primes;

void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
            primes.push_back(i);
        for (size_t j = 0; j < primes.size() && ((ll)i * primes[j] < n); j++)
        {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

vector<vector<int>> res(1001);

void solveCase()
{
    int n;
    cin >> n;
    db(n);
    if (n & 1)
    {
        cout << -1 << '\n';
        return;
    }
    if (res[n].size())
    {
        for (auto &x : res[n])
            cout << x << ' ';
        cout << '\n';
        return;
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (is_composite[i + j] == false)
            {
                adj[i].pb(j);
                adj[j].pb(i);
            }
        }
    }
    for (size_t i = 1; i <= n; i++)
    {
        db(i, adj[i]);
    }
    vector<int> vis(n + 1), vis2(n + 1);
    function<void(int, int)> dfs = [&](int node, int par) -> int
    {
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            if (vis[x])
            {
                // nice
            }
        }
    };
}

int32_t main()
{
    seive();
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}