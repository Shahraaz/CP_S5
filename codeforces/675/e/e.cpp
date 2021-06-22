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
    vector<int> a(n + 1);
    for (size_t i = 1; i < n; i++)
        cin >> a[i];
    a[n] = n;
    deque<pair<int, int>> dQ;
    vector<ll> dp(n + 1);
    dQ.push_back({n, n});
    for (int i = n - 1; i >= 1; i--)
    {
        int rptr = a[i];
        db(i, rptr);
        while (dQ.size() && dQ.front().second <= rptr)
            dQ.pop_front();
        dQ.push_front({i, rptr});
        db(i, dQ);
        int low = 0, high = dQ.size() - 1, ans = 0;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (dQ[mid].first <= rptr)
                ans = mid, low = mid + 1;
            else
                high = mid - 1;
        }
        db(ans, dQ[ans]);
        if (ans == 0)
            dp[i] = n - i;
        else
        {
            int zptr = dQ[ans].first;
            db(zptr, dp[zptr], a[i] - i, n - a[i] + dp[zptr] - (a[i] - zptr));
            dp[i] += a[i] - i;
            dp[i] += n - a[i] + dp[zptr] - (a[i] - zptr);
        }
        db(i, dp[i], '\n');
    }
    cout << accumulate(all(dp), 0LL) << '\n';
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