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

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    ll l, r;
    cin >> l >> r;
    ll dp[20][5][2];
    auto count = [&](ll lim) -> ll {
        if (lim == 0)
            return 0;
        if (lim < 10)
            return lim;
        memset(dp, -1, sizeof dp);
        auto N = to_string(lim);
        function<ll(int, int, bool)> solve = [&](int pos, int cnt, bool b) -> ll {
            if (cnt < 0)
                return 0;
            if (pos == N.size())
                return 1;
            auto &ret = dp[pos][cnt][b];
            if (ret >= 0)
                return ret;
            ret = 0;
            if (b)
            {
                ret += solve(pos + 1, cnt, '0' == N[pos]);
                for (int i = '1'; i <= N[pos]; i++)
                    ret += solve(pos + 1, cnt - 1, i == (N[pos]));
            }
            else
            {
                ret += solve(pos + 1, cnt, 0);
                ret += 9 * solve(pos + 1, cnt - 1, 0);
            }
            db(pos, cnt, b, ret);
            return ret;
        };
        ll res = 0;
        for (char c = '1'; c <= N[0]; c++)
            res += solve(1, 2, c == N[0]);
        for (size_t i = 1; i < N.size(); i++)
            res += 9 * solve(i + 1, 2, 0);
        db(lim, res);
        return res;
    };
    cout << count(r) - count(l - 1) << '\n';
}

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
