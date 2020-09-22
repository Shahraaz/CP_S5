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
    ll n;
    cin >> n;
    ll cnt = 1;
    ll val = 2;
    ll res = 0;
    db(n, cnt, val);
    while (n > 0)
    {
        db(n, cnt, val, res);
        db(n / (val - 1), cnt);
        if (n >= (val - 1) * (val) / 2)
        {
            res += 1;
            n -= (val - 1) * (val) / 2;
            cnt *= 2;
            val *= 2;
        }
        else
        {
            // res += n / (val - 1);
            break;
        }
    }
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
