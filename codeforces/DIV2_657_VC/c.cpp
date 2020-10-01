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
    ll n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> ab(m);
    for (auto &x : ab)
        cin >> x.f >> x.s;
    sort(all(ab));
    vector<ll> pref(m);
    for (size_t i = 0; i < m; i++)
    {
        pref[i] += ab[i].f;
        if (i > 0)
            pref[i] += pref[i - 1];
    }
    ll res = 0;
    db(n, m);
    db(ab);
    db(pref);
    for (size_t i = 0; i < m; i++)
    {
        auto idx = lower_bound(all(ab), make_pair(ab[i].s, 0LL)) - ab.begin();
        db(i, idx, make_pair(ab[i].s, 0LL));
        idx = max(0LL + idx, m - n);
        ll temp = pref[m - 1];
        if (idx > 0)
            temp -= pref[idx - 1];
        auto rem = max(0LL, n - m + idx);
        if (idx > i && rem)
            temp += ab[i].f, rem--;
        if (rem > 0)
            temp += rem * ab[i].s;
        db(i, temp);
        res = max(res, temp);
    }
    std::cout << res << '\n';
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
