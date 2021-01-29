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
    vector<int> p(n + 1), isLeft(n + 1);
    vector<int> left, right;
    for (size_t i = 1; i <= n; i++)
    {
        p[i] = i;
        int l = (i - 1);
        int r = (n - i);
        if (l <= r)
        {
            isLeft[i] = 1;
            left.pb(i);
        }
        else
            right.pb(i);
    }
    db(p);
    db(left, right);
    ll res = 0;
    vector<pair<int, int>> ret;
    for (auto &i : left)
    {
        int j = n;
        db(i, j, p[i], p[j]);
        if (i != j)
        {
            res += (i - j) * 1LL * (i - j);
            assert(p[i] == i);
            swap(p[i], p[j]);
            ret.pb({i, j});
        }
        db(p);
    }
    for (auto &i : right)
    {
        int j = 1;
        db(i, j, p[i], p[j]);
        if (i != j)
        {
            if (p[i] != i)
                continue;
            res += (i - j) * 1LL * (i - j);
            assert(p[i] == i);
            swap(p[i], p[j]);
            ret.pb({i, j});
        }
        db(p);
    }
    cout << res << '\n';
    for (size_t i = 1; i <= n; i++)
        cout << p[i] << ' ';
    cout << '\n';
    cout << ret.size() << '\n';
    reverse(all(ret));
    for (auto &x : ret)
        cout << x.first << ' ' << x.second << '\n';
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