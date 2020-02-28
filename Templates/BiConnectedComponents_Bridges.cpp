// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;


struct BiConnectedComponents
{
    int n, m, T, cmpCnt;
    vector<int> U, V, arr, compId;
    vector<bool> isBridge, vis;
    vector<vector<int>> adj_mytype, Tree;
    vector<queue<int>> Q;

    int getNode(int e, int node)
    {
        return U[e] == node ? V[e] : U[e];
    }

    int dfsBridge(int u, int edge)
    {
        vis[u] = 1;
        arr[u] = T++;
        int dbe = arr[u];
        for (auto &e : adj_mytype[u])
        {
            int v = getNode(e, u);
            if (!vis[v])
                dbe = min(dbe, dfsBridge(v, e));
            else if (e != edge)
                dbe = min(dbe, arr[v]);
        }
        if (dbe == arr[u] && edge != -1)
            isBridge[edge] = true;
        return dbe;
    }

    void dfsBridgeTree(int node)
    {
        int currCmp = cmpCnt;
        Q[currCmp].push(node);
        vis[node] = true;
        while (!Q[currCmp].empty())
        {
            int u = Q[currCmp].front();
            Q[currCmp].pop();
            compId[u] = currCmp;
            for (auto &edge : adj_mytype[u])
            {
                int v = getNode(edge, u);
                if (vis[v])
                    continue;
                if (isBridge[edge])
                {
                    cmpCnt++;
                    Tree[cmpCnt].push_back(currCmp);
                    Tree[currCmp].push_back(cmpCnt);
                    dfsBridgeTree(v);
                }
                else
                {
                    Q[currCmp].push(v);
                    vis[v] = true;
                }
            }
        }
    }

    void build_tree(vector<vector<int>> &adj)
    {
        n = adj.size();
        m = 0;
        adj_mytype.assign(n, vector<int>());
        U.clear();
        V.clear();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                if (i < adj[i][j])
                {
                    U.push_back(i);
                    V.push_back(adj[i][j]);
                    adj_mytype[i].push_back(m);
                    adj_mytype[adj[i][j]].push_back(m);
                    m++;
                }
            }
        }
        // db(m);
        isBridge.assign(m, false);
        vis.assign(n, false);
        arr.assign(n, 0);
        T = 0;
        dfsBridge(0, -1);
        fill(vis.begin(), vis.end(), false);
        Tree.assign(n, vector<int>());
        cmpCnt = 0;
        compId.assign(n, 0);
        Q.assign(n, queue<int>());
        dfsBridgeTree(0);
        Tree.resize(cmpCnt + 1);
    }
};
