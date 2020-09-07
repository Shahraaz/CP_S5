#include <bits/stdc++.h>
using namespace std;


const int NAXL = 1e3 + 5, MODL = 1000000007;

int last[NAXL], cap[NAXL], flow[NAXL];
int to[NAXL], _prev[NAXL], used[NAXL], level[NAXL];

struct MaxFlow
{
    int V, E;
    MaxFlow(int n)
    {
        V = n, E = 0;
        for (int i = 0; i < n; i++)
            last[i] = -1;
    }
    void add_edge(int x, int y, int f)
    {
        cap[E] = f;
        flow[E] = 0;
        to[E] = y;
        _prev[E] = last[x];
        last[x] = E;
        E++;

        cap[E] = 0;
        flow[E] = 0;
        to[E] = x;
        _prev[E] = last[y];
        last[y] = E;
        E++;
    }

    bool bfs(int s, int t)
    {
        for (size_t i = 0; i < V; i++)
            level[i] = -1;
        queue<int> Q;
        Q.push(s);
        level[s] = 0;
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for (int i = last[x]; i >= 0; i = _prev[i])
            {
                if (level[to[i]] == -1 && cap[i] > flow[i])
                {
                    Q.push(to[i]);
                    level[to[i]] = level[x] + 1;
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int t, int f)
    {
        if (v == t)
            return f;
        for (int i = used[v]; i >= 0; used[v] = i = _prev[i])
        {
            if (level[to[i]] > level[v] && cap[i] > flow[i])
            {
                int tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
                if (tmp > 0)
                {
                    flow[i] += tmp;
                    flow[i ^ 1] -= tmp;
                    return tmp;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t)
    {
        int i;
        while (bfs(s, t))
        {
            for (size_t i = 0; i < V; i++)
                used[i] = last[i];
            while (true)
            {
                int temp = dfs(s, t, MODL);
                if (temp == 0)
                    break;
            }
        }
        int ans = 0;
        for (int i = last[s]; i >= 0; i = _prev[i])
            ans += flow[i];
        return ans;
    }
};

//Weighted flow
// https://cp-algorithms.com/graph/min_cost_flow.html

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
