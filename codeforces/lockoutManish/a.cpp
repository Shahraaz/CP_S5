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
    ll l, r;
    cin >> l >> r;
    vector<ll> numList;
    for (ll i = l; i <= r; i++)
        numList.pb(i);
    for (size_t i = 0; i < numList.size(); i++)
    {
        for (size_t j = i + 1; j < numList.size(); j++)
        {
            if (__gcd(numList[i], numList[j]) != 1)
                continue;
            for (size_t k = j + 1; k < numList.size(); k++)
            {
                if (__gcd(numList[j], numList[k]) != 1)
                    continue;
                if (__gcd(numList[i], numList[k]) == 1)
                    continue;
                cout << numList[i] << ' ' << numList[j] << ' ' << numList[k] << '\n';
                return;
            }
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
