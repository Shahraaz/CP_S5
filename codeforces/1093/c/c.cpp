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
    int n;
    cin >> n;
    vector<ll> b(n + 1), a(n + 1);
    for (size_t i = 1; 2 * i <= n; i++)
        cin >> b[i];
    a[0] = 0;
    a[n + 1] = LLONG_MAX;
    for (int i = 1; 2 * i <= n; i++)
    {
        int rptr = n - i + 1;
        a[i] = a[i - 1];
        b[i] -= a[i];
        if (a[rptr + 1] >= b[i])
        {
            a[rptr] = b[i];
        }
        else
        {
            b[i] += a[i];
            a[rptr] = a[rptr + 1];
            a[i] = b[i] - a[rptr];
        }
    }
    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
    cout << '\n';
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