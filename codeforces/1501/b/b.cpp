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
    vector<int> prefsums(2 * n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        int rptr = i;
        int lptr = max(0, i - x + 1);
        prefsums[lptr]++;
        prefsums[rptr + 1]--;
    }
    for (size_t i = 0; i < n; i++)
    {
        if (i > 0)
            prefsums[i] += prefsums[i - 1];
        cout << (prefsums[i] > 0) << ' ';
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