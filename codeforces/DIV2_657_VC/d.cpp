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
    ll n, h, m, k;
    cin >> n >> h >> m >> k;
    vector<pair<ll, ll>> v(2 * n);
    const ll period = m >> 1;
    for (size_t i = 0; i < n; i++)
    {
        ll a, b;
        cin >> a >> b;
        v[2 * i] = {b % period, (ll)i};
        v[2 * i + 1] = {b % period + period, (ll)i};
    }
    sort(all(v));
    vector<ll> ans = {LLONG_MAX, LLONG_MAX};
    ll j = 0;
    for (int i = 0; i < 2 * n; i++)
    {
        ll t = v[i].f;
        while (v[j].f <= t - k)
            j++;
        if (i >= n)
            ans = min(ans, {i - j, t % period});
    }
    cout << ans[0] << ' ' << ans[1] << '\n';
    for (size_t i = 0; i < 2 * n; i++)
    {
        ll t = v[i].f;
        ll r = ans[1] + period;
        ll l = r - k;
        if (l < t && t < r)
            cout << v[i].s + 1 << ' ';
    }
    cout << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
