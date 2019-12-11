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
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 5e5 + 10, MOD = 1000000007;
vector<int> P[NAX];
vector<pair<int, int>> H[NAX];
int In[NAX], Out[NAX];
int ti;
string s;

void dfs(int node, int h)
{
    In[node] = ++ti;
    H[h].pb({ti, H[h].back().s ^ (1 << (s[node] - 'a'))});
    for (auto child : P[node])
        dfs(child, h + 1);
    Out[node] = ++ti;
}

void solveCase(int caseNo)
{
    db(seed);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        H[i].resize(1);
    for (int i = 0; i < n - 1; ++i)
    {
        int v;
        cin >> v;
        P[v - 1].pb(i + 1);
    }
    cin >> s;
    dfs(0, 0);
    while (m--)
    {
        int h, v;
        cin >> v >> h;
        --v, --h;
        int l = lower_bound(H[h].begin(), H[h].end(), make_pair(In[v], -1)) - H[h].begin() - 1;
        int r = lower_bound(H[h].begin(), H[h].end(), make_pair(Out[v], -1)) - H[h].begin() - 1;
        int t = H[h][l].s ^ H[h][r].s;
        if (t - (t & -t))
            cout << "No\n";
        else
            cout << "Yes\n";
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
        solveCase(i);
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}