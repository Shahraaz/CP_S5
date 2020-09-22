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
    int n;
    cin >> n;
    int totalTime = 0;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        totalTime += x;
    }
    int m;
    cin >> m;
    int ans = MOD;
    for (size_t i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        if (totalTime <= l)
        {
            ans = min(ans, l);
        }
        else if (l <= totalTime && totalTime <= r)
        {
            ans = totalTime;
            break;
        }
        else
        {
        }
    }
    if (ans == MOD)
        ans = -1;
    cout << ans << '\n';
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