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

void solveCase()
{
    string str;
    cin >> str;
    ll x, y;
    cin >> x >> y;
    int n = str.size();
    if (x > y)
    {
        swap(x, y);
        for (auto &c : str)
            c = (c == '?' ? '?' : '0' ^ '1' ^ c);
    }
    db(x, y, str);
    vector<vector<int>> prefsum(3, vector<int>(n));
    for (size_t i = 0; i < n; i++)
    {
        if (i > 0)
            prefsum[0][i] = prefsum[0][i - 1], prefsum[1][i] = prefsum[1][i - 1], prefsum[2][i] = prefsum[2][i - 1];
        if (str[i] != '?')
            prefsum[str[i] - '0'][i]++;
        else
            prefsum[2][i]++;
    }
    ll res = LLONG_MAX, one = 0, zero = 0;
    auto get_cnt = [&](int id, int x, int y) -> int {
        if (y < x)
            return 0;
        if (x == 0)
            return prefsum[id][y];
        return prefsum[id][y] - prefsum[id][x - 1];
    };
    auto calc = [&](ll now, ll l0, ll l1, ll r0, ll r1) -> ll {
        if (now == 0)
            return l1 * y + r1 * x;
        return l0 * x + r0 * y;
    };
    auto get_q0 = [&](int x, int y) -> int {
        return get_cnt(0, x, y) + get_cnt(2, x, y);
    };
    auto get_q1 = [&](int x, int y) -> int {
        return get_cnt(1, x, y) + get_cnt(2, x, y);
    };
    vector<int> qmarks;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '?')
        {
            qmarks.pb(i);
            // zero += calc(0, get_q0(0, i - 1), get_cnt(1, 0, i - 1), get_q0(i + 1, n - 1), get_cnt(1, i + 1, n - 1));
            one += calc(1, get_cnt(0, 0, i - 1), get_q1(0, i - 1), get_cnt(0, i + 1, n - 1), get_q1(i + 1, n - 1));
        }
        else if (str[i] == '0')
        {
            // zero += calc(0, get_cnt(0, 0, i - 1) + get_cnt(2, 0, i - 1), get_cnt(1, 0, i - 1), get_cnt(0, i + 1, n - 1) + get_cnt(2, i + 1, n - 1), get_cnt(1, i + 1, n - 1));
            one += calc(0, get_cnt(0, 0, i - 1), get_q1(0, i - 1), get_cnt(0, i + 1, n - 1), get_q1(i + 1, n - 1));
        }
        else
        {
            // zero += calc(1, get_cnt(0, 0, i - 1) + get_cnt(2, 0, i - 1), get_cnt(1, 0, i - 1), get_cnt(0, i + 1, n - 1) + get_cnt(2, i + 1, n - 1), get_cnt(1, i + 1, n - 1));
            one += calc(1, get_cnt(0, 0, i - 1), get_q1(0, i - 1), get_cnt(0, i + 1, n - 1), get_q1(i + 1, n - 1));
        }
    }
    db(one, zero);
    one /= 2;
    res = one;
    for (size_t i = 0; i < qmarks.size(); i++)
    {
        int id = qmarks[i];
        one -= calc(1, get_cnt(0, 0, id - 1) + get_cnt(2, 0, id - 1), get_cnt(1, 0, id - 1), get_cnt(0, id + 1, n - 1), get_cnt(1, id + 1, n - 1) + get_cnt(2, id + 1, n - 1));
        one += calc(0, get_cnt(0, 0, id - 1) + get_cnt(2, 0, id - 1), get_cnt(1, 0, id - 1), get_cnt(0, id + 1, n - 1), get_cnt(1, id + 1, n - 1) + get_cnt(2, id + 1, n - 1));
        db(i, id, one);
        res = min(res, one);
    }
    // assert(one == zero);
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