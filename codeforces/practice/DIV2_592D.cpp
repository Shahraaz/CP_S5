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

int n;
vector<int> cost[3];
vector<int> adj[NAX];

void solveCase()
{
    cin >> n;
    for (int i = 0; i < 3; i++)
    {
        cost[i] = vector<int>(n);
        for (size_t j = 0; j < n; j++)
            cin >> cost[i][j];
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int start = -1;
    for (int i = 0; i < n; i++)
    {
        if (adj[i].size() > 2)
        {
            cout << -1 << '\n';
            return;
        }
        else if (adj[i].size() == 1)
            start = i;
    }
    vector<int> order = {start};
    while (order.size() < n)
    {
        int current = order.back();
        for (auto &child : adj[current])
            if (order.size() == 1 || child != order[order.size() - 2])
            {
                order.pb(child);
                break;
            }
    }
    vector<int> perm = {0, 1, 2};
    vector<int> bestPerm;
    ll best = LLONG_MAX;
    do
    {
        ll score = 0;
        for (size_t i = 0; i < n; i++)
            score += cost[perm[i % 3]][order[i]];
        if (score < best)
        {
            best = score;
            bestPerm = perm;
        }
    } while (next_permutation(all(perm)));
    cout << best << '\n';
    vector<int> answer(n);
    for (int i = 0; i < n; i++)
        answer[order[i]] = bestPerm[i % 3];
    for (size_t i = 0; i < n; i++)
    {
        cout << answer[i] + 1 << ' ';
    }
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
