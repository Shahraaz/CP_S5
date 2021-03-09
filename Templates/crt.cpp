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
        db(r0, m0, r[i], m[i], rem);
        if (rem == LLONG_MAX)
            return {LLONG_MAX, LLONG_MAX};
        r0 = rem;
        m0 = m0 / __gcd(m0, m[i]) * m[i];
    }
    return {r0, m0};
}

void solveCase()
{
    ll X, Y, P, Q;
    cin >> X >> Y >> P >> Q;

    ll best = LLONG_MAX;
    for (ll t1 = X; t1 < X + Y; t1++)
        for (ll t2 = P; t2 < P + Q; t2++)
        {
            auto t = crt({t1, t2}, {2 * X + 2 * Y, P + Q});
            // auto t = crt(t1, 2 * X + 2 * Y, t2, P + Q);
            // best = min(best,t);
            db(t1, t2, t);
            if (t.first == LLONG_MAX)
                continue;
            if (t.first == 0)
                best = min(best, t.second);
            else
                best = min(best, t.first);
        }
    if (best == LLONG_MAX)
        cout << "infinity\n";
    else
        cout << best << '\n';
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