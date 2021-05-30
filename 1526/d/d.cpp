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
    string str;
    cin >> str;
    vector<char> vecc;
    map<int, int> mp;
    for (auto &x : str)
    {
        mp[x]++;
        if (count(all(vecc), x))
            continue;
        vecc.pb(x);
    }

    int n = str.size();

    sort(all(vecc));
    ll res_cost = -1;
    string res;
    do
    {
        string now;
        for (auto &x : vecc)
            for (size_t i = 0; i < mp[x]; i++)
                now += x;

        auto cost = [&](string now) -> ll
        {
            map<char, deque<int>> poses;
            for (size_t i = 0; i < n; i++)
                poses[str[i]].pb(i);
            Bit b(n);
            for (size_t i = 0; i < n; i++)
                b.update(i, 1);
            ll res = 0;
            for (size_t i = 0; i < n; i++)
            {
                auto idx = poses[now[i]].front();
                db(i, now[i], idx, res);
                poses[now[i]].pop_front();
                b.update(idx, -1);
                res += b.sum(idx);
            }
            return res;
        };
        ll cost_now = cost(now);
        db(now, cost_now);
        if (cost_now > res_cost)
        {
            res_cost = cost_now;
            res = now;
        }
    } while (next_permutation(all(vecc)));
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
        solveCase();
    return 0;
}