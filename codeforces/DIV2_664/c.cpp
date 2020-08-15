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

bool vis[201][1024];
struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(m);
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (size_t i = 0; i < m; i++)
        {
            cin >> b[i];
        }

        int res = INT_MAX;
        function<void(int, int)> fun = [&](int idx, int prev) -> void {
            if (idx == n)
            {
                res = min(res, prev);
                return;
            }
            if (vis[idx][prev])
                return;
            vis[idx][prev] = true;
            for (size_t j = 0; j < m; j++)
                fun(idx + 1, prev | (a[idx] & b[j]));
        };
        fun(0, 0);
        cout << res << '\n';
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
