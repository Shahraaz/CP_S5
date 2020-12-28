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

vector<int> factore(int x)
{
    vector<int> divisors = {1};
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            divisors.pb(i);
            if (i * i != x)
                divisors.pb(x / i);
        }
    if (x > 1)
        divisors.pb(x);
    sort(all(divisors));
    return divisors;
}

void solveCase()
{
    const int LIM = 10;
    int n;
    cin >> n;
    int lim = (n - 1) * (n - 2) / 2;
    int k;
    cin >> k;
    db(n, lim, k);
    if (k == 1)
    {
        cout << n - 1 << '\n';
        for (size_t i = 1; i + 1 <= n; i++)
            cout << i << ' ' << i + 1 << '\n';
        return;
    }
    if (k == (n) * (n - 1) / 2)
    {
        cout << k << '\n';
        for (size_t i = 1; i <= n; i++)
            for (size_t j = i + 1; j <= n; j++)
                cout << i << ' ' << j << '\n';
        return;
    }
    if (k > lim)
    {
        cout << -1 << '\n';
        // continue;
        return;
    }
    vector<pair<int, int>> edges;
    for (size_t i = 2; i <= n; i++)
        edges.emplace_back(1, i);
    int temp = n * (n - 1) / 2 - k;
    for (size_t i = 2; i <= n; i++)
        for (size_t j = i + 1; j <= n; j++)
            if (edges.size() < temp)
            {
                edges.pb({i, j});
            }
    cout << edges.size() << '\n';
    for (auto &x : edges)
    {
        cout << x.first << ' ' << x.second << '\n';
    }
}

int32_t main()
{
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