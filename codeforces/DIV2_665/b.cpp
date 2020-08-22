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
    vector<int> a(3);
    vector<int> b(3);
    for (auto &x : a)
    {
        cin >> x;
    }
    for (auto &x : b)
    {
        cin >> x;
    }
    int res = 0;
    int mini = min(a[2], b[1]);
    res += 2 * mini;
    a[2] -= mini;
    b[1] -= mini;
    mini = min(a[2], b[2]);
    a[2] -= mini;
    b[2] -= mini;
    mini = min(a[0], b[2]);
    a[0] -= mini;
    b[2] -= mini;
    mini = min(a[1], b[2]);
    a[1] -= mini;
    b[2] -= mini;
    res -= 2 * mini;
    cout << res << '\n';
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
