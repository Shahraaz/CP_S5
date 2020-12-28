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
    vector<int> c(3), a(5);
    for (auto &x : c)
        cin >> x;
    for (auto &x : a)
        cin >> x;
    c[0] -= a[0];
    c[1] -= a[1];
    c[2] -= a[2];
    a[0] = a[1] = a[2] = 0;

    for (auto &x : c)
    {
        if (x < 0)
        {
            cout << "NO\n";
            return;
        }
    }
    int temp = min(a[3], c[0]);
    c[0] -= temp;
    a[3] -= temp;

    for (auto &x : c)
    {
        if (x < 0)
        {
            cout << "NO\n";
            return;
        }
    }
    temp = min(a[4], c[1]);
    c[1] -= temp;
    a[4] -= temp;

    c[2] -= a[3] + a[4];
    for (auto &x : c)
    {
        if (x < 0)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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