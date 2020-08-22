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
    int n, k;
    cin >> n >> k;
    vector<int> divisors;
    int ctr = 2;
    while (n > 1)
    {
        if (n % ctr == 0)
        {
            divisors.pb(ctr);
            n /= ctr;
        }
        else
            ctr++;
    }
    if (n > 1)
        divisors.pb(n);
    db(divisors);
    if (divisors.size() >= k)
    {
        for (int i = 0; i < k - 1; i++)
            cout << divisors[i] << ' ';
        int tmep = 1;
        for (int i = k - 1; i < divisors.size(); i++)
            tmep *= divisors[i];
        cout << tmep << '\n';
    }
    else
    {
        cout << -1 << '\n';
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
