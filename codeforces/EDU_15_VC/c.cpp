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
        int n, m;
        cin >> n >> m;
        set<int> s, s2;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            s.insert(x);
        }
        for (size_t i = 0; i < m; i++)
        {
            int x;
            cin >> x;
            s2.insert(x);
        }
        ll res = 0;
        for (auto &x : s)
        {
            auto it = s2.lower_bound(x);
            ll temp = LLONG_MAX;
            if (it != s2.end())
                temp = min(temp, 0LL + *it - x);
            if (it != s2.begin())
            {
                --it;
                temp = min(temp, 0LL + x - *it);
            }
            res = max(res, temp);
        }
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
