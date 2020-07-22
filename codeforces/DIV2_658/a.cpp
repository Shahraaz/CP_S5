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
    void solveCase()
    {
        map<int, int> a, b;
        int n, m;
        cin >> n >> m;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            a[x]++;
        }
        for (size_t i = 0; i < m; i++)
        {
            int x;
            cin >> x;
            b[x]++;
        }
        for (auto &x : a)
        {
            if (b[x.f])
            {
                cout << "YES\n1 ";
                cout << x.f << '\n';
                return;
            }
        }
        cout << "NO\n";
    }
};

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
