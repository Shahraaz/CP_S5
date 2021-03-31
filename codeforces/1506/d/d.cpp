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

#define int ll

void solveCase()
{
    int n;
    cin >> n;
    map<int, int> cnt;
    int maxi = 0;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
        maxi = max(maxi, cnt[x]);
    }
    if (maxi >= (n - maxi))
    {
        cout << maxi - (n - maxi) << '\n';
    }
    else
        cout << (n&1) << '\n';
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