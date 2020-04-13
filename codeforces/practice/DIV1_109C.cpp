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

const int NAX = 1e6 + 5, MOD = 1000000007;

struct Hash_RabinKarp
{
    const int maxSize = 1e6 + 10;
    const long long p1 = 805306457, p2 = 29, p3 = 31;
    const int mod1 = 1610612741, mod2 = 2100003221, mod3 = 1e9 + 9;
    vector<long long> p_pow1, p_pow2, p_pow3;
    vector<long long> inv_pow1, inv_pow2, inv_pow3;
    ll expo(ll base, int index, int mod)
    {
        if (index == 0)
            return 1;
        ll temp = expo(base, index / 2, mod);
        temp = (temp * temp) % mod;
        if (index & 1)
            temp = (temp * base) % mod;
        return temp;
    }
    Hash_RabinKarp()
    {
        p_pow1.resize(maxSize);
        p_pow2.resize(maxSize);
        p_pow3.resize(maxSize);
        inv_pow1.resize(maxSize);
        inv_pow2.resize(maxSize);
        inv_pow3.resize(maxSize);
        p_pow1[0] = p_pow2[0] = p_pow3[0] = 1;
        for (int i = 1; i < (int)p_pow1.size(); i++)
        {
            p_pow1[i] = (p_pow1[i - 1] * p1) % mod1;
            p_pow2[i] = (p_pow2[i - 1] * p2) % mod2;
            p_pow3[i] = (p_pow3[i - 1] * p3) % mod3;
        }
        inv_pow1[maxSize - 1] = expo(p_pow1[maxSize - 1], mod1 - 2, mod1);
        inv_pow2[maxSize - 1] = expo(p_pow2[maxSize - 1], mod2 - 2, mod2);
        inv_pow3[maxSize - 1] = expo(p_pow3[maxSize - 1], mod3 - 2, mod3);
        for (int i = maxSize - 2; i >= 0; --i)
        {
            inv_pow1[i] = (inv_pow1[i + 1] * p1) % mod1;
            inv_pow2[i] = (inv_pow2[i + 1] * p2) % mod2;
            inv_pow3[i] = (inv_pow3[i + 1] * p3) % mod3;
        }
    }
} hashTables;

const int kmod = 1000000007;

int mul(int a, int b, int mod = kmod)
{
    return (long long)a * b % mod;
}

ll add(ll a, ll b, ll mod = kmod)
{
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

ll sub(ll a, ll b, ll mod = kmod)
{
    a -= b;
    if (a < 0)
        a += mod;
    return a;
}

vector<int> adj[NAX];
pair<ll, pair<ll, ll>> hashNodes[NAX];

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
        vector<pair<int, int>> edges;
        auto addhash = [&](int u, int v) {
            hashNodes[u].f = add(hashNodes[u].f, hashTables.p_pow1[v + 1], hashTables.mod1);
            hashNodes[u].s.f = add(hashNodes[u].s.f, hashTables.p_pow2[v + 1], hashTables.mod2);
            hashNodes[u].s.s = add(hashNodes[u].s.s, hashTables.p_pow3[v + 1], hashTables.mod3);
        };
        auto subhash = [&](int u, int v) {
            hashNodes[u].f = sub(hashNodes[u].f, hashTables.p_pow1[v + 1], hashTables.mod1);
            hashNodes[u].s.f = sub(hashNodes[u].s.f, hashTables.p_pow2[v + 1], hashTables.mod2);
            hashNodes[u].s.s = sub(hashNodes[u].s.s, hashTables.p_pow3[v + 1], hashTables.mod3);
        };
        for (size_t i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            edges.pb({u, v});
            addhash(u, v);
            addhash(v, u);
        }
        vector<pair<ll, pair<ll, ll>>> hashes;
        for (size_t i = 1; i <= n; i++)
            hashes.pb(hashNodes[i]);
        db(hashes);
        db(edges);
        ll res = 0;
        sort(all(hashes));
        for (auto it = hashes.begin(); it != hashes.end();)
        {
            auto up = upper_bound(all(hashes), *it);
            ll cnt = up - it;
            res += (cnt) * (cnt - 1) / 2;
            it = up;
        }
        db(res);
        for (auto &edge : edges)
        {
            addhash(edge.f, edge.f);
            addhash(edge.s, edge.s);
            db(hashNodes[edge.f], hashNodes[edge.s]);
            res += hashNodes[edge.f] == hashNodes[edge.s];
            subhash(edge.f, edge.f);
            subhash(edge.s, edge.s);
        }
        cout << res << '\n';
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
