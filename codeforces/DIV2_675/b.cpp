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
    vector<vector<int>> matt(n, vector<int>(m));
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            cin >> matt[i][j];
    vector<vector<int>> same;
    for (int i = 0; i < n; i++)
    {
        int rptri = n - i - 1;
        if (i <= rptri)
            for (int j = 0; j < m; j++)
            {
                int rptrj = m - j - 1;
                if (j > rptrj)
                    break;
                set<pair<int, int>> mySet;
                mySet.insert({i, j});
                mySet.insert({i, rptrj});
                mySet.insert({rptri, j});
                mySet.insert({rptri, rptrj});
                vector<int> vecc;
                db(i, j, mySet);
                for (auto &x : mySet)
                    vecc.pb(matt[x.f][x.s]);
                same.pb(vecc);
            }
    }
    ll res = 0;
    for (auto &x : same)
    {
        db(x);
        ll sum = accumulate(all(x), 0LL);
        ll Avg = sum / x.size();
        ll minRes = sum;

        for (auto avg : {Avg - 2, Avg - 1, Avg, Avg + 1, Avg + 2})
        {
            ll temp = 0;
            for (auto &y : x)
                temp += abs(y - avg);
            minRes = min(minRes, temp);
        }

        for (auto avg : x)
        {
            ll temp = 0;
            for (auto &y : x)
                temp += abs(y - avg);
            minRes = min(minRes, temp);
        }

        res += minRes;
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
