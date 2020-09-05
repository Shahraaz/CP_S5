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

const int NAX = 2e3 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

int dp[NAX][NAX];

void Solution::solveCase()
{
    int n, k;
    cin >> n >> k;
    vector<int> curr(n);
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        int num = 0;
        for (auto &x : str)
            num = num * 2 + x - '0';
        curr[i] = num;
    }
    vector<int> maskOfNumber(10);
    vector<string> ss = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};
    for (size_t i = 0; i < 10; i++)
    {
        int num = 0;
        for (auto &x : ss[i])
            num = num * 2 + x - '0';
        maskOfNumber[i] = num;
    }
    memset(dp, -1, sizeof dp);
    vector<int> toPrint;
    function<bool(int, int)> solve = [&](int pos, int rem) -> bool {
        if (rem < 0)
            return 0;
        if (pos == n)
            return rem == 0;
        int &ret = dp[pos][rem];
        if (ret >= 0)
            return ret;
        ret = 0;
        for (int i = 10 - 1; i >= 0; i--)
            if ((maskOfNumber[i] | curr[pos]) == maskOfNumber[i])
            {
                db(pos, i, curr[pos]);
                int diff = maskOfNumber[i] ^ curr[pos];
                int cnt = __builtin_popcount(diff);
                if (solve(pos + 1, rem - cnt))
                {
                    toPrint.pb(i);
                    ret = 1;
                    break;
                }
            }
        db(pos, rem, ret);
        return ret;
    };
    if (solve(0, k))
    {
        reverse(all(toPrint));
        for (auto &x : toPrint)
        {
            cout << x;
        }
    }
    else
    {
        cout << -1 << '\n';
    }
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
