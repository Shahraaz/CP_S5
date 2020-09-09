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
    sort(all(a));
    reverse(all(a));
    vector<int> b;
    b.pb(a[0]);
    int curr = a[0];
    a[0] = -1;
    for (size_t i = 1; i < n; i++)
    {
        int maxi = 0;
        int idx2 = -1;
        for (size_t j = 0; j < n; j++)
        {
            if (a[j] >= 0)
                if (__gcd(curr, a[j]) >= maxi)
                {
                    idx2 = j;
                    maxi = __gcd(curr, a[j]);
                }
        }
        curr = maxi;
        b.pb(a[idx2]);
        a[idx2] = -1;
    }
    for (auto &x : b)
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
