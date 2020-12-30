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
    int n, m;
    cin >> n;
    deque<int> red(n);
    for (auto &x : red)
        cin >> x;
    cin >> m;
    deque<int> blue(m);
    for (auto &x : blue)
        cin >> x;
    int res = -MOD, a, b;
    a = b = -MOD;
    for (size_t i = 0; i < n; i++)
    {
        if (i > 0)
            red[i] += red[i - 1];
        a = max(a, red[i]);
    }
    for (size_t i = 0; i < m; i++)
    {
        if (i > 0)
            blue[i] += blue[i - 1];
        b = max(b, blue[i]);
    }
    cout << max({0, a, b, a + b}) << '\n';
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