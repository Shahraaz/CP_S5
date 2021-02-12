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
    int m;
    cin >> m;
    vector<int> vecc(m);
    for (auto &x : vecc)
        cin >> x;
    sort(all(vecc));
    int res = INT_MAX;
    int lim = (m + 1) / 2 - 1;
    for (size_t i = 0; i < m; i++)
    {
        int j = i + lim;
        if (j >= m)
            break;
        res = min(res, vecc[j] - (i > 0 ? vecc[i - 1] : 0));
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