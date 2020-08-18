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
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (auto &x : v)
    {
        cin >> x;
    }
    --k;
    auto maxi = *max_element(all(v));
    for (auto &x : v)
        x = maxi - x;
    db(v);
    map<vector<ll>, int> mp;
    int ctr = 1;
    while (true)
    {
        if (k == 0)
            break;
        k--;
        auto maxi = *max_element(all(v));
        for (auto &x : v)
            x = maxi - x;
        if (mp.count(v))
        {
            ctr = ctr - mp[v];
            k %= ctr;
            mp.clear();
        }
        mp[v] = ctr;
        ctr++;
    }
    for (auto &x : v)
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
