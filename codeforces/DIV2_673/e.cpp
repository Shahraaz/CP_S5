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
    cin >> n;
    vector<int> vecc(n);
    for (auto &x : vecc)
        cin >> x;
    ll minInv = 0, X = 0;
    vector<vector<int>> order;
    order.pb(vecc);
    for (int i = 31 - 1; i >= 0; i--)
    {
        vector<vector<int>> next;
        ll invGivenZero = 0;
        ll invGivenOne = 0;
        db(i, order);
        for (auto &currVec : order)
        {
            int OneCnt = 0;
            int ZeroCnt = 0;
            vector<int> a, b;
            for (auto &x : currVec)
            {
                if (x & (1 << i))
                {
                    invGivenOne += ZeroCnt;
                    a.pb(x);
                    OneCnt++;
                }
                else
                {
                    invGivenZero += OneCnt;
                    b.pb(x);
                    ZeroCnt++;
                }
            }
            if (a.size() > 1)
                next.pb(a);
            if (b.size() > 1)
                next.pb(b);
        }
        db(invGivenOne, invGivenZero);
        if (invGivenZero <= invGivenOne)
            minInv += invGivenZero;
        else
        {
            minInv += invGivenOne;
            X |= (1 << i);
        }
        db(X, minInv);
        order.swap(next);
    }
    cout << minInv << ' ' << X << '\n';
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
