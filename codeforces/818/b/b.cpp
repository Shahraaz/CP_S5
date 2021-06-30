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
    int n, m;
    cin >> n >> m;
    vector<int> l(m);
    for (auto &x : l)
    {
        cin >> x;
        --x;
    }
    vector<int> a(n, -1);
    vector<bool> vis(n + 1);
    for (size_t i = 0; i + 1 < m; i++)
    {
        int diff = 0;
        if (l[i] == l[i + 1])
            diff = n;
        else if (l[i] < l[i + 1])
            diff = l[i + 1] - l[i];
        else
            diff = n - l[i] + l[i + 1];
        db(i, l[i], l[i + 1], diff, a[l[i]]);
        if (a[l[i]] == diff)
            continue;
        if (vis[diff] || (a[l[i]] != -1))
        {
            cout << -1 << '\n';
            return;
        }
        a[l[i]] = diff;
        vis[diff] = 1;
    }
    for (size_t i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        for (size_t j = 0; j < n; j++)
        {
            if (a[j] == -1)
            {
                a[j] = i;
                break;
            }
        }
    }
    for (auto &x : a)
    {
        cout << x << ' ';
    }
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