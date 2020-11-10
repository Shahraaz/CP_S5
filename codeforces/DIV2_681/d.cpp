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
    vector<int> sum(n);
    for (auto &x : sum)
        cin >> x;
    vector<int> decreasing(n), increasing(n);
    decreasing[0] = sum[0];
    for (size_t i = 1; i < n; i++)
    {
        if (sum[i] < increasing[i - 1])
        {
            cout << "No\n";
            return;
        }
        decreasing[i] = min(decreasing[i - 1], sum[i] - increasing[i - 1]);
        increasing[i] = sum[i] - decreasing[i];
        db(i, increasing[i], decreasing[i], sum[i]);
        assert(increasing[i - 1] <= increasing[i]);
        assert(decreasing[i - 1] >= decreasing[i]);
    }
    cout << "Yes\n";
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
