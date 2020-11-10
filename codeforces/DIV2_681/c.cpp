// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &x : a)
        cin >> x.f;
    for (auto &x : a)
        cin >> x.s;
    auto check = [&](ll lim) -> bool {
        int i = 0;
        ll tt = 0;
        while (i < n)
        {
            if (a[i].f <= lim)
            {
                ++i;
                continue;
            }
            tt += a[i].s;
            ++i;
        }
        return tt <= lim;
    };
    ll low = 0, high = 1e15;
    ll ans = high;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        db(low, mid, high) if (check(mid))
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else low = mid + 1;
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
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
