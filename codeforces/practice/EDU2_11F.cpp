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

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<ll> a(n + 1);
        for (size_t i = 1; i <= n; i++)
            cin >> a[i];
        vector<ll> S(n + 1), X(n + 1);
        for (size_t i = 1; i <= n; i++)
        {
            S[i] = a[i] + S[i - 1];
            X[i] = i * a[i] + X[i - 1];
        }
        ll res = 0;
        lineContainer L;
        for (int i = n; i >= 1; i--)
        {
            L.add(-S[i], X[i]);
            ll temp = L.query(i - 1) - (X[i - 1] - (i - 1) * (S[i - 1]));
            res = max(res, temp);
            db(i, temp);
            temp = LLONG_MIN;
            for (int j = i; j <= n; j++)
                temp = max(temp, X[j] - X[i - 1] - (i - 1) * (S[j] - S[i - 1]));
            db(i, temp);
        }

        cout << res << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
