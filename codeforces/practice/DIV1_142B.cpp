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

const int NAX = 1e5 + 5, MOD = 1000000007;

vector<pair<int, int>> adj[NAX];
vector<int> blockers[NAX];
vector<int> freeTimes[NAX];
bool vis[NAX];

void solveCase()
{
    int n, m;
    cin >> n >> m;
    for (size_t i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    for (int i = 1; i <= n; i++)
    {
        int k, t;
        cin >> k;
        while (k--)
        {
            cin >> t;
            blockers[i].pb(t);
        }
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    auto getTime = [](int node, int startTime) -> int {
        db(node, startTime);
        pc(blockers[node]);
        for (size_t i = 0; i < blockers[node].size(); i++)
        {
            if (blockers[node][i] < startTime)
                continue;
            int idx = i;
            while (idx != blockers[node].size() && blockers[node][idx] == startTime)
                idx++, startTime++;
            db(idx);
            break;
        }
        db(startTime);
        return startTime;
    };
    Q.push({0, 1});
    int answer = INT_MAX;
    while (!Q.empty())
    {
        int node = Q.top().second;
        int time = Q.top().first;
        Q.pop();
        if (node == n)
        {
            answer = min(answer, time);
            continue;
        }
        if (vis[node])
            continue;
        vis[node] = true;
        time = getTime(node, time);
        for (auto &child : adj[node])
        {
            if (vis[child.f])
                continue;
            Q.push({time + child.s, child.f});
        }
    }
    if (answer == INT_MAX)
        cout << -1 << '\n';
    else
        cout << answer << '\n';
}

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
