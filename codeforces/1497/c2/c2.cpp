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
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; ++i)
    {
      
    }
    if (n == k)
    {
        for (int i = 0; i < n; ++i)
            cout << 1 << ' ';
        cout << '\n';
        return;
    }
    vector<int> out(k, 1);
    n -= k;
    if (n % 2 == 0)
    {
        out[0] += n / 2;
        out[1] += n / 2;
    }
    else
    {
        out[0] += n / 2;
        out[1] += n / 2;
        out[2] += 1;
    }
    for (auto &x : out)
    {
        cout << x << ' ';
    }
    cout << '\n';
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