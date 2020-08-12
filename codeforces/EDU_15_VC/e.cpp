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

const int NAX = 2e5 + 5, MOD = 1000000007, L = 35;

ll n, k;
vector<pair<int, int>> adj[NAX];
int vis[NAX];
int par[L][NAX];
ll sum[L][NAX];
int mini[L][NAX];

// void dfs(int node, int par)
// {
//     if (vis[node])
//         return;
//     vis[node] = true;
//     for (auto &x : adj[node])
//         if (x.f != par)
//         {
//             ::par[0][node] = x.f;
//             sum[0][node] = x.s;
//             mini[0][node] = x.s;
//             dfs(x.f, node);
//         }
// }

struct Solution
{
    Solution() {}
    void solveCase()
    {
        db(log2(1e10));
        cin >> n >> k;
        vector<int> f(n);
        vector<int> ind(n);
        for (auto &x : f)
            cin >> x;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            par[0][i] = f[i];
            sum[0][i] = x;
            mini[0][i] = x;
            // adj[i].pb({f[i], x});
            // if (i != x)
            //     ind[x]++;
            // par[0][i] = -1;
        }
        // for (size_t i = 0; i < n; i++)
        //     dfs(i, -1);
        for (size_t i = 0; i < n; i++)
            db(i, par[0][i], sum[0][i], mini[0][i]);
        for (size_t i = 1; i < L; i++)
            for (size_t j = 0; j < n; j++)
            {
                par[i][j] = par[i - 1][par[i - 1][j]];
                mini[i][j] = min(mini[i - 1][j], mini[i - 1][par[i - 1][j]]);
                sum[i][j] = sum[i - 1][j] + sum[i - 1][par[i - 1][j]];
            }
        for (size_t i = 0; i < n; i++)
        {
            ll sumNode = 0;
            int minNode = INT_MAX;
            int node = i;
            for (size_t j = 0; j < L; j++)
                if (k & (1LL << j))
                {
                    sumNode += sum[j][node];
                    minNode = min(minNode, mini[j][node]);
                    node = par[j][node];
                }
            cout << sumNode << ' ' << minNode << '\n';
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
