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

const int OFFSET = 1001;
const int MAXT = 1e6 + 1;

void solveCase()
{
    int r, n;
    cin >> r >> n;
    ll res = 0;
    vector<vector<int>> vecc;
    vecc.pb({0, 1, 1});
    for (size_t i = 0; i < n; i++)
    {
        int t, x, y;
        cin >> t >> x >> y;
        vecc.pb({t, x, y});
    }
    n++;
    vector<ll> dp(n + 1);
    vector<ll> suffMax(n + 1);
    for (int i = n - 1; i >= 0; i--)
    {
        auto &res = dp[i];
        res = 1;
        for (size_t j = i + 1; j < n; j++)
        {
            if (vecc[j][0] - vecc[i][0] <= OFFSET)
            {
                if (abs(vecc[i][1] - vecc[j][1]) + abs(vecc[i][2] - vecc[j][2]) <= vecc[j][0] - vecc[i][0])
                    res = max(res, 1 + dp[j]);
            }
            else
            {
                res = max(res, 1 + suffMax[j]);
                break;
            }
        }
        suffMax[i] = max(res, suffMax[i + 1]);
        db(i, res);
    }
    cout << dp[0] - 1 << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
