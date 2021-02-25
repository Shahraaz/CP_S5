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
    srand(time(NULL));
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    auto check = [&](int x) -> bool {
        auto b = a;
        vector<int> pref(n);
        for (size_t i = 0; i < n; i++)
        {
            if (b[i] >= x)
                b[i] = 1;
            else
                b[i] = -1;
            pref[i] = b[i];
            if (i > 0)
                pref[i] += pref[i - 1];
        }
        int suffmax = -MOD;
        db(x, b);
        db(pref);
        for (int i = n - k; i >= 0; i--)
        {
            int rptr = i + k - 1;
            suffmax = max(suffmax, pref[rptr]);
            ll prev = 0;
            if (i > 0)
                prev = pref[i - 1];
            db(i, prev, suffmax);
            ll curr = suffmax - prev;
            if (curr > 0)
                return true;
        }
        return false;
    };
    int low = 1, high = n, ans = 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (check(mid))
        {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
    cout << ans << '\n';
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