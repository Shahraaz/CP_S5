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
    for (auto &x : a)
        cin >> x;
    for (auto &x : b)
        cin >> x;
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    // sort(all(b));
    for (size_t j = 0; j < m; j++)
    {
        ll g = a[0] + b[j];
        auto g1 = g;
        int i = 1;
        while (i < a.size())
        {
            g = __gcd(g, a[i] + b[j]);
            ++i;
            if (g == 1)
                break;
        }
        db(g, g1);
        cout << g << ' ';
        // assert(g == g1);
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