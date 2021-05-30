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
const int NAX = 1e7 + 5, MOD = 1000000007;

int ok[NAX];
vector<int> vecc;

int calc(int x)
{
    auto &ret = ok[x];
    if (ret != -1)
        return ret;
    ret = 0;
    for (auto &y : vecc)
        if (x >= y && calc(x - y))
            return ret = 1;
    return ret;
}

void solveCase()
{
    int x;
    cin >> x;
    if (x >= 1100 || ok[x])
        cout << "YES\n";
    else
        cout << "NO\n";
}

int32_t main()
{
    memset(ok, -1, sizeof ok);
    ll now = 11;
    while (now <= MOD)
    {
        vecc.pb(now);
        now = now * 10 + 1;
    }

    ok[0] = 1;
    for (size_t i = 11; i < NAX; i++)
    {
        if (calc(i) == 0)
        {
            db(i);
        }
    }
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