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
    int n;
    ll T;
    cin >> n >> T;
    vector<int> a(n);
    vector<int> res(n);
    map<int, vector<int>> mp;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        mp[a[i]].pb(i);
    }
    map<int, int> clr;
    for (auto &x : mp)
    {
        int ctr = 0;
        if (x.f * 2 == T)
        {
            for (auto &y : x.second)
            {
                res[y] = ctr;
                ctr = 1 - ctr;
            }
            continue;
        }
        if (clr.find(T - x.f) != clr.end())
            ctr = 1 - clr[T - x.f];
        clr[x.f] = ctr;
        for (auto &y : x.second)
            res[y] = ctr;
    }
    for (auto &x : res)
    {
        cout << x << ' ';
    }

    cout << '\n';
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
