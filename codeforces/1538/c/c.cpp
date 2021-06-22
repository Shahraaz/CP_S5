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
    int n, l, r;
    cin >> n >> l >> r;
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    sort(all(a));
    db(l, r, a);
    ll res = 0;
    for (size_t i = 0; i + 1 < n; i++)
    {
        if (a[i] + a[n - 1] < l)
            continue;
        if (a[i] + a[i + 1] > r)
            continue;

        int low = i + 1, high = n - 1, ans = n - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (l <= a[i] + a[mid])
                ans = mid, high = mid - 1;
            else
                low = mid + 1;
        }

        int ans1 = ans;
        low = i + 1, high = n - 1, ans = i + 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (a[i] + a[mid] <= r)
                ans = mid, low = mid + 1;
            else
                high = mid - 1;
        }
        db(i, ans, ans1);
        res += ans - ans1 + 1;
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
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}