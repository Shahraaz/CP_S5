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

ll dp[31][31][51];
class Solution
{
private:
    ll solve(int n, int m, int k)
    {
        if (k > n * m || k < 0)
            return 1e18;
        if (k == n * m)
            return 0;
        if (k == 0)
            return 0;
        if (n > m)
            swap(n, m);
        ll &ret = dp[n][m][k];
        if (ret >= 0)
            return ret;
        ret = 1e18;
        for (int i = 0; i <= k; i++)
        {
            for (int j = 1; j < n; j++)
                ret = min(ret, solve(j, m, i) + solve(n - j, m, k - i) + m * m);
            for (int j = 1; j < m; j++)
                ret = min(ret, solve(n, j, i) + solve(n, m - j, k - i) + n * n);
        }
        db(n, m, k, ret);
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int q;
        cin >> q;
        memset(dp, -1, sizeof dp);
        while (q--)
        {
            int n, m, k;
            cin >> n >> m >> k;
            cout << solve(n, m, k) << '\n';
        }
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
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
