//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
#ifdef WIN32
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
    std::cerr << name << " { ";
    for (const auto &v : arg)
        cerr << v << ' ';
    cerr << " }\n";
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
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 5e4 + 10;
set<int> Adj[nax];
int n, isNotPrime[nax], len;
vector<int> Prime;

void build()
{
    // db("Debug Start");
    Prime.pb(2);
    for (int j = 4; j < nax; j += 2)
        isNotPrime[j] = 1;
    // db("Even Crossed");
    for (int i = 3; i < nax; i += 2)
        if (!isNotPrime[i])
        {
            // db(i, len, i * i);
            // cout << i << ' ' << len << '\n';
            Prime.pb(i);
            // len++;
            for (ll j = (ll)i * i; j < nax; j += i)
            {
                // db(j);
                isNotPrime[j] = 1;
            }
        }
    len = Prime.size();
    // db("Primes recorded");
}

int currentTreeSize, subTreeSize[nax], ndist[20][nax];

void dfs1(int node, int p)
{
    subTreeSize[node] = 1;
    currentTreeSize++;
    for (auto child : Adj[node])
        if (child != p)
        {
            dfs1(child, node);
            subTreeSize[node] += subTreeSize[child];
        }
}

int getCentroid(int node, int p)
{
    for (auto child : Adj[node])
        if (child != p)
            if (subTreeSize[child] > currentTreeSize / 2)
                return getCentroid(child, node);
    return node;
}

void dfs3(int node, int p, int depth, int dist, int add)
{
    ndist[depth][dist] += add;
    for (auto child : Adj[node])
        if (child != p)
            dfs3(child, node, depth, dist + 1, add);
}

ll ans = 0;

ll dfs4(int node, int p, int depth, int dist)
{
    ll ret = 0;
    for (int i = 0; i < len; ++i)
    {
        if (Prime[i] - dist < 0)
            continue;
        if (!ndist[depth][Prime[i] - dist])
            break;
        if (Prime[i] != dist)
            ret += ndist[depth][Prime[i] - dist];
        else
            ret += 2 * ndist[depth][Prime[i] - dist];
    }
    for (auto child : Adj[node])
        if (child != p)
            ret += dfs4(child, node, depth, dist + 1);
    return ret;
}

void decompose(int node, int depth)
{
    currentTreeSize = 0;
    dfs1(node, node);
    int centroid = getCentroid(node, node);
    dfs3(centroid, centroid, depth, 0, 1);
    ll add = 0;
    node = centroid;
    for (auto child : Adj[node])
    {
        dfs3(child, node, depth, 1, -1);
        add += dfs4(child, node, depth, 1);
        dfs3(child, node, depth, 1, 1);
    }
    ans += add / 2;
    for (auto child : Adj[node])
    {
        Adj[child].erase(node);
        decompose(child, depth + 1);
    }
    for (int i = 0; i < nax && ndist[depth][i]; ++i)
        ndist[depth][i] = 0;
}

void solve()
{
    build();
    cin >> n;
    int u, v;
    for (int i = 1; i < n; ++i)
    {
        cin >> u >> v;
        --u;
        --v;
        Adj[u].insert(v);
        Adj[v].insert(u);
    }
    decompose(0, 0);
    long double res = (long double)ans * 2 / ((ll)n * (n - 1));
    cout << fixed << setprecision(10);
    cout << res << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
#ifdef multitest
    cin >> t;
#endif
    while (t--)
        solve();
#ifdef WIN32
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}