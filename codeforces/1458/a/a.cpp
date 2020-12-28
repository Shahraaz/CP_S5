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
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (size_t i = 0; i < m; i++)
    {
        cin >> b[i];
    }

    if (n == 1)
    {
        for (size_t i = 0; i < m; i++)
        {
            cout << a[0] + b[i] << ' ';
        }
        cout << '\n';
        return;
    }

    ll g = 0;
    sort(all(a));
    reverse(all(a));
    for (size_t i = 0; i + 1 < n; i++)
        g = __gcd(g, a[i] - a[i + 1]);
    for (size_t i = 0; i < m; i++)
    {
        cout << __gcd(g, a[n - 1] + b[i]) << ' ';
    }
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    srand(time(NULL));
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}