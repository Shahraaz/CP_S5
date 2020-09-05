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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    int one, two;
    one = two = 0;
    for (auto &x : a)
    {
        cin >> x;
        one ^= x;
    }
    for (auto &x : b)
    {
        cin >> x;
        two ^= x;
    }
    if (one == two)
    {
        cout << "YES\n";
        one = a[0];
        for (size_t i = 1; i < m; i++)
        {
            one ^= b[i];
        }
        cout << one << ' ';
        for (size_t i = 1; i < m; i++)
            cout << b[i] << ' ';
        cout << '\n';
        for (size_t i = 1; i < n; i++)
        {
            cout << a[i] << ' ';
            for (size_t j = 1; j < m; j++)
            {
                cout << 0 << ' ';
            }
            cout << '\n';
        }
    }
    else
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
