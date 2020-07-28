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
        p.pb(INT_MAX);
        vector<int> batch;
        int mx = p[0];
        batch.pb(0);
        db(p);
        for (size_t i = 0; i <= 2 * n; i++)
            if (p[i] > mx)
            {
                batch.pb(i);
                mx = p[i];
            }
        db(batch);
        vector<int> setSizes;
        for (size_t i = 1; i < batch.size(); i++)
            setSizes.pb(batch[i] - batch[i - 1]);
        db(setSizes);
        sort(all(setSizes));
        vector<bool> dp(n + 1);
        dp[0] = 1;
        for (size_t i = 0; i < setSizes.size(); i++)
            for (int j = n; j >= 0; j--)
                if (j - setSizes[i] >= 0 && dp[j - setSizes[i]])
                    dp[j] = 1;
        if (dp[n])
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
