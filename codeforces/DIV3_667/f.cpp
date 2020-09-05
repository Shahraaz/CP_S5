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

struct Solution
{
    Solution() {}
    void solveCase();
};

int dp[NAX][NAX][2];

void Solution::solveCase()
{
    int n, k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;
    function<int(int, int, int)> solve = [&](int pos, int rem, int toCheck) -> int {
        if (rem < 0)
            return -MOD;
        if (pos == n)
            return 0;
        int &ret = dp[pos][rem][toCheck];
        if (ret >= 0)
            return ret;
        ret = solve(pos + 1, rem, 0);
        // ret = 0;
        if (toCheck == 0)
        {
            if (t[0] == s[pos])
            {
                ret = max(ret, solve(pos + 1, rem, 1));
                ret = max(ret, solve(pos + 1, rem, 0));
            }
            else
            {
                ret = max(ret, solve(pos + 1, rem, 0));
                ret = max(ret, 1 + solve(pos + 1, rem - 1, 1));
            }
        }
        else
        {
            if (t[1] == s[pos])
            {
                if (t[0] == s[pos])
                {
                    ret = max(ret, 1 + solve(pos + 1, rem, 1));
                    ret = max(ret, 1 + solve(pos + 1, rem, 0));
                }
                else
                {
                    ret = max(ret, 1 + solve(pos + 1, rem, 0));
                    // ret = max(ret, 1 + solve(pos + 1, rem, 0));
                }
            }
            else
            {
                ret = max(ret, solve(pos + 1, rem, 0));
                if (t[0] == s[pos])
                {
                    ret = max(ret, 1 + solve(pos + 1, rem - 1, 1));
                    ret = max(ret, 1 + solve(pos + 1, rem - 1, 0));
                }
                else
                    ret = max(ret, 1 + solve(pos + 1, rem - 1, 0));
            }
        }
        return ret;
    };
    cout << solve(0, k, 0) << '\n';
}

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
