#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

ll fib[NAX];

void solveCase()
{
    int n, m;
    cin >> n >> m;
    fib[1] = 2;
    fib[2] = 4;
    for (size_t i = 3; i < NAX; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
        if (fib[i] >= MOD)
            fib[i] -= MOD;
    }
    cout << (fib[n] + fib[m] - 2 + MOD) % MOD << '\n';
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
        solveCase();
    return 0;
}