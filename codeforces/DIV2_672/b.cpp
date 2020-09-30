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
    int n;
    cin >> n;
    vector<int> vecc[32];
    int zebra = 0;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        bool ok = 0;
        for (int i = 31 - 1; i >= 0; i--)
        {
            if (x & (1 << i))
            {
                vecc[i].pb(x);
                ok = true;
                break;
            }
        }
        zebra += ok == 0;
    }
    ll res = 0;
    for (int i = 31 - 1; i >= 0; i--)
    {
        res += vecc[i].size() * (vecc[i].size() - 1LL) / 2;
    }
    res += zebra * (zebra - 1LL) / 2;
    cout << res << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
