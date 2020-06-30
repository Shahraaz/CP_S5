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

int n;
vector<int> adj[NAX];
int startIdx[NAX], endIdx[NAX], nodeForPos[NAX];
int pos;
int clr[NAX];
int seg[4 * NAX];
int isLazy[4 * NAX];

class Solution
{
private:
    void dfs(int node, int par)
    {
        startIdx[node] = pos;
        nodeForPos[pos] = node;
        ++pos;
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            dfs(x, node);
        }
        endIdx[node] = pos - 1;
        db(node, startIdx[node], endIdx[node]);
    }
    void propagate(int node, int start, int end)
    {
        if (isLazy[node])
        {
            isLazy[node] = false;
            seg[node] = end - start + 1 - seg[node];
            if (start != end)
            {
                isLazy[2 * node] = !isLazy[2 * node];
                isLazy[2 * node + 1] = !isLazy[2 * node + 1];
            }
        }
    }
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            db(node, start, nodeForPos[start], clr[nodeForPos[start]]);
            seg[node] = clr[nodeForPos[start]];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }
    int query(int node, int start, int end, int qstart, int qend)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return 0;
        if (qstart <= start && end <= qend)
            return seg[node];
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, qstart, qend) + query(2 * node + 1, mid + 1, end, qstart, qend);
    }
    void update(int node, int start, int end, int qstart, int qend)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return;
        if (qstart <= start && end <= qend)
        {
            isLazy[node] = true;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(2 * node, start, mid, qstart, qend);
        update(2 * node + 1, mid + 1, end, qstart, qend);
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        for (size_t i = 1; i < n; i++)
        {
            int p;
            cin >> p;
            --p;
            adj[p].pb(i);
            adj[i].pb(p);
        }
        pos = 0;
        dfs(0, -1);
        for (size_t i = 0; i < n; i++)
        {
            cin >> clr[i];
        }
        build(1, 0, n - 1);
#ifdef LOCAL
        // db(q, Q, v);
        for (size_t i = 0; i < n; i++)
        {
            auto Query = query(1, 0, n - 1, startIdx[i], endIdx[i]);
            auto Query2 = query(1, 0, n - 1, startIdx[i], startIdx[i]);
            db(i, Query, Query2, startIdx[i], endIdx[i]);
        }
#endif

        int q;
        cin >> q;
        while (q--)
        {
            string Q;
            int v;
            cin >> Q >> v;
            --v;
            if (Q == "get")
                cout << query(1, 0, n - 1, startIdx[v], endIdx[v]) << '\n';
            else
                update(1, 0, n - 1, startIdx[v], endIdx[v]);
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
