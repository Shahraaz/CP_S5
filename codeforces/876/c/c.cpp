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
    ll n;
    cin >> n;
    vector<int> res;

    for (int i = 0; i < 100; i++)
    {
        if (n >= i)
        {
            int n1 = n - i;
            int sum = 0;
            {
                int n2 = n1;
                while (n2)
                {
                    sum += n2 % 10;
                    n2 /= 10;
                }
            }
            if (i == sum)
            {
                res.pb(n1);
            }
        }
    }
    cout << res.size() << '\n';
    sort(all(res));
    for (auto &x : res)
        cout << x << ' ';
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