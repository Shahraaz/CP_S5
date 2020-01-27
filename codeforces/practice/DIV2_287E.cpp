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

vector<pair<int, int>> graph[NAX];
int D1[NAX], DN[NAX], MaxOp[NAX], parent[NAX], path[NAX];
int from[NAX], to[NAX];
bool opened[NAX], visited[NAX];

void solveCase()
{
    int n, m;
    cin >> n >> m;
    int counter = 0;
    for (int i = 0; i < m; i++)
    {
        cin >> from[i] >> to[i] >> opened[i];
        graph[from[i]].pb({to[i], opened[i]});
        graph[to[i]].pb({from[i], opened[i]});
        counter += opened[i];
    }
    memset(D1, -1, sizeof D1);
    memset(DN, -1, sizeof DN);
    memset(MaxOp, -1, sizeof MaxOp);
    queue<int> Q;
    Q.push(1);
    D1[1] = 0;
    while (!Q.empty())
    {
        int node = Q.front();
        // db("bfs1", node);
        Q.pop();
        for (auto &child : graph[node])
        {
            // db(child);
            if (D1[child.f] == -1)
            {
                D1[child.f] = D1[node] + 1;
                Q.push(child.f);
            }
        }
    }
    Q.push(n);
    DN[n] = 0;
    while (!Q.empty())
    {
        int node = Q.front();
        // db("bfs2", node);
        Q.pop();
        for (auto &child : graph[node])
        {
            // db(child);
            if (DN[child.f] == -1)
            {
                DN[child.f] = DN[node] + 1;
                Q.push(child.f);
            }
        }
    }
    // db("stage 2 Start");
    int d = D1[n];
    db(d);
    Q.push(1);
    MaxOp[1] = 0;
    while (!Q.empty())
    {
        auto node = Q.front();
        Q.pop();
        if (visited[node])
            continue;
        db(node);
        visited[node] = true;
        for (auto &child : graph[node])
        {
            db(child);
            db(D1[child.f], DN[child.f]);
            if ((D1[child.f] + DN[child.f]) != d || (D1[node] + 1 + DN[child.f]) != d || visited[child.f])
                continue;
            db(MaxOp[child.f], MaxOp[node], child.s);
            if (MaxOp[child.f] != -1 && MaxOp[child.f] >= MaxOp[node] + child.s)
                continue;
            Q.push(child.f);
            parent[child.f] = node;
            MaxOp[child.f] = MaxOp[node] + child.s;
        }
    }
    db("stage 2 End");
    int node = n;
    int cnt = 10;
    while (node != 1)
    {
        if (cnt == 0)
            break;
        // cnt--;
        db(node);
        path[node] = parent[node];
        node = path[node];
    }
    cout << counter + d - 2 * MaxOp[n] << '\n';
    for (int i = 0; i < m; i++)
    {
        if (path[from[i]] == to[i] || path[to[i]] == from[i])
        {
            if (!opened[i])
                cout << from[i] << ' ' << to[i] << ' ' << 1 << '\n';
        }
        else if (opened[i])
            cout << from[i] << ' ' << to[i] << ' ' << 0 << '\n';
    }
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
