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

const int NAX = 1e6 + 5, MOD = 1000000007;

vector<ll> poses[NAX];

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        if (poses[a[i]].size() == 0)
            poses[a[i]].pb(0);
        poses[a[i]].pb(i + 1);
    }
    ll res = 0;
    // for (size_t i = 0; i < n; i++)
    // {
    //     for (size_t j = i; j < n; j++)
    //     {
    //         set<int> ss;
    //         int l = min(i, j);
    //         int r = max(i, j);
    //         for (size_t k = l; k <= r; k++)
    //             ss.insert(a[k]);
    //         res += ss.size();
    //         // db(i, j, ss.size());
    //     }
    // }
    // db(res);
    // res = 2 * res - n;
    // cout << (1.0 * res / n / n) << '\n';
    res = 0;
    for (int i = 0; i < NAX; i++)
        if (poses[i].size())
        {
            db(i, poses[i]);
            for (size_t j = 1; j < poses[i].size(); j++)
                res += (poses[i][j] - poses[i][j - 1]) * (n - poses[i][j] + 1);
        }
    res = 2 * res - n;
    cout << fixed << setprecision(9);
    cout << (1.0 * res / n / n) << '\n';
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
