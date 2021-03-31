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

ll euclid(ll a, ll b, ll &x, ll &y)
{
    if (b)
    {
        ll d = euclid(b, a % b, y, x);
        return y -= a / b * x, d;
    }
    return x = 1, y = 0, a;
}

ll crt(ll a, ll m, ll b, ll n)
{
    if (n > m)
        swap(a, b), swap(m, n);
    if (n == 1)
        return a;
    ll x, y, g = euclid(m, n, x, y);
    if ((a - b) % g != 0)
        return LLONG_MAX;
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m * n / g : x;
}

pair<ll, ll> crt(const vector<ll> &r, const vector<ll> &m)
{
    ll r0 = 0, m0 = 1;
    assert(r.size() == m.size());
    for (size_t i = 0; i < r.size(); i++)
    {
        auto rem = crt(r0, m0, r[i], m[i]);
        if (rem == LLONG_MAX)
            return {LLONG_MAX, LLONG_MAX};
        r0 = rem;
        m0 = m0 / __gcd(m0, m[i]) * m[i];
    }
    return {r0, m0};
}

void solveCase()
{
    int n, m;
    cin >> n >> m;
    ll k;
    cin >> k;
    const int LIM = 2 * (n + m);
    vector<int> rev_a(LIM, -1);
    vector<int> rev_b(LIM, -1);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        --x;
        rev_a[x] = i;
    }
    for (size_t i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        --x;
        rev_b[x] = i;
    }
    vector<ll> good;
    ll md = -1;
    for (size_t i = 0; i < LIM; i++)
    {
        if (rev_a[i] == -1 || rev_b[i] == -1)
            continue;
        auto res = crt({rev_a[i], rev_b[i]}, {n, m});
        db(rev_a[i], rev_b[i], n, m, res);
        if (res.first == LLONG_MAX)
            continue;
        // assert(res.first != LLONG_MAX);
        assert(md == -1 || md == res.second);
        good.pb(res.first);
        md = res.second;
    }
    if (md == -1)
    {
        cout << k << '\n';
        return;
    }
    sort(all(good));
    int sz = good.size();
    good.erase(unique(all(good)), good.end());
    assert(sz == good.size());
    ll low = 0, high = 4e18;
    ll ans = high;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        ll cc = mid - (mid / md) * (ll)good.size();
        ll r = mid % md;
        for (auto &x : good)
            if (x < r)
                cc--;
        if (cc >= k)
            ans = mid, high = mid - 1;
        else
            low = mid + 1;
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