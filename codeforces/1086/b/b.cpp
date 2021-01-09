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
    using ld = long double;
    int n;
    ld s;
    cin >> n >> s;
    vector<int> degree(n);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        degree[u - 1]++;
        degree[v - 1]++;
    }
    int leafcnt = 0;
    for (size_t i = 0; i < n; i++)
        if (degree[i] == 1)
            leafcnt++;
    cout << fixed << setprecision(10) << (s / leafcnt) * 2 << '\n';
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