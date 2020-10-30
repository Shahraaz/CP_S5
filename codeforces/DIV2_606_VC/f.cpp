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
    map<int, int> mp;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        mp[x]++;
    }
    vector<vector<int>> vecc(n + 1);
    for (auto &x : mp)
        vecc[x.s].pb(x.f);
    vector<int> geq(n + 2);
    for (int i = n; i >= 0; i--)
        geq[i] = geq[i + 1] + vecc[i].size();
    int total = 0;
    int best = 0, best_a;
    for (int a = 1; a <= n; a++)
    {
        total += geq[a];
        int b = total / a;
        if (a <= b && best < a * b)
        {
            best = a * b;
            best_a = a;
        }
    }
    cout << best << '\n';
    int best_b = best / best_a;
    cout << best_a << ' ' << best_b << '\n';
    vector<vector<int>> res(best_a, vector<int>(best_b));
    int x = 0, y = 0;
    for (int i = n; i >= 0; i--)
        for (auto &val : vecc[i])
            for (size_t j = 0; j < min(i, best_a); j++)
            {
                if (res[x][y] > 0)
                {
                    ++x;
                    if (x >= best_a)
                        x -= best_a;
                }
                if (res[x][y] == 0)
                    res[x][y] = val;
                ++x;
                if (x >= best_a)
                    x -= best_a;
                ++y;
                if (y >= best_b)
                    y -= best_b;
            }
    for (auto &x : res)
    {
        for (auto &y : x)
            cout << y << ' ';
        cout << '\n';
    }
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
