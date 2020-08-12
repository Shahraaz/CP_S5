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

const int NAX = 3e6 + 5, MOD = 1000000007;

ll cnt[NAX];
ll ans[NAX];
ll a[NAX];

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
            cnt[a[i]]++;
        }
        // ans[1] = cnt[1] * cnt[1];
        for (ll i = 1; i < NAX; i++)
            if (cnt[i])
            {
                for (ll j = 1; i * j < NAX; j++)
                {
                    if (i != j)
                        ans[i * j] += cnt[i] * cnt[j];
                    else
                        ans[i * j] += cnt[i] * (cnt[i] - 1);
                }
                db(i, ans[i]);
            }
        for (ll i = 1; i < NAX; i++)
            ans[i] += ans[i - 1];
        int m;
        cin >> m;
        for (size_t i = 0; i < m; i++)
        {
            int p;
            cin >> p;
            cout << n * (n - 1LL) - ans[p - 1] << '\n';
        }
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
