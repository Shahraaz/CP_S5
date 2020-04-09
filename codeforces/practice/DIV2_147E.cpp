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

struct Edge
{
    int from, to, capacity, cost;
};

struct MyFlow
{

    vector<vector<int>> adj, cost, capacity;
    const int INF = 1e9;
    pair<int, int> doIt(int N, vector<Edge> edges, int K, int s, int t)
    {
        adj.resize(N);
        cost.assign(N, vector<int>(N));
        capacity.assign(N, vector<int>(N));
        for (auto &e : edges)
        {
            adj[e.from].pb(e.to);
            adj[e.to].pb(e.from);
            cost[e.from][e.to] = e.cost;
            cost[e.to][e.from] = -e.cost;
            capacity[e.from][e.to] = e.capacity;
        }
        int flow = 0;
        int cost = 0;
        d.clear(), p.clear();
        while (flow < K)
        {
            shortest_path(N, s);
            pc(d);
            pc(p);
            if (d[t] == INF)
                break;
            int f = K - flow;
            int cur = t;
            while (cur != s)
            {
                f = min(f, capacity[p[cur]][cur]);
                cur = p[cur];
            }
            flow += f;
            cost += f * d[t];
            cur = t;
            while (cur != s)
            {
                capacity[p[cur]][cur] -= f;
                capacity[cur][p[cur]] += f;
                cur = p[cur];
            }
        }
        if (flow < K)
            return {-1, cost};
        return {flow, cost};
    }
    vector<int> d, p;
    void shortest_path(int N, int v0)
    {
        d.assign(N, INF);
        d[v0] = 0;
        vector<bool> inq(N, false);
        queue<int> q;
        q.push(v0);
        p.assign(N, -1);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (auto &v : adj[u])
            {
                if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v])
                {
                    d[v] = d[u] + cost[u][v];
                    p[v] = u;
                    if (!inq[v])
                    {
                        inq[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
};

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        string str;
        cin >> str;
        vector<int> freq(27);
        for (auto &x : str)
            freq[x - 'a' + 1]++;
        vector<Edge> edges;
        for (size_t i = 1; i < 27; i++)
            if (freq[i])
                edges.pb(Edge{0, i, freq[i], 0});
        int n;
        cin >> n;
        const int SINK = 150;
        for (size_t i = 1; i <= n; i++)
        {
            string str;
            cin >> str;
            int a;
            cin >> a;
            vector<int> freq(27);
            for (auto &x : str)
                freq[x - 'a' + 1]++;
            for (size_t j = 1; j < 27; j++)
                edges.pb(Edge{j, 30 + i, freq[j], i});
            edges.pb(Edge{30 + i, SINK, a, 0});
        }
        MyFlow m;
        auto ret = m.doIt(151, edges, str.size(), 0, SINK);
        db(ret);
        if (ret.f != str.size())
            cout << -1 << '\n';
        else
            cout << ret.s << '\n';
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