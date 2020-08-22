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
    vector<int> prev_zero(n, -MOD);
    vector<int> next_zero(n, MOD);
    for (auto &x : a)
        cin >> x;
    for (size_t i = 0; i < n; i++)
        if (a[i] == 0)
            prev_zero[i] = i;
        else if (i > 0)
            prev_zero[i] = prev_zero[i - 1];
    for (int i = n - 1; i >= 0; i--)
        if (a[i] == 0)
            next_zero[i] = i;
        else if (i < (n - 1))
            next_zero[i] = next_zero[i + 1];
    // reverse(all(next_zero));
    for (int i = 0; i < n; i++)
    {
        int t = min(i - prev_zero[i], next_zero[i] - i);
        cout << t << ' ';
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
