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
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a)
            cin >> x;
        vector<int> b(n);
        iota(all(b), 0);
        sort(all(b), [&](int x, int y) {
            if (a[x] != a[y])
                return a[x] < a[y];
            return x < y;
        });
        db(a, b);
        vector<pair<int, int>> ret;
        for (size_t it = 0; it < n; it++)
            for (int i = 0; i < n - 1; i++)
            {
                if (b[i] > b[i + 1])
                {
                    ret.pb({b[i + 1], b[i]});
                    swap(b[i], b[i + 1]);
                }
            }
        cout << ret.size() << '\n';
        for (auto &x : ret)
            cout << x.f + 1 << ' ' << x.s + 1 << '\n';
    }
};

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
