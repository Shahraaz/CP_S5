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
const int NAX = 3e5 + 5, MOD = 1000000007;

const int LIM = 3e5 + 5, LOG = 19;
int lvl[LIM];
int a[LIM];
int c[LIM];
int par[LOG][LIM];

void solveCase()
{
    int q;
    cin >> q >> a[0] >> c[0];
    for (size_t i = 1; i <= q; i++)
    {
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            int p;
            cin >> p >> a[i] >> c[i];
            par[0][i] = p;
            for (size_t j = 1; j < LOG; j++)
                par[j][i] = par[j - 1][par[j - 1][i]];
        }
        else
        {
            int v, w;
            cin >> v >> w;
            ll cost = 0, take = 0;
            while (w)
            {
                int u = v;
                for (int i = LOG - 1; i >= 0; i--)
                    if (a[par[i][u]])
                        u = par[i][u];
                // db(u,a[u],c[u],w,cost);
                if (a[u] == 0)
                    break;
                ll mini = min(w, a[u]);
                take += mini;
                a[u] -= mini;
                w -= mini;
                cost += mini * c[u];
            }
            cout << take << ' ' << cost << endl;
        }
    }
}

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}