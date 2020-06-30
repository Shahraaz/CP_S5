// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

vector<int> adj[NAX];
int a[NAX];
vector<int> divisiors[NAX];
int count[NAX], res[NAX];

class Solution
{
private:
    void seive()
    {
        // memset(isPrime, 1, sizeof isPrime);
        // isPrime[0] = isPrime[1] = false;
        for (size_t i = 1; i < NAX; i++)
        {
            for (size_t j = i; j < NAX; j += i)
                divisiors[j].pb(i);
        }
    }
    void dfs(int node, int par, int depth, int currGcd)
    {
        res[node] = currGcd;
        for (auto &x : divisiors[a[node]])
        {
            ::count[x]++;
            if (::count[x] >= depth)
                res[node] = max(res[node], x);
        }
        for (auto &x : adj[node])
            if (x != par)
                dfs(x, node, depth + 1, __gcd(currGcd, a[node]));
        for (auto &x : divisiors[a[node]])
            ::count[x]--;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        seive();
        int n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (size_t i = 1; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            --x, --y;
            adj[x].pb(y);
            adj[y].pb(x);
        }
        dfs(0, -1, 0, a[0]);
        for (size_t i = 0; i < n; i++)
            cout << res[i] << ' ';
        cout << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
