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

void solveCase()
{
    vector<int> spc = {4, 8, 15, 16, 23, 42};
    vector<int> q(7);
    vector<int> a(7);
    auto ask = [](int i, int j) -> int {
        cout << "? ";
        cout << i << ' ' << j << endl;
        cin >> i;
        if (i == 0)
            exit(0);
        return i;
    };
    int g = 0;
    for (size_t i = 2; i <= 5; i++)
    {
        q[i] = ask(1, i);
        g = __gcd(g, q[i]);
    }
    if (g % 15 == 0)
        g = 15;
    if (g % 23 == 0)
        g = 23;
    a[1] = g;
    for (size_t i = 2; i <= 5; i++)
        a[i] = q[i] / a[1];
    long long al = 1;
    for (auto &x : spc)
        al *= x;
    cout << "! ";
    for (size_t i = 1; i <= 5; i++)
    {
        cout << a[i] << ' ';
        al /= a[i];
    }
    cout << al << endl;
}

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}