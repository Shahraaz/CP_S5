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

// #define int ll

vector<int> _factors(int x)
{
    vector<int> ret;
    for (ll i = 1; i * i <= x; i++)
        if (x % i == 0)
        {
            ret.pb(i);
            ret.pb(x / i);
        }
    sort(all(ret));
    ret.resize(unique(all(ret)) - ret.begin());
    return ret;
}

void solveCase()
{
    int n;
    cin >> n;
    vector<pair<int, int>> vecc(n);
    for (auto &x : vecc)
        cin >> x.f >> x.s;
    vector<int> space;
    auto temp = _factors(vecc[0].f);
    for (auto &x : temp)
        if (x > 1)
            space.pb(x);
    temp = _factors(vecc[0].s);
    for (auto &x : temp)
        if (x > 1)
            space.pb(x);
    sort(all(space));
    space.resize(unique(all(space)) - space.begin());
    for (auto &x : space)
    {
        bool ok = true;
        for (auto &y : vecc)
            if (y.f % x && y.s % x)
            {
                ok = false;
                break;
            }
        if (ok && x > 1)
        {
            cout << x << '\n';
            return;
        }
    }
    cout << -1 << '\n';
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
