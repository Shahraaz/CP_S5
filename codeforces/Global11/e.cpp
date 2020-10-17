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

vector<vector<ll>> opers;
set<ll> have;

// Refference : https://codeforces.com/blog/entry/68953
struct vectorSpace
{
    typedef long long base;
    int D, sz = 0;
    vector<base> basis; // basis[i] keeps the mask of the vector whose f value is i
    vectorSpace(int _D)
    {
        D = _D;
        basis.resize(D, 0);
    }
    void insert(base mask)
    {
        if (sz == D)
            return;
        vector<pair<ll, ll>> now;
        vector<pair<long long, long long>> ops;
        for (int i = D - 1; i >= 0; --i)
        {
            if (!((mask >> i) & 1))
                continue;
            if (!basis[i])
            {
                basis[i] = mask;
                ++sz;
                for (auto &x : now)
                    opers.pb({x.f, 1, x.s});
                return;
            }
            now.pb({mask, basis[i]});
            have.insert(mask ^ basis[i]);
            mask ^= basis[i];
        }
    }
    bool represent(base mask)
    {
        if (sz == D)
            return 1;
        for (int i = D - 1; i >= 0; --i)
        {
            if (!((mask >> i) & 1))
                continue;
            if (!basis[i])
                return 0;
            mask ^= basis[i];
        }
        return 1;
    }
};

void solveCase()
{
    const ll LIM = 5e18;
    const int BASIS_SIZE = __lg(LIM);
    ll x;
    cin >> x;
    db(x,LIM,BASIS_SIZE);

    vectorSpace space(BASIS_SIZE);
    have.insert(x);

    space.insert(x);

    while (!space.represent(1))
    {
        bool found = false;
        db(have);
        for (auto &x : have)
        {
            for (auto &y : have)
            {
                if (y < x || x > LIM - y)
                    continue;
                if (space.represent(x + y))
                    continue;
                opers.pb({x, 0, y});
                space.insert(x + y);
                have.insert(x + y);
                found = true;
                break;
            }
            if (found)
                break;
        }
        assert(found);
    }
    ll mask = 1;
    vector<ll> req;

    for (int i = space.D - 1; i >= 0; i--)
    {
        if (!(mask & (1LL << i)))
            continue;
        mask ^= space.basis[i];
        req.pb(space.basis[i]);
    }

    ll cur = req[0];

    for (size_t i = 1; i < req.size(); i++)
        opers.pb({cur, 1, req[i]});

    cout << opers.size() << '\n';
    for (auto &x : opers)
    {
        cout << x[0] << ' ';
        x[1] ? cout << "^ " : cout << "+ ";
        cout << x[2] << '\n';
    }
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
