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


#define int ll
struct Bit
{
    int size;
    vector<int> table;
    Bit(int size)
    {
        this->size = size;
        table.resize(size);
    }
    void update(int i, int delta)
    {
        while (i < size)
        {
            table[i] += delta;
            i = i | (1 + i);
        }
    }
    int sum(int i)
    {
        int ret = 0;
        while (i >= 0)
        {
            ret += table[i];
            i = (i & (i + 1)) - 1;
        }
        return ret;
    }
    int rangeSum(int i, int j)
    {
        if (i == 0)
            return sum(j);
        return sum(j) - sum(i - 1);
    }
    void print()
    {
#ifdef LOCAL
        for (int i = 0; i < size; i++)
            cout << rangeSum(i, i) << ' ';
        cout << '\n';
#else

#endif
    }
};

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> sources;
    int cnt = 0;
    Bit b(n);
    vector<pair<int, int>> sinks;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] >= 0)
        {
            sources.insert(i);
            b.update(i, a[i]);
            cnt++;
        }
        else
            sinks.pb({-a[i], i});
    }
    sort(all(sinks), [](const pair<int, int> &l, const pair<int, int> &r) -> bool
         {
             if (l.first == r.first)
                 return l.second > r.second;
             return l.first < r.first;
         });
    db(sinks);
    for (auto &c : sinks)
    {
        if (sources.empty())
            break;
        int cost = c.first;
        int idx = c.second;
        if (b.sum(idx) < cost)
            continue;
        while (true)
        {
            if (cost == 0)
            {
                cnt++;
                break;
            }
            auto it = sources.lower_bound(idx);
            assert(it != sources.begin());
            --it;
            int idxsrc = *it;
            int mini = min(a[idxsrc], cost);

            b.update(idxsrc, -mini);
            a[idxsrc] -= mini;
            cost -= mini;

            if (a[idxsrc] == 0)
                sources.erase(it);
        }
    }
    cout << cnt << '\n';
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