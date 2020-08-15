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

const int NAX = 16777216 + 5, MOD = 1000000007;

bool vis[NAX];
ll cost[NAX];
struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n, x, y;
        cin >> n >> x >> y;
        set<pair<ll, int>> Q;
        // for (size_t i = 0; i < NAX; i++)
        //     cost[i] = LLONG_MAX;
        cost[1] = x;
        for (size_t i = 2; i <= n; i++)
        {
            cost[i] = cost[i - 1] + x;
            if (i & 1)
            {
                cost[i] = min(cost[i], x + y + cost[(i + 1) / 2]);
            }
            else
            {
                cost[i] = min(cost[i], cost[i / 2] + y);
            }
        }
        cout << cost[n] << '\n';
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
