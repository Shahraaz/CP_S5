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

const int NAX = 100 + 5, MOD = 1000000007;

int dp[NAX][2 * NAX];

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n, k, l;
        cin >> n >> k >> l;
        vector<ll> a(n + 1);
        a[0] = -MOD;
        for (size_t i = 0; i < n; i++)
            cin >> a[i + 1];
        vector<int> p;
        for (size_t i = 0; i < k; i++)
            p.pb(i);
        for (int i = k; i >= 1; i--)
            p.pb(i);
        memset(dp, -1, sizeof dp);
        function<int(int, int)> solve = [&](int pos, int t) -> int {
            if (pos == (n + 1))
                return 1;
            t %= (2 * k);
            int &ret = dp[pos][t];
            if (ret >= 0)
                return ret;
            ret = false;
            if (p[t] + a[pos] <= l)
                ret = solve(pos + 1, t + 1) || solve(pos, t + 1);
            return ret;
        };
        if (solve(0, 0))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
};

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
