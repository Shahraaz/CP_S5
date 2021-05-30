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

int64_t solveCase(int n, const vector<pair<int, int>> &a)
{
    map<int, vector<pair<int, int>>> cnt;

    vector<pair<int, int>> vecc;
    for (size_t i = 0; i < n; i++)
        vecc.pb({a[i].first, i});

    sort(all(vecc));
    for (size_t i = 0; i + 1 < n; i++)
        cnt[abs(vecc[n - 1].first - vecc[i].first)].pb({vecc[i].second, vecc[n - 1].second});
    ;
    for (size_t i = 1; i < n; i++)
        cnt[abs(vecc[0].first - vecc[i].first)].pb({vecc[0].second, vecc[i].second});

    vecc.clear();
    for (size_t i = 0; i < n; i++)
        vecc.pb({a[i].second, i});

    sort(all(vecc));
    for (size_t i = 0; i + 1 < n; i++)
        cnt[abs(vecc[n - 1].first - vecc[i].first)].pb({vecc[i].second, vecc[n - 1].second});
    for (size_t i = 1; i < n; i++)
        cnt[abs(vecc[0].first - vecc[i].first)].pb({vecc[0].second, vecc[i].second});

    set<pair<int, int>> ss;
    bool one = false;

    db(cnt);

    while (true)
    {
        auto it = --cnt.end();
        for (auto &x : it->second)
        {
            if (ss.count(x))
                continue;
            ss.insert(x);
            if (one)
            {
                // cout << it->first << '\n';
                return it->first;
            }
            one = true;
        }
        cnt.erase(it);
    }
    return -1;
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    // failed to analyze input format
    // TODO: edit here
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i].first >> a[i].second;
    }
    auto ans = solveCase(n, a);
    cout << ans << endl;
    return 0;
}