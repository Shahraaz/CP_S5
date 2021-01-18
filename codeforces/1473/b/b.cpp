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
    string one, two;
    cin >> one >> two;
    int len1 = one.size();
    int len2 = two.size();
    auto lcm = len1 * len2 / __gcd(len1, len2);
    auto a = one, b = two;
    while (a.size() < lcm)
        a += one;
    while (b.size() < lcm)
        b += two;
    if (a != b)
        cout << -1 << '\n';
    else
        cout << a << '\n';
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
        solveCase();
    return 0;
}