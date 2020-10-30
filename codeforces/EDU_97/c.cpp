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

const int NAX = 400 + 5, MOD = 1000000007;

int dp[NAX][NAX];

void solveCase()
{
    int n;
    cin >> n;
    vector<int> vecc(n);
    for (auto &x : vecc)
        cin >> x;
    sort(all(vecc));
    memset(dp, -1, sizeof dp);
    function<int(int, int)> solve = [&](int dishidx, int xCord) -> int {
        if (dishidx == n)
            return 0;
        if (xCord == 404)
            return MOD;
        int &ret = dp[dishidx][xCord];
        if (ret >= 0)
            return ret;
        ret = min(solve(dishidx, xCord + 1), abs(xCord - vecc[dishidx]) + solve(dishidx + 1, xCord + 1));
        db(dishidx, xCord, ret);
        return ret;
    };
    cout << solve(0, 1) << '\n';
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
