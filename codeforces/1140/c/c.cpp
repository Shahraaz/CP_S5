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

// const long long one = 1e6, two = 3e5;

void solveCase()
{
    // db(one * one * two);
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> vecc(n);
    for (auto &x : vecc)
        cin >> x.second >> x.first;
    sort(all(vecc));
    ll res = 0, sum = 0;
    set<pair<int, int>> ss;
    for (int i = n - 1; i >= 0; i--)
    {
        if (ss.size() == k - 1)
        {
            res = max(res, (sum + vecc[i].second) * (vecc[i].first));
            if (k != 1)
            {
                auto mini = (ss.begin())->first;
                if (mini < vecc[i].second)
                {
                    ss.erase(ss.begin());
                    ss.insert({vecc[i].second, i});
                    sum += vecc[i].second;
                    sum -= mini;
                }
            }
        }
        else
        {
            res = max(res, (sum + vecc[i].second) * (vecc[i].first));
            ss.insert({vecc[i].second, i});
            sum += vecc[i].second;
        }
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