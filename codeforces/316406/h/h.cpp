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

#include <bits/stdc++.h>
using namespace std;
struct Line
{
    mutable long long k, m;
    mutable function<const Line *()> succ;
    bool operator<(const Line &o) const
    {
        return k > o.k;
    }
    bool operator<(const long long &_p) const
    {
        const Line *s = succ();
        if (s == nullptr)
            return false;
        return (m + k * _p) < (s->m + s->k * _p);
    }
};

ostream &operator<<(ostream &out, const Line &p)
{
    out << "slope " << p.k << " constant " << p.m << ' ';
    return out;
}
//Max Query

struct lineContainer : multiset<Line, less<>>
{
    bool bad(iterator y)
    {
        auto z = next(y);
        if (y == begin())
        {
            if (z == end())
                return false;
            return y->k == z->k && y->m <= z->m;
        }
        auto x = prev(y);
        if (z == end())
            return y->k == x->k && y->m <= x->m;
        return 1.0L * (x->m - y->m) * (y->k - z->k) >= 1.0L * (y->k - x->k) * (z->m - y->m);
    }
    void add(long long k, long long m)
    {
        auto y = insert({k, m});
        y->succ = [=] { return next(y) == end() ? nullptr : &*(next(y)); };
        if (bad(y))
        {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y)))
            erase(next(y));
        while (y != begin() && bad(prev(y)))
            erase(prev(y));
    }
    long long query(long long x)
    {
        auto l = lower_bound(x);
        db(x, *l, l->k * x + l->m);
        return l->k * x + l->m;
    }
};

void solveCase()
{
    int n;
    cin >> n;
    vector<pair<pair<ll, ll>, ll>> xya(n);
    for (auto &x : xya)
        cin >> x.first.first >> x.first.second >> x.second;
    sort(all(xya));
    ll dp_res = 0, dp_now = 0;
    lineContainer l;
    l.add(0, 0);
    for (size_t i = 0; i < n; i++)
    {
        dp_now = xya[i].first.first * xya[i].first.second - xya[i].second + l.query(xya[i].first.second);
//         db(i, xya[i], dp_now);
// #ifdef LOCAL
//         for (auto &x : l)
//             cout << x.k << ' ' << x.m << ' ' << x.p << ", ";
//         cout << '\n';
// #endif
        l.add(-xya[i].first.first, dp_now);
        dp_res = max(dp_res, dp_now);
    }

    cout << dp_res << '\n';
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