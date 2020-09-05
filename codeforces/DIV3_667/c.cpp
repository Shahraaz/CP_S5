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
    int n, x, y;
    cin >> n >> x >> y;
    vector<ll> vecc = {LLONG_MAX, 0, 1};
    for (ll i = 0; i < n; i++)
    {
        for (ll j = i + 1; j < n; j++)
        {
            int diff = j - i;
            if ((y - x) % diff == 0)
            {
                int k = (y - x) / diff;
                int a0 = x - i * k;
                ll an = a0 + (n - 1) * k;
                if (a0 > 0)
                    vecc = min(vecc, {an, i, j});
            }
        }
    }
    int i = vecc[1];
    int j = vecc[2];
    int diff = j - i;
    int k = (y - x) / diff;
    int a0 = x - i * k;
    for (size_t i = 0; i < n; i++)
    {
        cout << a0 << ' ';
        a0 += k;
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
