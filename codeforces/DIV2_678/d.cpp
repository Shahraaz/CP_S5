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
// ll dp[NAX];
ll a[NAX];
vector<pair<ll, int>> st;

bool dfs(int node, ll LIM)
{
    if (adj[node].empty())
    {
        if (a[node] > LIM)
            return false;
        ll now = a[node];
        while (st.size() && now < LIM)
        {
            auto b = st.back();
            auto diff = LIM - now;
            diff = min(diff, b.f);
            b.f -= diff;
            now += diff;
            st.back() = b;
            if (st.back().f == 0)
                st.pop_back();
        }
        return true;
    }
    if (a[node])
        st.pb({a[node], node});
    for (auto &x : adj[node])
        if (!dfs(x, LIM))
            return false;
    if (st.size() && st.back().s == node)
        return false;
    return true;
}

void solveCase()
{
    int n;
    cin >> n;
    for (size_t i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        adj[x].pb(i);
    }
    for (size_t i = 0; i < n; i++)
        cin >> a[i + 1];
    ll low = 0, high = MOD * 1LL * n;
    ll ans = high;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        auto ret = dfs(1, mid);
        st.clear();
        // db(mid, ret);
        if (ret)
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
#ifdef LOCAL
    for (size_t i = 0; i < 5; i++)
    {
        auto ret = dfs(1, i);
        db(i, ret);
    }
#endif
    cout << ans << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
