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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, k;
        cin >> n >> k;
        int parent[n + 1] = {0};
        vector<int> adj[n + 1];
        for (size_t i = 2; i <= n; i++)
        {
            cin >> parent[i];
            adj[i].pb(parent[i]);
            adj[parent[i]].pb(i);
        }
        int depth[n + 1] = {0};
        depth[0] = MOD;
        function<void(int, int, int)> dfs = [&](int node, int par, int level) -> void {
            db(node, par, level);
            depth[node] = level;
            for (auto &x : adj[node])
                if (x != par)
                    dfs(x, node, level + 1);
        };
        dfs(1, 1, 1);
        vector<int> allColorsOnIt[n + 1], parentOfColor[n + 1];
        struct node
        {
            int node, depth;
        };
        vector<node> parentOf;
        int isPut[n + 1] = {0};
        node a;
        for (size_t i = 1; i <= k; i++)
        {
            int len;
            cin >> len;
            int u = 0;
            for (size_t i = 0; i < len; i++)
            {
                int v;
                cin >> v;
                u = depth[u] < depth[v] ? u : v;
                allColorsOnIt[v].pb(i);
            }
            db(i, u);
            a.node = u;
            a.depth = depth[u];
            if (isPut[a.node] == 0)
            {
                parentOf.pb(a);
                isPut[a.node] = 1;
            }
            parentOfColor[u].pb(i);
        }
        sort(all(parentOf), [](node a, node b) -> bool {
            return a.depth > b.depth;
        });
        // db(parentOf);
        int res = 0;
        int isArrested[n + 1] = {0};
        for (size_t i = 0; i < parentOf.size(); i++)
        {
            int u = parentOf[i].node;
            db(parentOf[i].node, parentOf[i].depth);
            db(parentOfColor[u]);
            int flag = 1;
            for (size_t j = 0; j < parentOfColor[u].size() && flag; j++)
                flag = flag && isArrested[parentOfColor[u][j]];
            if (flag == 0)
            {
                res++;
                for (size_t j = 0; j < allColorsOnIt[u].size(); j++)
                    isArrested[allColorsOnIt[u][j]] = 1;
            }
        }

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
