// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> minIdx(n + 1, MOD), maxIdx(n + 1, -MOD);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i]--;
        minIdx[a[i]] = min(minIdx[a[i]], i);
        maxIdx[a[i]] = max(maxIdx[a[i]], i);
    }
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    vector<int> dp(a.size());
    db(minIdx);
    db(maxIdx);
    for (int i = a.size() - 1; i >= 0; i--)
    {
        if (i + 1 >= a.size() || maxIdx[a[i]] > minIdx[a[i + 1]])
            dp[i] = 1;
        else
            dp[i] = dp[i + 1] + 1;
    }
    db(dp);
    cout << a.size() - *max_element(all(dp)) << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
