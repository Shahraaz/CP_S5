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

const int NAX = 1e3 + 5, MOD = 1000000007;

vector<int> adj[NAX];
int isRemoved[NAX];

class Solution
{
private:
    int sz;
    vector<int> tempSubTree;
    bool dfs(int node, int par, int u, int v)
    {
        bool ret = false;
        for (auto &chil : adj[node])
        {
            if (chil == par || isRemoved[chil])
                continue;
            ret |= dfs(chil, node, u, v);
        }
        tempSubTree.pb(node);
        if (node == u || node == v)
            ret = true;
        return ret;
    }
    int maxDist;
    int farthestNode;
    void dfs(int node, int par, int dist)
    {
        for (auto &chil : adj[node])
        {
            if (chil == par || isRemoved[chil])
                continue;
            dfs(chil, node, dist + 1);
        }
        if (maxDist < dist)
        {
            maxDist = dist;
            farthestNode = node;
        }
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        sz = n;
        vector<int> aval;
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            aval.pb(i);
            adj[u].pb(v);
            adj[v].pb(u);
        }
        aval.pb(n);
        int lca = -1;
        while (sz != 1)
        {
            // int u = Random<int>(0, aval.size() - 1)(rng);
            int v = aval[0];
            if (aval.size() == 1)
            {
                cout << "! " << v << endl;
                return;
            }
            int u;
            maxDist = -1;
            dfs(v, v, 0);
            u = farthestNode;
            maxDist = -1;
            dfs(u, u, 0);
            v = farthestNode;
            cout << "? ";
            cout << u << ' ' << v << endl;
            cin >> lca;
            if (aval.size() == 2)
            {
                cout << "! " << lca << endl;
                return;
            }
            // db(u, v, lca);
            for (auto &child : adj[lca])
            {
                tempSubTree.clear();
                bool check = dfs(child, lca, u, v);
                db(child, lca, u, v, check);
                pc(tempSubTree);
                if (check)
                {
                    for (auto &elem : tempSubTree)
                    {
                        isRemoved[elem] = true;
                    }
                    vector<int> temp;
                    sort(all(tempSubTree));
                    for (auto &elem : aval)
                        if (upper_bound(all(tempSubTree), elem) - lower_bound(all(tempSubTree), elem) == 0)
                            temp.pb(elem);
                    aval = temp;
                }
            }
        }
        // cout <<
    }
};

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
