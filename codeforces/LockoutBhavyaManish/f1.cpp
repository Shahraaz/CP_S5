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

const int NAX = 2e6 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

bool isPrime[NAX];
vector<int> primeFactors[NAX];
int n, q;
vector<int> adj[NAX];
int isGood[NAX];
vector<pair<int, int>> lookUp[NAX];

void Solution::solveCase()
{
    cin >> n >> q;
    vector<int> a(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        cin >> a[i];
        isGood[a[i]] = 1;
    }
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> queriesOverNodes(n + 1);
    for (size_t i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<vector<int>> Q;
    vector<int> ans(q + 1);
    for (size_t i = 0; i < q; i++)
    {
        int x, y, z = 0;
        cin >> x;
        if (x == 1)
            cin >> y;
        else
        {
            cin >> y >> z;
            isGood[z] = 1;
        }
        Q.pb({x, y, z});
    }
    fill(isPrime, isPrime + NAX, 1);
    isPrime[0] = isPrime[1] = 0;
    for (size_t i = 2; i < NAX; i++)
    {
        if (isPrime[i])
            for (size_t j = i; j < NAX; j += i)
            {
                if (i != j)
                    isPrime[j] = false;
                if (isGood[j])
                    primeFactors[j].pb(i);
            }
        if (isGood[i])
        {
            db(i, primeFactors[i]);
        }
    }
    function<void(int, int, int)> solve = [&](int node, int par, int depth) -> void {
        pair<int, int> p;
        p.f = -1;
        p.s = -1;
        for (auto &x : primeFactors[a[node]])
        {
            db(node, a[node], x, lookUp[x]);
            if (lookUp[x].size())
                p = max(p, lookUp[x].back());
        }
        for (auto &idx : queriesOverNodes[node])
        {
            ans[idx] = p.s;
        }
        queriesOverNodes[node].clear();
        for (auto &x : primeFactors[a[node]])
            lookUp[x].pb({depth, node});
        for (auto &x : adj[node])
            if (x != par)
                solve(x, node, depth + 1);
        for (auto &x : primeFactors[a[node]])
            lookUp[x].pop_back();
    };
    for (size_t i = 0; i < q; i++)
    {
        int x = Q[i][0];
        if (x == 1)
            queriesOverNodes[Q[i][1]].pb(i);
        else
        {
            solve(1, 0, 0);
            a[Q[i][1]] = Q[i][2];
        }
    }
    solve(1, 0, 0);
    for (size_t i = 0; i < q; i++)
        if (ans[i] != 0)
            cout << ans[i] << '\n';
}

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
