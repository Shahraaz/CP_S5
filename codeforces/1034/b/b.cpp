#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second

using flowUnit = long long;
struct Edge
{
    int from, to;
    flowUnit cap, flow;
    int index;
    Edge(int from, int to, flowUnit cap, flowUnit flow, int index) : from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushReLabel
{
    int n;
    vector<vector<Edge>> g;
    vector<flowUnit> excess;
    vector<int> height, active, count;
    queue<int> Q;

    PushReLabel(int n) : n(n), g(n), excess(n), height(n), active(n), count(2 * n) {}

    void addEdge(int from, int to, flowUnit cap)
    {
        g[from].pb(Edge(from, to, cap, 0, g[to].size()));
        if (from == to)
            g[from].back().index++;
        g[to].pb(Edge(to, from, 0, 0, g[from].size() - 1));
    }

    void enqueue(int node)
    {
        if (!active[node] && excess[node] > 0)
        {
            active[node] = 0;
            Q.push(node);
        }
    }

    void push(Edge &e)
    {
        flowUnit amt = min(excess[e.from], e.cap - e.flow);
        if (height[e.from] <= height[e.to] || amt == 0)
            return;
        e.flow += amt;
        g[e.to][e.index].flow -= amt;
        excess[e.to] += amt;
        excess[e.from] -= amt;
        enqueue(e.to);
    }

    void relabel(int node)
    {
        count[height[node]]--;
        int d = 2 * n;
        for (auto &it : g[node])
            if (it.cap - it.flow > 0)
                d = min(d, height[it.to] + 1);
        height[node] = d;
        count[height[node]]++;
        enqueue(node);
    }

    void gap(int k)
    {
        for (int node = 0; node < n; node++)
        {
            if (height[node] < k)
                continue;
            count[height[node]]--;
            height[node] = max(height[node], n + 1);
            count[height[node]]++;
            enqueue(node);
        }
    }

    void discharge(int node)
    {
        for (size_t i = 0; excess[node] > 0 && i < g[node].size(); i++)
            push(g[node][i]);
        if (excess[node] > 0)
        {
            if (count[height[node]] == 1)
                gap(height[node]);
            else
                relabel(node);
        }
    }

    flowUnit max_flow(int source, int dest)
    {
        count[0] = n - 1;
        count[n] = 1;
        height[source] = n;
        active[source] = active[dest] = 1;
        for (auto &it : g[source])
        {
            excess[source] += it.cap;
            push(it);
        }
        while (Q.size())
        {
            auto node = Q.front();
            Q.pop();
            active[node] = false;
            discharge(node);
        }
        flowUnit max_flow = 0;
        for (auto &it : g[source])
            max_flow += it.flow;
        return max_flow;
    }
};

const int LIM = 10;
ll cache[LIM + 1][LIM + 1];

vector<pair<int, int>> dirs = {{1, -2}, {2, -1}, {3, 0}, {2, 1}, {1, 2}, {0, 3}};

ll brute_force(int a, int b)
{
    if (a <= 0 || b <= 0 || a > LIM || b > LIM)
        return 0;
    // assert(a <= LIM && b <= LIM);
    ll &ret = cache[a][b];
    // db(a, b, ret);
    if (ret != -1)
        return ret;
    vector<vector<int>> adj(a * b);
    PushReLabel p(a * b + 2);
    // db(a, b);
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if ((i + j) & 1)
                p.addEdge(a * b, i * b + j, 1);
            else
                p.addEdge(i * b + j, a * b + 1, 1);
            for (auto dir : dirs)
            {
                int x = i + dir.first;
                int y = j + dir.second;
                if (0 <= x && x < a && 0 <= y && y < b)
                {
                    // db(i, j, a, b);
                    if ((i + j) & 1)
                        p.addEdge(i * b + j, x * b + y, 1);
                    else
                        p.addEdge(x * b + y, i * b + j, 1);
                    // adj[i * b + j].pb(x * b + y);
                    // [] = 1;
                    // adj[x * b + y].pb(i * b + j);
                    // [i * b + j] = 1;
                }
            }
        }
    }
    ret = 2 * p.max_flow(a * b, a * b + 1);
    db(a, b, ret, a * b);
    return ret;
}

void solveCase()
{
    // memset(cache, -1, sizeof cache);

    // for (int i = 1; i <= LIM; i++)
    // {
    //     // cout << i << ' ';
    //     for (int j = i; j <= LIM; j++)
    //     {
    //         brute_force(i, j);
    //         // cout << brute_force(i, j) - i * j << ' ';
    //     }
    //     // cout << '\n';
    // }

    // return;
    ll n, m;
    cin >> n >> m;

    if (n > m)
        swap(n, m);

    if (n == 1)
        cout << 6 * (m / 6) + 2 * (max(0LL, m % 6 - 3)) << '\n';
    else if (n == 2)
    {
        if (m == 2)
            cout << 0 << '\n';
        else if (m == 3)
            cout << 4 << '\n';
        else if (m == 7)
            cout << 12 << '\n';
        else
            cout << n * m << '\n';
    }
    else
    {
        cout << n * m - ((n & 1) && (m & 1)) << '\n';
    }
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
        solveCase();
    return 0;
}