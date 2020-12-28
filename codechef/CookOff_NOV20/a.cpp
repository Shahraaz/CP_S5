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
    int n, m, k;
    cin >> n >> m >> k;
    int count = 0;
    for (size_t i = 0; i < n; i++)
    {
        ll sum = 0;
        for (size_t j = 0; j < k; j++)
        {
            int x;
            cin >> x;
            sum += x;
        }
        int Q;
        cin >> Q;
        if (sum >= m && Q <= 10)
        {
            count++;
        }
    }

    cout << count << '\n';
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