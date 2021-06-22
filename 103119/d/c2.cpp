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
    int n = 10;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
    {
        x = rand() % 30;
        cin >> x;
    }
    db(n, a);
    int globres = 0;
    vector<int> x, y;
    for (size_t i = 0; i < (1 << n); i++)
    {
        vector<int> one, two;
        for (size_t j = 0; j < n; j++)
        {
            if ((i >> j) & 1)
                one.pb(a[j]);
            else
                two.pb(a[j]);
        }
        int res = MOD;
        for (size_t i = 0; i < one.size(); i++)
            for (size_t j = i + 1; j < one.size(); j++)
                res = min(res, one[i] ^ one[j]);
        for (size_t i = 0; i < two.size(); i++)
            for (size_t j = i + 1; j < two.size(); j++)
                res = min(res, two[i] ^ two[j]);
        if (globres < res)
        {
            globres = res;
            x = one, y = two;
        }
    }
    cout << globres << '\n';
    // db(x, y);
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