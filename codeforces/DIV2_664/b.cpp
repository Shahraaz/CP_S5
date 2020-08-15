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

const int NAX = 100 + 5, MOD = 1000000007;

bool vis[NAX][NAX];
bool row[NAX];
struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        int sx, sy;
        cin >> sx >> sy;
        sx--, sy--;
        for (size_t i = 0; i < n; i++)
        {
            int idx = 0;
            if (i == 0)
                idx = sx;
            while (row[idx])
                idx++;
            cout << idx + 1 << ' ' << sy + 1 << '\n';
            vis[idx][sy] = 1;
            for (size_t j = 0; j < m; j++)
                if (!vis[idx][j])
                {
                    vis[idx][j] = 1;
                    sy = j;
                    cout << idx + 1 << ' ' << sy + 1 << '\n';
                }
            row[idx] = 1;
        }
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
