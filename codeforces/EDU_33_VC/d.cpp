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
    int n, d;
    cin >> n >> d;
    vector<ll> a(n);
    ll sum = 0;
    ll res = 0;
    ll gunjaish = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        db(i, a[i], sum, gunjaish);
        if (a[i] == 0)
        {
            if (sum < 0)
            {
                if (abs(sum) <= gunjaish)
                {
                    gunjaish -= abs(sum);
                    sum = 0;
                }
                else
                {
                    res++;
                    sum = 0;
                    gunjaish = MOD;
                }
            }
        }
        else if (a[i] > 0)
        {
            sum += a[i];
            if (sum > d)
            {
                std::cout << -1 << '\n';
                return;
            }
            gunjaish = min(gunjaish, d - sum);
        }
        else
        {
            sum += a[i];
            gunjaish = min(gunjaish, d - sum);
        }
    }
    cout << res << '\n';
}

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
