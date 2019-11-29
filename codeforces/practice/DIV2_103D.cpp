//Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
#define pc(...) PC(#__VA_ARGS__, __VA_ARGS__);
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}
template <typename Arg>
void PC(const char *name, Arg &&arg)
{
    while (*name == ',' || *name == ' ')
        name++;
    std::cerr << name << " { ";
    for (const auto &v : arg)
        cerr << v << ' ';
    cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
    while (*names == ',' || *names == ' ')
        names++;
    const char *comma = strchr(names, ',');
    std::cerr.write(names, comma - names) << " { ";
    for (const auto &v : arg1)
        cerr << v << ' ';
    cerr << " }\n";
    PC(comma, args...);
}
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1;
    ZZ(comma, args...);
}
#else
#define db(...)
#define pc(...)
#endif

using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const int NAX = 2e5 + 10, MOD = 1000000007;
int n, m, s, l;
vector<pair<int, ll>> adj[NAX];
vector<pair<pair<int, int>, ll>> edges;
vector<ll> dist;

void solveCase(int caseNo)
{
    cin >> n >> m >> s;
    --s;
    int u, v, w;
    db("here");
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        --u;
        --v;
        db(u, v, w);
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        edges.pb({{u, v}, w});
    }
    db("here");
    cin >> l;
    dist.resize(n, 1e18);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> Q;
    vector<bool> vis(n);
    Q.push({0, s});
    ll ans = 0;
    while (!Q.empty())
    {
        auto top = Q.top();
        Q.pop();
        db(top);
        if (vis[top.s])
            continue;
        vis[top.s] = true;
        if (top.f == l)
            ans++;
        for (auto child : adj[top.s])
        {
            if (dist[child.f] > dist[top.s] + child.s)
            {
                dist[child.f] = dist[top.s] + child.s;
                Q.push({dist[child.f], child.f});
            }
        }
    }
    db("here");
    for (int i = 0; i < m; ++i)
    {
        u = edges[i].f.f;
        v = edges[i].f.s;
        w = edges[i].s;
        db(u, v, w);
        ll fromU = l - dist[u];
        ll fromV = l - dist[v];
        db("End");
        if (fromU + fromV < w)
        {
            if ((fromU <= 0 || fromU >= w) && (fromV <= 0 || fromV >= w))
                continue;
            else if ((fromU <= 0 || fromU >= w) || (fromV <= 0 || fromV >= w))
                ans++;
            else
                ans += 2;
        }
        else 
            if(fromU + fromV == w && fromU > 0&& fromU < w)
                ans++;
    }
    cout << ans << '\n';
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    for (int i = 0; i < t; ++i)
        solveCase(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}