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

const int NAX = 1e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

// vector<int> divisors[NAX];

int cnt[NAX];

void Solution::solveCase()
{
    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<int> pow2(n + 1);
    pow2[0] = 1;
    for (size_t i = 1; i <= n; i++)
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    // for (size_t i = 0; i <= n; i++)
    //     pow2[i] = (pow2[i] - 1 + MOD) % MOD;
    vector<int> dp(NAX);
    for (int i = NAX - 1; i >= 1; i--)
    {
        int temp = 0;
        int totCnt = 0;
        for (size_t j = i; j < NAX; j += i)
        {
            totCnt += cnt[j];
            temp += dp[j];
            if (temp >= MOD)
                temp -= MOD;
        }
        dp[i] = pow2[totCnt] - 1 + MOD;
        if (dp[i] >= MOD)
            dp[i] -= MOD;
        dp[i] = dp[i] - temp + MOD;
        if (dp[i] >= MOD)
            dp[i] -= MOD;
    }
    cout << dp[1] << '\n';
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
