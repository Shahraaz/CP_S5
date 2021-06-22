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

#define int ll

void solveCase()
{
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<int> prefor(n);
    vector<int> suffor(n);
    for (size_t i = 0; i < n; i++)
    {
        if (i > 0)
            prefor[i] = prefor[i - 1];
        prefor[i] |= a[i];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (i + 1 < n)
            suffor[i] = suffor[i + 1];
        suffor[i] |= a[i];
    }
    db(n,k,x);
    db(a);
    db(prefor);
    db(suffor);
    int res = 0;
    for (size_t i = 0; i < n; i++)
    {
        int now = i > 0 ? prefor[i - 1] : 0;
        now |= i + 1 < n ? suffor[i + 1] : 0;
        int temp = a[i];
        for (size_t i = 0; i < k; i++)
            temp *= x;
        now |= temp;
        res = max(res, now);
    }
    cout << res << '\n';
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