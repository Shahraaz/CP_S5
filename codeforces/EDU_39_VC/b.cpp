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

void my_gcd(ll &a, ll &b)
{
    if (a == 0 || b == 0)
        return;
    if (a < 2 * b && b < 2 * a)
        return;
    db(a, b);
    if (b)
        a %= 2 * b;
    db(a);
    if (a)
        b %= 2 * a;
    db(b);
    my_gcd(a, b);
}

void solveCase()
{
    ll n, m;
    cin >> n >> m;
    my_gcd(n, m);
    cout << n << ' ' << m << '\n';
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
