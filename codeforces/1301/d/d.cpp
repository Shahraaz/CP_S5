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
    if (k > (4 * n * m - 2 * n - 2 * m))
    {
        cout << "NO\n";
        return;
    }
    vector<pair<int, string>> res;
    for (size_t i = 0; i < n; i++)
    {
        string moveright = "R";
        if (i != 0)
            moveright = "RUD";
        int j = k / moveright.size();
        db(i, j, moveright, k);
        if (j >= m - 1)
        {
            k -= moveright.size() * (m - 1);
            if (m > 1)
                res.pb({m - 1, moveright});
        }
        else
        {
            k -= moveright.size() * j;
            if (j > 0)
                res.pb({j, moveright});
            if (k)
                res.pb({1, moveright.substr(0, k)});
            k = 0;
        }
        if (k == 0)
            break;

        string moveleft = "L";
        j = k / moveleft.size();
        db(i, j, moveleft, k);
        if (j >= m - 1)
        {
            k -= moveleft.size() * (m - 1);
            if (m > 1)
                res.pb({m - 1, moveleft});
        }
        else
        {
            k -= moveleft.size() * j;
            if (j > 0)
                res.pb({j, moveleft});
            if (k)
                res.pb({1, moveright.substr(0, k)});
            k = 0;
        }
        if (k == 0)
            break;

        if (i + 1 < n)
        {
            --k;
            res.pb({1, "D"});
        }
    }

    if (k)
        res.pb({k, "U"});
    cout << "YES\n";
    cout << res.size() << '\n';
    for (auto &x : res)
    {
        cout << x.first << ' ' << x.second << '\n';
    }
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