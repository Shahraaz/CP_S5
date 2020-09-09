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

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<int> res;
    for (size_t i = 0; i < n; i++)
    {
        if (i + 1 == n)
        {
            if (a[i] == 1)
                ;
            else
                res.pb(0);
        }
        else if (a[i] == a[i + 1])
        {
            res.pb(a[i]);
            res.pb(a[i + 1]);
            ++i;
        }
        else if (a[i] == 0)
        {
            if (i + 2 == n)
            {
                res.pb(0);
                break;
            }
            else
            {
                res.pb(a[i + 2]);
                res.pb(a[i + 2]);
                ++i;
                ++i;
            }
        }
        else
        {
            if (i + 2 == n)
            {
                res.pb(0);
                break;
            }
            else
            {
                res.pb(a[i + 2]);
                res.pb(a[i + 2]);
                ++i;
                ++i;
            }
        }
    }
    cout << res.size() << '\n';
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
