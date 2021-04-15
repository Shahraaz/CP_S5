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
    int n, k1, k2;
    cin >> n >> k1 >> k2;
    int k = k1 + k2;
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, -1));
    vector<long long> a(n + 1);
    vector<long long> b(n + 1);
    for (size_t i = 0; i < n; i++)
        cin >> a[i];
    set<pair<int, int>> ss;
    for (size_t i = 0; i < n; i++)
    {
        cin >> b[i];
        b[i] = abs(b[i] - a[i]);
        ss.insert({b[i], i});
    }
    sort(all(b));
    while (k--)
    {
        auto maxi = *ss.rbegin();
        ss.erase(maxi);
        if (maxi.first)
            maxi.first--;
        else
            maxi.first++;
        ss.insert(maxi);
    }
    long long res = 0;
    for (auto &x : ss)
    {
        res += x.first * 1LL * x.first;
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}