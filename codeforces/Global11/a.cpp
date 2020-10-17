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
    vector<ll> a(n);
    for (auto &x : a)
    {
        cin >> x;
    }
    ll sum = accumulate(all(a), 0LL);
    if (sum == 0)
        cout << "NO\n";
    else
    {
        cout << "YES\n";
        sort(all(a));
        // for (auto &x : a)
        // {
        //     cout << x << ' ';
        // }
        if (sum > 0)
        {
            for (auto &x : a)
            {
                if (x > 0)
                    cout << x << ' ';
            }
            for (auto &x : a)
            {
                if (x < 0)
                    cout << x << ' ';
            }
            for (auto &x : a)
            {
                if (x == 0)
                    cout << x << ' ';
            }
        }
        else
        {
            for (auto &x : a)
            {
                if (x < 0)
                    cout << x << ' ';
            }
            for (auto &x : a)
            {
                if (x > 0)
                    cout << x << ' ';
            }
            for (auto &x : a)
            {
                if (x == 0)
                    cout << x << ' ';
            }
        }
        cout << '\n';
    }
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
