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
    int a;
    cin >> a;
    int maxGcd = 1;
    // for (int i = 1; i < a; i++)
    // {
    //     if (__gcd(i + a, a & i) > __gcd(maxGcd + a, a & maxGcd))
    //         maxGcd = i;
    // }
    // cout << bitset<16>(maxGcd) << '\n';
    // cout << bitset<16>(a) << '\n';
    // cout << __gcd(a + maxGcd, a & maxGcd) << '\n';
    int b = 0;
    int cnt = __lg(a);
    for (int i = 0; i < cnt; i++)
    {
        if (a & (1 << i))
            ;
        else
            b |= 1 << i;
    }
    if (b == 0)
    {
        //     cout << 1 << '\n';
        //     return;
        b = 1;
        for (ll i = 2; i * i <= a; i++)
            if (a % i == 0)
                b = max(b, (int)(a / i));
    }
    // cout << bitset<10>(b) << '\n'
    //      << bitset<10>(a) << '\n';
    cout << __gcd(b + a, a & b) << '\n';
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
