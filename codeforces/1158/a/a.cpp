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
    int n, m;
    cin >> n >> m;
    vector<int> b(n), g(m);
    for (auto &x : b)
        cin >> x;
    for (auto &x : g)
        cin >> x;
    sort(all(b));
    sort(all(g));
    if (b[n - 1] > g[0])
    {
        cout << "-1\n";
        return;
    }
    ll res = 0;
    int rptr_g = m - 1;
    for (int i = n - 1; i >= 0; i--)
    {
        int cnt = 0;
        db(i, b[i], rptr_g, g[rptr_g]);
        while (rptr_g >= 0 && b[i] <= g[rptr_g])
        {
            if (cnt + 1 == m)
            {
                if (g[rptr_g] != b[i])
                    break;
            }
            cnt++;
            res += g[rptr_g];
            rptr_g--;
            if (rptr_g >= 0)
            {
                db(i, b[i], rptr_g, g[rptr_g]);
            }
        }
        res += (m - cnt) * 1LL * b[i];
        db(i, cnt, res);
    }
    cout << res << '\n';
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