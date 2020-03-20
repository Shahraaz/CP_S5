// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

vector<int> adj[NAX];
vector<int> org[NAX];
int dist[NAX];
int Next[NAX];

class Solution
{
private:
    int n, m, pathLen;
    vector<int> path;

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> m;
        for (size_t i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[v].pb(u);
            org[u].pb(v);
        }
        cin >> pathLen;
        path.resize(pathLen);
        for (auto &x : path)
            cin >> x;
        int src = path[0], dest = path.back();
        queue<int> Q;
        memset(dist, -1, sizeof dist);
        dist[dest] = 0;
        Q.push(dest);
        while (!Q.empty())
        {
            auto node = Q.front();
            Q.pop();
            db(node, dist[node]);
            for (auto &child : adj[node])
            {
                if (dist[child] != -1)
                    continue;
                dist[child] = dist[node] + 1;
                Next[child] = node;
                Q.push(child);
            }
        }
        int mini = 0, maxi = 0;
        for (size_t i = 0; i < pathLen - 1; i++)
        {
            int cntPossibleWays = 0;
            int currNode = path[i];
            int nextNode = path[i + 1];
            bool isNextNodeCorrect = false;
            for (auto &child : org[currNode])
            {
                if ((dist[currNode]) == dist[child] + 1)
                {
                    cntPossibleWays++;
                    if (child == nextNode)
                        isNextNodeCorrect = true;
                }
            }
            db(currNode, nextNode, cntPossibleWays, isNextNodeCorrect);
            if (isNextNodeCorrect)
            {
                if (cntPossibleWays > 1)
                    maxi++;
            }
            else
            {
                mini++;
                maxi++;
            }
        }
        cout << mini << ' ' << maxi << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}