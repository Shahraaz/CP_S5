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

#define MAX 2001 * 2001
#define NIL 0
#define INF (1 << 28)

vector<int> G[MAX];
int n, match[MAX], dist[MAX];
int vis[MAX], degree[MAX];
// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]

bool bfs()
{
    int i, u, v, len;
    queue<int> Q;
    for (i = 1; i <= n; i++)
    {
        if (match[i] == NIL)
        {
            dist[i] = 0;
            Q.push(i);
        }
        else
            dist[i] = INF;
    }
    dist[NIL] = INF;
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();
        if (u != NIL)
        {
            len = G[u].size();
            for (i = 0; i < len; i++)
            {
                v = G[u][i];
                if (dist[match[v]] == INF)
                {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL] != INF);
}

bool dfs(int u)
{
    int i, v, len;
    if (u != NIL)
    {
        len = G[u].size();
        for (i = 0; i < len; i++)
        {
            v = G[u][i];
            if (dist[match[v]] == dist[u] + 1)
            {
                if (dfs(match[v]))
                {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp()
{
    int matching = 0, i;
    // match[] is assumed NIL for all vertex in G
    while (bfs())
        for (i = 1; i <= n; i++)
            if (match[i] == NIL && dfs(i))
                matching++;
    return matching;
}

vector<pair<int, int>> dxy = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<string> vecc(n);
    for (auto &x : vecc)
        cin >> x;
    ::n = n * m;
    int cnt = 0;
    vector<int> cands;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (vecc[i][j] == '.')
            {
                cands.pb(i * m + j + 1);
                cnt++;
                for (auto d : dxy)
                {
                    int x = i + d.first;
                    int y = j + d.second;
                    if (0 <= x && x < n && 0 <= y && y < m)
                        if (vecc[x][y] == '.')
                        {
                            G[i * m + j + 1].pb(x * m + y + 1);
                            // G[x * m + y + 1].pb(i * m + j + 1);
                        }
                }
            }
        }
    vector<string> ret = vecc;
    queue<int> Q;
    db(cands);
    for (auto &x : cands)
    {
        db(x, G[x]);
        degree[x] = G[x].size();
        if (G[x].size() == 1)
        {
            Q.push(x);
            vis[x] = 1;
            degree[x]--;
        }
    }
    while (Q.size())
    {
        auto top = Q.front();
        db(top);
        Q.pop();
        if (match[top] == NIL)
            for (auto &x : G[top])
                if (match[x] == NIL)
                {
                    auto solve = [&](int a, int b) {
                        --a, --b;
                        int x1 = a / m, y1 = a % m;
                        int x2 = b / m, y2 = b % m;
                        if (x1 == x2)
                        {
                            if (y2 == (y1 + 1))
                            {
                                ret[x1][y1] = '<';
                                ret[x2][y2] = '>';
                            }
                            else
                            {
                                ret[x1][y1] = '>';
                                ret[x2][y2] = '<';
                            }
                        }
                        else if (y1 == y2)
                        {
                            if (x2 == (x1 + 1))
                            {
                                ret[x1][y1] = '^';
                                ret[x2][y2] = 'v';
                            }
                            else
                            {
                                ret[x1][y1] = 'v';
                                ret[x2][y2] = '^';
                            }
                        }
                    };
                    solve(top, x);
                    match[top] = x;
                    match[x] = top;
                    Q.push(match[top]);
                    vis[match[top]] = 1;
                    // break;
                }
        db(match[top]);
        for (auto &x : G[top])
            if (!vis[x])
            {
                degree[x]--;
                if (degree[x] == 1)
                {
                    Q.push(x);
                    vis[x] = 1;
                }
            }
    }
    for (auto &x : cands)
    {
        db(x, vis[x], degree[x]);
        if (!vis[x] || ret[(x - 1) / m][(x - 1) % m] == '.')
        {
            cout << "Not unique\n";
            return;
        }
    }
    for (auto &x : ret)
    {
        cout << x << '\n';
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