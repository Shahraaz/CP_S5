#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
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
    int n, k;
    cin >> n >> k;
    vector<long long> a(n), c(n);
    for (size_t i = 0; i < n; i++)
        cin >> a[i];
    for (size_t i = 0; i < n; i++)
        cin >> c[i];
    vector<long long> mincost(n, -1);
    mincost[0] = 0;
    for (size_t i = 0; i < k; i++)
    {
        vector<long long> mincostnext(n, -1);
        lineContainer l;
        for (size_t j = 0; j < n; j++)
        {
            // db(j, l);
            if (l.size())
                mincostnext[j] = -l.query(a[j]) + a[j] * a[j];
            if (mincost[j] == -1)
                continue;
            long long cx = mincost[j] + a[j] * a[j] + c[j];
            long long m = -2 * a[j];
            db(m, cx);
            l.add(-m, -cx);
        }
        db(i);
        db(mincost);
        db(mincostnext);
        mincostnext.swap(mincost);
    }
    cout << mincost[n - 1] << '\n';
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