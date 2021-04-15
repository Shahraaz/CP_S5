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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a[i] = x;
    }
    for (size_t i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        auto idx = find(all(a), t) - a.begin();
        cout << idx + 1 << ' ';
        for (int i = idx; i > 0; i--)
            a[i] = a[i - 1];
        a[0] = t;
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