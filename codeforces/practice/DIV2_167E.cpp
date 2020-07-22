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

const int NAX = 3e5 + 5, MOD = 1000000007;

vector<int> adj[NAX];
struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        string ret(n, '0');
        // db(ret);
        for (size_t i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        int ctr = 100;
        bool ok = false;
        while (ctr--)
        {
            ok = true;
            for (size_t i = 0; i < n; i++)
            {
                int k = 0;
                for (auto &x : adj[i])
                    k += ret[x] == ret[i];
                if (k > 1)
                {
                    ret[i] = '1' ^ ret[i] ^ '0';
                    ok = false;
                }
            }
            if (ok)
                break;
        }
        if (ctr)
            cout << ret << '\n';
        else
            cout << -1 << '\n';
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
