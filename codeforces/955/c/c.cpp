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
const int NAX = 1e6 + 5, MOD = 1000000007;

vector<ll> indices;

ll root(ll x)
{
    ll low = 1, high = sqrtl(x) + 10, ans = 1;
    while (low <= high)
    {
        auto mid = (low + high) / 2;
        if (mid * mid <= x)
            ans = mid, low = mid + 1;
        else
            high = mid - 1;
    }
    // db(x, ans);
    return ans;
}

void pre()
{
    for (__int128_t i = 2; i < NAX; i++)
    {
        __int128_t j = i * i * i;
        while (j <= LLONG_MAX)
        {
            indices.pb(j);
            j *= i;
        }
    }
    sort(all(indices));
    indices.resize(unique(all(indices)) - indices.begin());

    db(indices.size());
    auto back = indices;
    indices.clear();
    for (auto &x : back)
    {
        auto r = root(x);
        if (r * r != x)
            indices.pb(x);
    }
    db(indices.size());
}

ll count(ll x)
{
    if (x <= 1)
        return x;
    ll ret = root(x);
    ret += (upper_bound(all(indices), x) - indices.begin());
    db(x, ret);
    return ret;
}

void solveCase()
{
    ll l, r;
    cin >> l >> r;
    cout << count(r) - count(l - 1) << '\n';
}

int32_t main()
{
    pre();
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