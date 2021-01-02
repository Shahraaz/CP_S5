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
vector<int> vecc[NAX];
int cnt[NAX], CNT[NAX];
vector<pair<int, int>> cnt_small[NAX];

void solveCase()
{
    int n, sz;
    // cin >> n;
    vector<int> ranges;
    n = sqrt(NAX);
    sz = NAX / n;
    int ctrr = 0;
    for (size_t i = 0; i < n; i++)
    {
        // cin >> sz;
        vecc[i].resize(sz);
        for (auto &y : vecc[i])
        {
            y = ctrr++;
            // cin >> y;
            ranges.pb(y);
        }
    }
    const int LIM = 400, M = ranges.size();
    for (size_t i = 0; i < M; i++)
    {
        cnt[i] = 0;
        cnt_small[i].clear();
        CNT[i] = 0;
    }
    sort(all(ranges));
    for (size_t i = 0; i < n; i++)
        for (auto &y : vecc[i])
        {
            y = lower_bound(all(ranges), y) - ranges.begin();
            CNT[y]++;
        }
    ranges.clear();
    for (size_t i = 0; i < n; i++)
        if (vecc[i].size() > LIM)
        {
            for (auto &x : vecc[i])
                cnt[x]++;
            for (size_t j = 0; j < n; j++)
                if (i != j)
                {
                    int res = 0;
                    for (auto &x : vecc[j])
                        res += cnt[x];
                    if (res >= 2)
                    {
                        cout << i + 1 << ' ' << j + 1 << '\n';
                        return;
                    }
                }
            for (auto &x : vecc[i])
                cnt[x]--;
        }
    for (size_t i = 0; i < n; i++)
    {
        if (vecc[i].size() <= LIM)
        {
            for (size_t j = 0; j < vecc[i].size(); j++)
            {
                for (size_t k = j + 1; k < vecc[i].size(); k++)
                {
                    int x = vecc[i][j], y = vecc[i][k];
                    if (x > y)
                        swap(x, y);
                    // if (CNT[x] > 1 && CNT[y] > 1)
                    cnt_small[x].pb({y, i});
                }
            }
        }
        vecc[i].clear();
    }
    for (size_t i = 0; i < M; i++)
    {
        auto &x = cnt_small[i];
        // sort(all(x));
        for (size_t i = 0; i < x.size(); i++)
        {
            if (cnt[x[i].first] != 0)
            {
                cout << x[i].second + 1 << ' ';
                cout << cnt[x[i].first] << '\n';
                return;
            }
            cnt[x[i].first] = x[i].second + 1;
        }
        for (size_t i = 0; i < x.size(); i++)
            cnt[x[i].first] = 0;
    }
    cout << -1 << '\n';
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
    ;
    0;
}