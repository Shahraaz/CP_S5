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
    int n = 1e5;
    cin >> n;
    vector<pair<int, int>> a;
    for (int i = 1; i <= n; i++)
    {
        int x = n - i + 1;
        cin >> x;
        a.pb({x, i});
    }
    ll res = 0;
    sort(all(a));
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            int sum = a[i].second + a[j].second;
            ll prod = a[i].first * 1LL * a[j].first;
            if (prod > 2 * n)
                break;
            if (sum == prod)
                res++;
        }
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
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}