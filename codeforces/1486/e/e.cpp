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
const int NAX = 1e5 + 5, MOD = 1000000007;

const int MAXWT = 52;
ll oddPath[NAX][MAXWT];
int visoddPath[NAX][MAXWT];
vector<pair<int, int>> adj[NAX];

void solveCase()
{
    int n, m;
    cin >> n >> m;
    for (size_t i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    memset(oddPath, -1, sizeof oddPath);
    oddPath[0][0] = 0;
    // visoddPath[0][0] = 1;
    priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>, greater<pair<ll, pair<int, int>>>> pQ;
    pQ.push({0, {0, 0}});
    while (pQ.size())
    {
        auto top = pQ.top();
        pQ.pop();
        ll curr = top.first;
        int node = top.second.second;
        int wt = top.second.first;
        db(top, visoddPath[node][wt]);
        if (visoddPath[node][wt])
            continue;
        visoddPath[node][wt] = 1;
        if (wt == 0)
        {
            for (auto &x : adj[node])
                if (!visoddPath[x.first][x.second])
                    if (oddPath[x.first][x.second] == -1 || (curr) < oddPath[x.first][x.second])
                    {
                        oddPath[x.first][x.second] = curr;
                        pQ.push({oddPath[x.first][x.second], {x.second, x.first}});
                    }
        }
        else
        {
            for (auto &x : adj[node])
                if (!visoddPath[x.first][0])
                    if (oddPath[x.first][0] == -1 || (curr + ((x.second + wt) * (x.second + wt))) < oddPath[x.first][0])
                    {
                        oddPath[x.first][0] = (curr + ((x.second + wt) * (x.second + wt)));
                        pQ.push({oddPath[x.first][0], {0, x.first}});
                    }
        }
    }
    for (size_t i = 0; i < n; i++)
        cout << oddPath[i][0] << ' ';
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
        solveCase();
    return 0;
}