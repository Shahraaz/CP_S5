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
    void solveCase()
    {
        int n;
        cin >> n;
        deque<int> p(2 * n);
        for (size_t i = 0; i < 2 * n; i++)
            cin >> p[i];
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(2, -1)));
        function<int(int, int, int)> solve = [&](int s1, int s2, int state) -> int {
            int idx = 2 * n - s1 - s2;
            if (idx <= 0)
                return 1;
            if (s1 == 0 || s2 == 0)
                return true;
            int &ret = dp[s1][s2][state];
            if (ret >= 0)
                return ret;
            ret = false;
            if (state == 0)
            {
            }
            else
            {
            }
            return ret;
        };
        if (solve(n, n, 0))
            cout << "YES\n";
        else
            cout << "NO\n";
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
