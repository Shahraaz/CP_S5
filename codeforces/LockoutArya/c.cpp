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
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    sort(all(a));
    int smallSize = n / k;
    int largeSize = smallSize + 1;
    int largeCnt = n % k;
    int smallCnt = k - n % k;
    vector<vector<ll>> dp(largeCnt + 1, vector<ll>(smallCnt + 1, 1e15));
    dp[0][0] = 0;
    for (int currLarge = 0; currLarge <= largeCnt; currLarge++)
        for (int currSmall = 0; currSmall <= smallCnt; currSmall++)
        {
            int pos = currLarge * largeSize + currSmall * smallSize;
            if (currSmall < smallCnt)
                dp[currLarge][currSmall + 1] = min(dp[currLarge][currSmall + 1], dp[currLarge][currSmall] + a[pos + smallSize - 1] - a[pos]);
            if (currLarge < largeCnt)
                dp[currLarge + 1][currSmall] = min(dp[currLarge + 1][currSmall], dp[currLarge][currSmall] + a[pos + largeSize - 1] - a[pos]);
        }
    cout << dp[largeCnt][smallCnt] << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
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
