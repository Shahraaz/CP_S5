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
        vector<pair<ll, ll>> a(n);
        for (auto &x : a)
            cin >> x.f >> x.s;
        map<pair<ll, ll>, int> cnt;
        ll res = 0;
        sort(all(a));
        for (size_t i = 0; i < n; i++)
            for (size_t j = i + 1; j < n; j++)
            {
                ll temp = cnt[{a[i].f - a[j].f, a[i].s - a[j].s}]++;
                res += temp;
            }
        db(res);
        db(cnt);
        // for (auto &x : cnt)
        // {
        //     res += x.s * 1LL * (x.s - 1) / 2;
        // }
        res /= 2;
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
