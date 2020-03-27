// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

int a[NAX];
int ans[NAX];
vector<int> adj[NAX];
int seive[NAX];

class Solution
{
private:
    int gcd(int a, int b)
    {
        if (a == 0 || b == 0)
            return a + b;
        if (a > b)
            swap(a, b);
        return gcd(b % a, a);
    }
    void dfs(int node, int par, int depth, int currGcd)
    {
        ans[node] = currGcd;
        for (ll i = 1; i * i <= a[node]; i++)
        {
            if (a[node] % i == 0)
            {
                ++seive[i];
                if (i * i != a[node])
                    ++seive[a[node] / i];
                if (seive[i] >= depth)
                    ans[node] = max(ans[node], (int)i);
                if (seive[a[node] / i] >= depth)
                    ans[node] = max(ans[node], a[node] / (int)i);
            }
        }
        for (auto &child : adj[node])
            if (child != par)
                dfs(child, node, depth + 1, gcd(currGcd, a[node]));
        for (ll i = 1; i * i <= a[node]; i++)
        {
            if (a[node] % i == 0)
            {
                --seive[i];
                if (i * i != a[node])
                    --seive[a[node] / i];
                // if (seive[i] >= depth)
                //     ans[node] = max(ans[node], (int)i);
                // if (seive[a[i] / i] >= depth)
                //     ans[node] = max(ans[node], a[i] / (int)i);
            }
        }
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
            cin >> a[i + 1];
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(1, 1, 0, 0);
        for (size_t i = 1; i <= n; i++)
            cout << ans[i] << ' ';
    }
};

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