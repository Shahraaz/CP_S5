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
    int b1, k;
    cin >> b1 >> k;
    vector<int> b(k);
    for (auto &x : b)
    {
        cin >> x;
    }
    reverse(all(b));
    ll n = 0, B = 1;
    for (auto &x : b)
    {
        n = n + B * x;
        n %= 2;
        B *= b1;
        B %= 2;
        db(x, n, B);
    }
    if (n & 1)
        cout << "odd";
    else
        cout << "even";
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
