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
    int n, x;
    cin >> n >> x;
    ll mini = 0, maxi = 0;
    for (size_t i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        mini += temp;
        maxi += (temp + x - 1) / x;
    }
    mini = (mini + x - 1) / x;
    cout << mini << ' ' << maxi << '\n';
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