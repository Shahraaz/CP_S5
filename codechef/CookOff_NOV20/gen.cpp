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
    const int N = 5;
    int t = N * (N + 1) / 2;
    cout << t << '\n';
    srand(time(NULL));
    int n;
    for (size_t i = 1; i <= N; i++)
    {
        for (int j = 1; j <= i; j++)
            cout << i << ' ' << j << '\n';
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
        solveCase();
    return 0;
}