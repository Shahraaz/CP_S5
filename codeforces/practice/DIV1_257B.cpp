// Optimise
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
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n, m, k;
    cin >> n >> m >> k;
    map<pair<int, int>, int> Map;
    vector<pair<long long, pair<int, int>>> adj[n];
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        --x, --y;
        if (x > y)
            swap(x, y);
        if (Map.find({x, y}) == Map.end())
            Map[{x, y}] = w;
        else
            Map[{x, y}] = min(Map[{x, y}], w);
    }
    map<int, int> trains;
    for (int i = 0; i < k; i++)
    {
        int s, x;
        cin >> s >> x;
        --s;
        if (trains.find(s) == trains.end())
            trains[s] = x;
        else
            trains[s] = min(trains[s], x);
    }
    for (auto &elem : Map)
    {
        adj[elem.f.f].pb({elem.s, {elem.f.s, -1}});
        adj[elem.f.s].pb({elem.s, {elem.f.f, -1}});
    }
    int cnt = 0;
    for (auto &t : trains)
        adj[0].pb({t.s, {t.f, cnt++}});
    db("GraphPrepared");
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
    vector<int> Token(n, -1), visToken(k);
    vector<bool> vis(n);
    const long long MAX = 1e15;
    vector<ll> dist(n, MAX);
    dist[0] = 0;
    Q.push({0, 0});
    db("GraphPrepared");
    while (!Q.empty())
    {
        auto top = Q.top();
        db(top);
        Q.pop();
        if (vis[top.s])
            continue;
        vis[top.s] = true;
        for (auto &child : adj[top.s])
        {
            ll currWt = child.f;
            int Tkn = child.s.s;
            int next = child.s.f;
            db(currWt, Tkn, next);
            if (vis[next])
                continue;
            if (top.f + currWt < dist[next] || (top.f + currWt == dist[next] && Token[next] != -1 && Tkn == -1))
            {
                dist[next] = top.f + currWt;
                if (Token[next] > -1)
                    visToken[Token[next]]--;
                Token[next] = Tkn;
                if (Token[next] > -1)
                    visToken[Token[next]]++;
                Q.push({dist[next], next});
            }
        }
    }
    int ans = 0;
    for (auto &x : visToken)
    {
        ans += x == 0;
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
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
