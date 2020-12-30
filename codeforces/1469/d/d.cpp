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
    vector<int> a(n + 1);
    for (size_t i = 1; i <= n; i++)
        a[i] = i;
    vector<pair<int, int>> res;
    auto do_it = [&](int x, int y) {
        a[x] = (a[x] + a[y] - 1) / a[y];
        res.pb({x, y});
    };
    for (int i = n; i >= 3;)
    {
        int j = i;
        while (j >= 2)
        {
            int temp = (i + j - 1) / j;
            temp = (temp + j - 1) / j;
            db(i, j, temp);
            if (temp == 1)
                --j;
            else
                break;
        }
        db(i, j);
        for (int k = j + 2; k < i; k++)
            do_it(k, i);
        do_it(i, j + 1);
        do_it(i, j + 1);
        if (i <= j + 1)
            break;
        i = j + 1;
    }
    db(a);
    db(res);
    assert(res.size() <= n + 5);
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
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}