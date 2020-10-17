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

const int NAX = 3e5 + 5, MOD = 1000000007;

// ll dp[NAX][3];
vector<vector<ll>> dp;
int n;
vector<pair<ll, ll>> ab;
const ll LIM = 1e18 + 1;

ll solve(int idx, int prevExt)
{
    if (idx == n)
        return 0;
    auto &ret = dp[idx][prevExt];
    if (ret >= 0)
        return ret;
    ret = LIM;
    ll prevHt = prevExt;
    if (idx > 0)
        prevHt += ab[idx - 1].f;
    else
        prevHt += -10;
    for (int i = 0; i < 3; i++)
        if (ab[idx].f + i != prevHt)
            ret = min(ret, solve(idx + 1, i) + i * ab[idx].s);
    return ret;
}

void solveCase()
{
    cin >> n;
    ab = vector<pair<ll, ll>>(n);
    for (size_t i = 0; i < n; i++)
        cin >> ab[i].f >> ab[i].s;
    // memset(dp, -1, sizeof dp);
    dp = vector<vector<ll>>(n, vector<ll>(3, -1));
    
    cout << min({solve(0, 0)}) << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
