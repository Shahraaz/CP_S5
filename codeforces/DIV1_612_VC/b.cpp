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

const int NAX = 2000 + 5, MOD = 1000000007;

vector<int> adj[NAX];
int c[NAX], n, sizes[NAX], a[NAX], A[NAX];

vector<int> dfs(int node, int par)
{
    vector<int> temp;
    for (auto &child : adj[node])
        if (child != par)
        {
            auto child_res = dfs(child, node);
            temp.insert(temp.end(), child_res.begin(), child_res.end());
        }
    if (c[node] > temp.size())
    {
        cout << "NO\n";
        exit(0);
    }
    temp.insert(temp.begin() + c[node], node);
    db(node, par, temp);
    return temp;
}

void solveCase()
{
    cin >> n;
    int root = 0;
    for (size_t i = 1; i <= n; i++)
    {
        int p;
        cin >> p >> c[i];
        if (p == 0)
            root = i;
        else
        {
            adj[p].pb(i);
            adj[i].pb(p);
        }
    }
    db(root);
    auto res = dfs(root, root);
    for (size_t i = 0; i < n; i++)
        a[res[i]] = i + 1;
    cout << "YES\n";
    for (size_t i = 1; i <= n; i++)
        cout << a[i] << ' ';
    cout << '\n';
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
