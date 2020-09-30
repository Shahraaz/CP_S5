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
    for (auto &x : a)
    {
        cin >> x;
    }
    vector<vector<int>> vecc(n + 1);
    for (size_t i = 1; i <= n; i++)
        vecc[i].pb(-1);
    for (size_t i = 0; i < n; i++)
        vecc[a[i]].pb(i);
    for (size_t i = 1; i <= n; i++)
        vecc[i].pb(n);
    vector<int> maxDiff(n + 1, -1);
    vector<int> res(n + 1, -1);
    for (int i = 1; i <= n; i++)
    {
        db(i, vecc[i]);
        if (vecc[i].size() == 2)
            continue;
        for (size_t j = 1; j < vecc[i].size(); j++)
            maxDiff[i] = max(maxDiff[i], vecc[i][j] - vecc[i][j - 1]);
        db(i, maxDiff[i]);
        if (res[maxDiff[i]] == -1 || res[maxDiff[i]] > i)
            res[maxDiff[i]] = i;
    }
    int prevMin = -1;
    db(res);
    for (size_t i = 1; i <= n; i++)
    {
        if (prevMin == -1 || (res[i] != -1 && res[i] < prevMin))
            prevMin = res[i];
        cout << prevMin << ' ';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
