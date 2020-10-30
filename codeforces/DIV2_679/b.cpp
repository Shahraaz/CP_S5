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
    int n, m;
    cin >> n >> m;
    vector<deque<int>> rows(n);
    for (auto &x : rows)
    {
        x.resize(m);
        for (auto &y : x)
            cin >> y;
    }
    vector<deque<int>> cols(m);
    for (auto &x : cols)
    {
        x.resize(n);
        for (auto &y : x)
            cin >> y;
    }
    if (m == 1)
    {
        for (auto &x : cols)
            for (auto &y : x)
                cout << y << '\n';
        return;
    }
    if (n == 1)
    {
        for (auto &x : rows)
            for (auto &y : x)
                cout << y << '\n';
        cout << '\n';
        return;
    }
    // vector<int> cnt(n * m);
    map<int, int> cnt;
    for (size_t i = 0; i < cols.size(); i++)
        cnt[cols[i][0]] = i;
    for (auto &x : rows)
        for (auto &y : x)
            if (cnt.find(y) != cnt.end())
            {
                map<int, int> mapper;
                for (size_t i = 0; i < x.size(); i++)
                    mapper[i] = cnt[x[i]];
                for (size_t i = 0; i < n; i++)
                {
                    for (size_t j = 0; j < m; j++)
                        cout << cols[mapper[j]][i] << ' ';
                    cout << '\n';
                }
                return;
            }
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
