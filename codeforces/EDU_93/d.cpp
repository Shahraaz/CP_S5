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

const int NAX = 200 + 5, MOD = 1000000007;

ll dp[NAX][NAX][NAX];

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int r, g, b;
        cin >> r >> g >> b;
        vector<int> R(r), G(g), B(b);
        for (auto &x : R)
            cin >> x;
        for (auto &x : G)
            cin >> x;
        for (auto &x : B)
            cin >> x;
        sort(all(R));
        sort(all(G));
        sort(all(B));
        reverse(all(R));
        reverse(all(G));
        reverse(all(B));
        memset(dp, -1, sizeof dp);
        function<ll(int, int, int)> solve = [&](int ridx, int gidx, int bidx) -> ll {
            ll &ret = dp[ridx][gidx][bidx];
            if (ret >= 0)
                return ret;
            ret = 0;
            if (ridx < r)
            {
                if (gidx < g)
                    ret = max(ret, R[ridx] * G[gidx] + solve(ridx + 1, gidx + 1, bidx));
                if (bidx < b)
                    ret = max(ret, R[ridx] * B[bidx] + solve(ridx + 1, gidx, bidx + 1));
            }
            if (gidx < g)
                if (bidx < b)
                    ret = max(ret, B[bidx] * G[gidx] + solve(ridx, gidx + 1, bidx + 1));
            return ret;
        };
        cout << solve(0, 0, 0) << '\n';
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
