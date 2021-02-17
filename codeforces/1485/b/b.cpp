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
    int n, q, k;
    cin >> n >> q >> k;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<int> cnt(n);
    vector<ll> presum(n);
    for (size_t i = 0; i < n; i++)
    {
        int low = 1, high = k;
        if (i > 0)
            low = a[i - 1] + 1;
        if (i + 1 < n)
            high = a[i + 1] - 1;
        cnt[i] += high - low + 1 - 1;
        presum[i] += cnt[i];
        if (i > 0)
            presum[i] += presum[i - 1];
    }
    for (size_t i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        --l, --r;
        if (l == r)
        {
            cout << k - 1 << '\n';
            continue;
        }
        ll res = 0;
        if (l + 1 == r)
        {
            res += a[r] - 2;
            res += k - a[l] - 1;
        }
        else
        {
            res += a[l + 1] - 2;
            res += k - a[r - 1] - 1;
            res += presum[r - 1] - presum[l];
        }
        cout << res << '\n';
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