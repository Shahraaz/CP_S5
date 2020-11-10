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
    ll a, b, q;
    cin >> a >> b >> q;
    if (a > b)
        swap(a, b);
    auto g = a * b / __gcd(a, b);
    db(a, b, q);
    auto count = [&](ll x) -> ll {
        ll ret = (x / g) * b;
        db(ret);
        if (x % g < b)
            ret += x % g + 1;
        else
            ret += b;
        db(a, b, g, x, ret);
        return ret;
    };
    auto slow = [&](ll l, ll r) {
        ll res = 0;
        while (l <= r)
        {
            res += (l % a) % b != (l % b) % a;
            ++l;
        }
        cout << res << '\n';
    };
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        ll cnt = r - l + 1;
        cnt -= count(r) - count(l - 1);
        cout << cnt << ' ';
#ifdef LOCAL
        slow(l, r);
#endif
        // db("\n");
    }
    cout << '\n';
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
