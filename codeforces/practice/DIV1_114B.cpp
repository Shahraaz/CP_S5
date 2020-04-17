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

double dp[NAX][NAX][NAX], p[NAX];
int a[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, l, k;
        cin >> n >> l >> k;
        for (size_t i = 0; i < n; i++)
        {
            cin >> p[i];
            p[i] /= 100;
        }
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
            // a[i]++;
        }
        if (l > n)
        {
            cout
                << 0 << '\n';
            return;
        }
        memset(dp, -1, sizeof dp);
        function<double(int, int, int)> solve = [&](int pos, int currWinCnt, int bagCapaity) -> double {
            if (pos == n)
                return currWinCnt >= l && currWinCnt <= bagCapaity;
            auto &ret = dp[pos][currWinCnt][bagCapaity];
            if (ret >= 0)
                return ret;
            ret = (1 - p[pos]) * solve(pos + 1, currWinCnt, bagCapaity);
            if (a[pos] != -1)
                ret += p[pos] * solve(pos + 1, currWinCnt + 1, min(200, bagCapaity + a[pos] + 1));
            else
                ret += p[pos] * solve(pos + 1, currWinCnt + 1, min(200, bagCapaity));
            db(pos, currWinCnt, bagCapaity, ret);
            return ret;
        };
        cout << fixed << setprecision(9);
        cout << solve(0, 0, k) << '\n';
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
