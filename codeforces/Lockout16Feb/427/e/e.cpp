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
    int n = 1e6, m = 1;
    cin >> n >> m;
    vector<ll> poses(n);
    for (size_t i = 0; i < n; i++)
    {
        poses[i] = (rand() % 2 ? -1 : 1) * rand() % MOD;
        cin >> poses[i];
    }
    if (!is_sorted(all(poses)))
        sort(all(poses));
    ll low = poses.front(), high = poses.back();
    pair<ll, int> ans = {LLONG_MAX, -1};
    auto compute = [&](ll idx) -> ll {
        int pos = lower_bound(all(poses), idx) - poses.begin();
        ll ret = 0;
        for (size_t i = 0; i < pos; i += m)
            ret += 2 * abs(poses[i] - idx);
        for (int i = n - 1; i >= pos; i -= m)
            ret += 2 * abs(poses[i] - idx);
        return ret;
    };
    while ((high - low) > 20)
    {
        ll m1 = (low + low + high) / 3;
        ll m2 = (low + high + high) / 3;
        ll rm1 = compute(m1);
        ll rm2 = compute(m2);
        db(low, high);
        db(m1, rm1, m2, rm2);
        if (rm1 < rm2)
            high = m2;
        else
            low = m1;
    }
    while (low <= high)
    {
        auto res = compute(low);
        db(low, res);
        ans = min(ans, {res, low});
        ++low;
        // cout << res << '\n';
    }
    db(ans);
    cout << ans.first << '\n';
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