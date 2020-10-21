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
    string str;
    cin >> str;
    int n = str.size();
    if (n & 1)
    {
        int lenM1 = (n - 3) / 2;
        int lenM2 = lenM1;
        cout << 3 << '\n';
        cout << "L " << 2 + lenM1 << '\n';
        n += lenM1 + 1;
        db(n);
        cout << "R " << 2 + lenM1 << '\n';
        n += 2 * lenM1 + 2;
        db(n);
        cout << "R " << n - lenM1 - 1 << '\n';
    }
    else
    {
        int lenM1 = (n - 2) / 2;
        int lenM2 = lenM1;
        cout << 3 << '\n';
        cout << "L " << lenM1 + 1 << '\n';
        n += lenM1;
        db(n);
        cout << "R " << lenM1 + 1 << '\n';
        n += 2 * lenM1 + 1;
        db(n);
        cout << "R " << n - lenM1 << '\n';
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
