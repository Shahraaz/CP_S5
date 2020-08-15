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

const int HS = 3, K = 10;

int mod[HS];

struct Hash
{
    ll a[HS];
    Hash()
    {
        fill(a, a + HS, 0);
        a[1] = 1;
    }
    Hash(ll x)
    {
        for (size_t i = 0; i < HS; i++)
            a[i] = (x % mod[i] + mod[i]) % mod[i];
    }
    Hash operator+(Hash rhs)
    {
        Hash res;
        res.a[0] = (a[0] + rhs.a[0]) % mod[0];
        res.a[1] = (a[1] * rhs.a[1]) % mod[1];
        res.a[2] = (a[2] + rhs.a[2]) % mod[2];
        return res;
    }
    bool operator==(const Hash &x) const
    {
        for (size_t i = 0; i < HS; i++)
            if (a[i] != x.a[i])
                return false;
        return true;
    }
} val[NAX], c[K][K], s;

ostream &operator<<(ostream &ou, const Hash &hs)
{
    ou << hs.a[0] << ' ' << hs.a[1] << ' ' << hs.a[2] << '\n';
    return ou;
};

int n,
    m, k;
int ans = 0;
vector<pair<int, int>> adj[NAX];
void dfs(int x, Hash hsh)
{
    if (x == k)
    {
        db(hsh, s);
        if (hsh == s)
            ans++;
        return;
    }
    for (size_t i = 1; i <= (x + 1); i++)
        dfs(x + 1, hsh + c[x + 1][i]);
}

struct Solution
{
    Solution() {}
    void solveCase()
    {
        srand(time(NULL));
        mod[0] = MOD;
        mod[1] = 1e9 + 9;
        mod[2] = 1e8 + rand() % int(1e8) + 1;
        db(mod[0], mod[1], mod[2]);
        cin >> n >> m >> k;
        for (size_t i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].pb({w, v});
        }
        for (size_t i = 1; i <= n; i++)
        {
            val[i] = Hash(rand() % MOD + 1);
            s = s + val[i];
        }
        for (size_t i = 1; i <= n; i++)
        {
            int d = adj[i].size();
            sort(all(adj[i]));
            for (int j = 1; j <= d; j++)
            {
                int v = adj[i][j - 1].s;
                c[d][j] = c[d][j] + val[v];
            }
        }
        dfs(0, Hash());
        cout << ans << '\n';
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
