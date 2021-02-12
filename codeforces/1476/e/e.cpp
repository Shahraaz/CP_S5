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
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<string, int>> patters(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> patters[i].first;
        patters[i].second = i;
    }
    sort(all(patters));
    vector<vector<int>> adj(n);
    vector<int> degree(n);
    for (size_t i = 0; i < m; i++)
    {
        string str;
        int mt;
        cin >> str >> mt;
        --mt;
        bool ok = false;
        for (size_t curr = 0; curr < (1 << k); curr++)
        {
            string str2 = str;
            for (size_t j = 0; j < k; j++)
            {
                if (curr & (1 << j))
                    str2[j] = '_';
            }
            auto it = lower_bound(all(patters), make_pair(str2, 0));
            if (it != patters.end() && it->first == str2)
            {
                if (it->second == mt)
                {
                    ok = true;
                    continue;
                }
                adj[mt].pb(it->second);
                degree[it->second]++;
            }
        }
        if (!ok)
        {
            cout << "NO\n";
            return;
        }
    }
    queue<int> Q;
    vector<int> order;
    for (size_t i = 0; i < n; i++)
        if (degree[i] == 0)
            Q.push(i);
    while (Q.size())
    {
        auto front = Q.front();
        Q.pop();
        order.pb(front);
        for (auto &x : adj[front])
        {
            degree[x]--;
            if (degree[x] == 0)
                Q.push(x);
        }
    }
    if (order.size() != n)
    {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (auto &x : order)
    {
        cout << x + 1 << ' ';
    }
    cout << '\n';
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
        solveCase();
    return 0;
}