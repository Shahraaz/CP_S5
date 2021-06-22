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
    int n = 20;
    cin >> n;
    vector<int> o;
    int ecnt = 0;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x & 1)
            o.pb(x);
        else
            ecnt++;
    }

    int res = ecnt * (ecnt - 1) / 2 + ecnt * o.size();
    for (size_t i = 0; i < o.size(); i++)
    {
        for (size_t j = i + 1; j < o.size(); j++)
        {
            if (__gcd(o[i], o[j]) > 1)
                res++;
        }
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