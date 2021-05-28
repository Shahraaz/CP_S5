#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 1e5 + 5, MOD = 1000000007;

vector<int> gra[NAX];
map<int, ll> po[NAX], ne[NAX];
int dp[NAX];
string str;
ll ans = 0;
int n;

void dfs(int par, int node)
{
    int lar = n;
    for (auto &c : gra[node])
    {
        if (c != par)
        {
            dfs(node, c);
            if (po[c].size() > po[lar].size())
                lar = c;
        }
    }
    swap(po[node], po[lar]);
    swap(ne[node], ne[lar]);
    swap(dp[node], dp[lar]);
    for (auto &c : gra[node])
        if (c != par && c != lar)
        {
            for (auto &j : po[c])
                ans += ne[node][-dp[c] - dp[node] - j.first] * 1LL * j.second;
            for (auto &j : ne[c])
                ans += po[node][-dp[c] - dp[node] - j.first] * 1LL * j.second;

            for (auto &j : po[c])
                po[node][j.first - dp[node] + dp[c]] += j.second;
            for (auto &j : ne[c])
                ne[node][j.first - dp[node] + dp[c]] += j.second;
        }
    if (node)
    {
        po[node][-dp[node]]++;
        ne[node][-dp[node]]++;

        if (str[node] == '(')
            dp[node]++;
        else
            dp[node]--;

        int at = node;
        while (po[at].size() && (*po[at].begin()).first + dp[at] < 0)
            po[at].erase(po[at].begin());
        while (ne[at].size() && (*(--ne[at].end())).first + dp[at] > 0)
            ne[at].erase(--ne[at].end());
        ans += po[at][-dp[at]];
        ans += ne[at][-dp[at]];
    }
}

void solveCase()
{
    cin >> n;
    ans = 0;
    for (size_t i = 0; i <= n; i++)
    {
        gra[i].clear();
        ne[i].clear();
        po[i].clear();
        dp[i] = 0;
    }
    for (size_t i = 0; i < n; i++)
    {
        int p;
        cin >> p;
        if (i)
            gra[p].pb(i);
    }
    cin >> str;
    str = '0' + str;
    dfs(0, 0);
    cout << ans << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}