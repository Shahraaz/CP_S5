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
