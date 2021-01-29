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

vector<vector<int>> divisors(NAX);

void pre()
{
    for (size_t i = 1; i < NAX; i++)
        for (size_t j = i; j < NAX; j += i)
            divisors[j].pb(i);
}

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> mp, dp;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        mp[a[i]]++;
    }

    sort(all(a));
    // reverse(all(a));

    int res = n;
    for (size_t i = 0; i < n; i++)
    {
        int temp = 0;

        if (dp[a[i]])
            dp[a[i]]++;
        else
        {
            for (auto &x : divisors[a[i]])
                if (x != a[i])
                    temp = max(temp, dp[x]);
            dp[a[i]] += temp + 1;
        }
        db(i, a[i], temp, dp[a[i]]);
        res = min(res, n - dp[a[i]]);
    }
    cout << res << '\n';
}

int32_t main()
{
    pre();
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