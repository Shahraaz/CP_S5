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

void solveCase()
{
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (auto &x : a)
    {
        cin >> x;
    }
    db(a);
    int SQRT = sqrt(n) + 1;
    vector<vector<vector<ll>>> dp(SQRT, vector<vector<ll>>(SQRT, vector<ll>(2, -1)));
    function<ll(int, int, int)> solve = [&](int idx, int pos, int turn) -> ll {
        if (pos == SQRT || (pos + idx * SQRT) >= n)
            return 0;
        auto &ret = dp[idx][pos][turn];
        if (ret >= 0)
            return ret;
        ret = solve(idx, pos + 1, turn);
        if (turn == 0)
            ret = max(ret, a[pos + idx * SQRT] + solve(idx, pos + 1, 1));
        else
            ret = max(ret, -a[pos + idx * SQRT] + solve(idx, pos + 1, 0));
        return ret;
    };
    for (size_t i = 0; i < SQRT; i++)
        solve(i, 0, 0);
    function<ll(int, int)> solve2 = [&](int idx, int turn) -> ll {
        if (idx == SQRT)
            return 0;
        ll ret = solve2(idx + 1, turn);
        ret = max(ret, dp[idx][0][turn] + solve2(idx + 1, 1 - turn));
        ret = max(ret, dp[idx][0][turn] + solve2(idx + 1, turn));
        return ret;
    };
    cout << solve2(0, 0) << '\n';
    for (size_t i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        --l, --r;
        int idx1 = l / SQRT;
        int idx2 = r / SQRT;
        swap(a[l], a[r]);
        dp[idx1] = vector<vector<ll>>(SQRT, vector<ll>(2, -1));
        solve(idx1, 0, 0);
        if (idx2 != idx1)
        {
            dp[idx2] = vector<vector<ll>>(SQRT, vector<ll>(2, -1));
            solve(idx2, 0, 0);
        }
        cout << solve2(0, 0) << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
