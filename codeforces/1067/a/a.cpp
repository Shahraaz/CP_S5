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
const int NAX = 2e5 + 5, MOD = 998244353;

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (size_t i = 0; i < n; i++)
        cin >> a[i];
    vector<ll> now(201), nextt(201), after_next(201);

    if (a[0] == -1)
        fill(now.begin() + 1, now.end(), 1);
    else
        now[a[0]] = 1;

    for (size_t i = 0; i + 1 < n; i++)
    {
        int low = 1, high = 200;
        if (a[i] != -1)
            low = high = a[i];
        for (size_t j = low; j <= high; j++)
        {
            // if(now[i][j] == 0)
            //     continue;
            if (a[i + 1] == -1)
            {
                after_next[1]++;
                after_next[j + 1]--;
            }
        }
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