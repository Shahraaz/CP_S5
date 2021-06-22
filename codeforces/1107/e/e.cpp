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
const int NAX = 100 + 5, MOD = 1000000007;

int n;
string str;
ll dp[NAX][NAX][NAX];
int a[NAX];

ll solve(int l, int r, int tgt)
{
    if (l > r)
        return 0;
    auto &ret = dp[l][r][tgt];
    if (ret >= 0)
        return ret;
    if (l == r)
        return ret = a[tgt];
    ret = a[tgt] + solve(l + 1, r, 1);
    for (size_t i = l + 1; i <= r; i++)
        if (str[i] == str[l])
            ret = max(ret, solve(l + 1, i - 1, 1) + solve(i, r, tgt + 1));
    db(l, r, tgt, ret);
    return ret;
}

void solveCase()
{
    cin >> n;
    cin >> str;
    for (size_t i = 0; i < n; i++)
        cin >> a[i + 1];
    memset(dp, -1, sizeof dp);
    cout << solve(0, n - 1, 1) << '\n';
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