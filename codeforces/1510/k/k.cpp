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
    vector<int> p(2 * n);
    for (auto &x : p)
    {
        cin >> x;
        --x;
    }
    auto one = [&]() {
        for (size_t i = 0; i < p.size(); i += 2)
            swap(p[i], p[i + 1]);
    };
    auto two = [&]() {
        for (size_t i = 0; 2 * i < p.size(); i++)
            swap(p[i], p[i + n]);
    };
    auto ok = [&]() -> bool {
        for (size_t i = 0; i < p.size(); i++)
            if (i != p[i])
                return false;
        return true;
    };
    auto back = p;
    int res = MOD;
    if (ok())
        res = min(res, 0);
    for (int i = 0; i < 2000; i++)
    {
        if (i % 2 == 0)
            one();
        else
            two();
        if (ok())
        {
            res = min(res, i + 1);
            break;
        }
    }
    p = back;
    for (int i = 0; i < 2000; i++)
    {
        if (i % 2 == 1)
            one();
        else
            two();
        if (ok())
        {
            res = min(res, i + 1);
            break;
        }
    }
    if (res == MOD)
        res = -1;
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