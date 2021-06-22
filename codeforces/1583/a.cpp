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
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    int min_idx = min_element(all(a)) - a.begin();
    int max_idx = max_element(all(a)) - a.begin();
    int res = MOD;
    res = min(res, max(min_idx, max_idx) + 1);
    res = min(res, max(n - min_idx - 1, n - max_idx - 1) + 1);

    res = min(res, (n - min_idx - 1 + max_idx + 2));
    res = min(res, (min_idx + n - max_idx - 1 + 2));
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