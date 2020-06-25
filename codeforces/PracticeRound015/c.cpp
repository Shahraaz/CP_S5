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

vector<pair<int, ll>> adj[NAX];
ll a[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        for (size_t i = 0; i < m; i++)
        {
            ll u, v, w;
            cin >> u >> v >> w;
            --u, --v;
            w = 2 * w;
            adj[u].pb({v, w});
            adj[v].pb({u, w});
        }
        set<pair<ll, int>> pp;
        ll currCost[n];
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
            currCost[i] = a[i];
            pp.insert({currCost[i], i});
        }
        db("here") while (pp.size())
        {
            db(pp);
            auto top = *pp.begin();
            pp.erase(top);
            for (auto &x : adj[top.s])
            {
                if (currCost[x.f] > top.f + x.s)
                {
                    pp.erase({currCost[x.f], x.f});
                    currCost[x.f] = top.f + x.s;
                    pp.insert({currCost[x.f], x.f});
                }
            }
        }
        for (size_t i = 0; i < n; i++)
            cout << currCost[i] << ' ';
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
