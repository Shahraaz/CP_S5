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
    vector<int> p(n);
    vector<vector<int>> adj(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> p[i];
        --p[i];
    }
    vector<int> vis(n);
    vector<vector<int>> decomposed;
    for (size_t i = 0; i < n; i++)
    {
        if (vis[i])
            continue;
        int j = i;
        vector<int> curr;
        while (!vis[j])
        {
            curr.pb(j);
            vis[j] = 1;
            j = p[j];
        }
        decomposed.pb(curr);
    }
    sort(all(decomposed), [&](auto &x, auto &y) -> bool { return x.size() < y.size(); });
    if (decomposed[0].size() > 2)
    {
        cout << "NO\n";
        return;
    }
    vector<pair<int, int>> res;
    if (decomposed[0].size() == 2)
        res.pb({decomposed[0][0], decomposed[0][1]});
    for (size_t i = 1; i < decomposed.size(); i++)
    {
        if (decomposed[i].size() % decomposed[0].size())
        {
            cout << "NO\n";
            return;
        }
        for (size_t j = 0; j < decomposed[i].size(); j += decomposed[0].size())
            for (size_t k = 0; k < decomposed[0].size(); k++)
                res.pb({decomposed[0][k], decomposed[i][j + k]});
    }
    cout << "YES\n";
    for (auto &x : res)
    {
        cout << x.first + 1 << ' ' << x.second + 1 << '\n';
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