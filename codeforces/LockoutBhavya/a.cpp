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
    vector<int> a(n);
    for (auto &x : a)
    {
        cin >> x;
    }
    vector<int> strictForwLen(n), strictBackLen(n);
    strictBackLen[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
    {
        if (a[i] < a[i + 1])
            strictBackLen[i] = strictBackLen[i + 1] + 1;
        else
            strictBackLen[i] = 1;
    }
    strictForwLen[0] = 1;
    for (size_t i = 1; i < n; i++)
    {
        if (a[i - 1] < a[i])
            strictForwLen[i] = strictForwLen[i - 1] + 1;
        else
            strictForwLen[i] = 1;
    }
    if (strictBackLen[0] == n)
        cout << n << '\n';
    else
    {
        int maxLen = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (i == 0)
                maxLen = max(maxLen, strictBackLen[1]);
            else if (i == n - 1)
                maxLen = max(maxLen, strictForwLen[n - 2]);
            else if (a[i - 1] < a[i + 1])
                maxLen = max(maxLen, strictForwLen[i - 1] + strictBackLen[i + 1]);
            else
            {
                maxLen = max(maxLen, strictForwLen[i - 1] + 0);
                maxLen = max(maxLen, strictBackLen[i + 1] + 0);
            }
        }
        cout << maxLen << '\n';
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
