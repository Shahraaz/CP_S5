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
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    auto pref = a;
    for (size_t i = 1; i < n; i++)
        pref[i] += pref[i - 1];
    set<ll> mySet;
    for (int i = 0; i < n; i++)
    {
        if (pref[i] == (pref.back() - pref[i]))
        {
            cout << "YES\n";
            return;
        }
        mySet.insert(a[i]);
        ll mya = pref[i];
        ll sum = 2 * mya - pref.back();
        if (sum >= 0 && sum % 2 == 0)
        {
            if (mySet.count(sum / 2))
            {
                cout << "YES\n";
                return;
            }
        }
    }
    mySet.clear();

    reverse(all(a));
    pref = a;
    for (size_t i = 1; i < n; i++)
        pref[i] += pref[i - 1];
    // set<ll> mySet;
    for (int i = 0; i < n; i++)
    {
        if (pref[i] == (pref.back() - pref[i]))
        {
            cout << "YES\n";
            return;
        }
        mySet.insert(a[i]);
        ll mya = pref[i];
        ll sum = 2 * mya - pref.back();
        if (sum >= 0 && sum % 2 == 0)
        {
            if (mySet.count(sum / 2))
            {
                cout << "YES\n";
                return;
            }
        }
    }

    cout << "NO\n";
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
