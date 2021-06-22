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
const int NAX = 2e5 + 5, MOD = 1000000000;

void solveCase()
{
    int n = 100000;
    // cin >> n;
    cout << n << '\n';
    vector<int> a(n);
    for (auto &x : a)
    {
        x = rand() % MOD;
        // cin >> x;
        cout << x << ' ';
    }
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 10;
    cout << t << '\n';
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}