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
    int n;
    cin >> n;
    vector<ll> v(n), d(n), p(n), vis(n);
    set<int> indices;
    for (size_t i = 0; i < n; i++)
    {
        indices.insert(i);
        cin >> v[i] >> d[i] >> p[i];
    }
    vector<int> res;
    for (size_t i = 0; i < n; i++)
    {
        db(i, v[i], d[i], p[i]);
        if (vis[i])
            continue;
        res.pb(i);
        int v_i = v[i];
        queue<int> cry_babies;
        for (size_t j = i + 1; v_i && j < n; j++)
        {
            if (vis[j])
                continue;
            p[j] -= v_i;
            --v_i;
            if (p[j] < 0)
            {
                vis[j] = 1;
                cry_babies.push(j);
            }
        }
        while (cry_babies.size())
        {
            auto top = cry_babies.front();
            db(top);
            cry_babies.pop();
            for (size_t j = top + 1; j < n; j++)
            {
                if (vis[j])
                    continue;
                p[j] -= d[top];
                if (p[j] < 0)
                {
                    vis[j] = 1;
                    cry_babies.push(j);
                }
            }
        }
    }
    cout << res.size() << '\n';
    for (auto &x : res)
        cout << x + 1 << ' ';
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