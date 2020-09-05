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
    int n, w;
    cin >> n >> w;
    vector<int> a(n);
    vector<int> pour(n);
    for (auto &x : a)
        cin >> x;
    vector<pair<int, int>> myVec;
    for (size_t i = 0; i < n; i++)
        myVec.pb({a[i], i});
    sort(all(myVec));
    for (size_t i = 0; i < n; i++)
    {
        int idx = myVec[i].s;
        int cap = a[idx];
        int minVal = ceil(cap / 2.0);
        db(i, idx, cap, minVal, w);
        if (minVal > w)
        {
            cout << -1 << '\n';
            return;
        }
        w -= minVal;
        pour[idx] = minVal;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        int idx = myVec[i].s;
        int remCap = a[idx] - pour[idx];
        remCap = min(remCap, w);
        pour[idx] += remCap;
        w -= remCap;
    }
    if (w != 0)
    {
        cout << -1 << '\n';
        return;
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << pour[i] << ' ';
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
