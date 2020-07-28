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
        vector<int> p(n);
        string str;
        // cin >> str;
        for (size_t i = 0; i < n; i++)
        {
            cin >> p[i];
        }
        cin >> str;
        vector<ll> prefSum(n);
        vector<ll> prefSum2(n);
        for (size_t i = 0; i < n; i++)
        {
            if (str[i] == 'A')
                prefSum2[i] = p[i];
            else
                prefSum[i] = p[i];
            if (i > 0)
            {
                prefSum[i] += prefSum[i - 1];
                prefSum2[i] += prefSum2[i - 1];
            }
        }
        ll res = prefSum[n - 1];
        for (size_t i = 0; i < n; i++)
            res = max(res, prefSum[n - 1] - prefSum[i] + prefSum2[i]);
        vector<ll> suffSum(n), suffSum2(n);
        for (int i = n - 1; i >= 0; i--)
        {
            if (str[i] == 'A')
                suffSum2[i] = p[i];
            else
                suffSum[i] = p[i];
            if (i + 1 < n)
            {
                suffSum[i] += suffSum[i + 1];
                suffSum2[i] += suffSum2[i + 1];
            }
        }
        db(prefSum, suffSum);
        for (size_t i = 0; i < n; i++)
            res = max(res, suffSum[0] - suffSum[i] + suffSum2[i]);
        cout << res << '\n';
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
