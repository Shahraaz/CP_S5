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
    int a, b;
    cin >> a >> b;
    int res = MOD;
    auto brute_forces = [&]() -> int {
        if (b == 1)
            return MOD;
        int ret = 0;
        int a1 = a;
        while (a1)
        {
            a1 /= b;
            ret++;
        }
        return ret;
    };
    for (int i = 0; i < 32; i++)
    {
        res = min(res, i + brute_forces());
        ++b;
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
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}