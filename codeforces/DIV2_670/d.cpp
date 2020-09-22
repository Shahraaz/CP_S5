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

ll a[NAX], n, sumg, suml, a1;

void solveCase()
{
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        if (i > 0)
            (a[i] > a[i - 1]) ? sumg += a[i] - a[i - 1] : suml += a[i] - a[i - 1];
    }
    a1 = a[0];
    for (int i = n - 1; i > 0; i--)
        a[i] -= a[i - 1];
    auto check = [&]() -> ll {
        return ceil((a1 + sumg) / 2.0);
    };
    auto cg = [&](int x, int t) {
        if (x >= n)
            return;
        a[x] > 0 ? sumg -= a[x] : suml += a[x];
        a[x] += t;
        a[x] > 0 ? sumg += a[x] : suml -= a[x];
    };
    cout << check() << '\n';
    int q;
    cin >> q;
    for (size_t i = 0; i < q; i++)
    {
        int l, r, x;
        cin >> l >> r >> x;
        --l;
        --r;
        if (l == 0)
            a1 += x;
        else
            cg(l, x);
        cg(r + 1, -x);
        cout << check() << '\n';
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
