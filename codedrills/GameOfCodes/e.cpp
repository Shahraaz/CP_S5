#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
const int NAX = 2e3 + 5, MOD = 1000000007;

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

int n;
vector<pair<char, int>> orders;
vector<vector<int>> invmapper;
Bit meow(2);

int dp[NAX][NAX];

int solve(int posB, int posD)
{
    if (posB == n && posD == n)
        return 0;
    auto &ret = dp[posB][posD];
    if (ret >= 0)
        return ret;
    ret = MOD;
    if (posB != n)
    {
        int idx = invmapper[0][posB];
        meow.update(idx, -1);
        ret = min(ret, meow.rangeSum(0, idx) + solve(posB + 1, posD));
        meow.update(idx, 1);
    }
    if (posD != n)
    {
        int idx = invmapper[1][posD];
        meow.update(idx, -1);
        ret = min(ret, meow.rangeSum(0, idx) + solve(posB, posD + 1));
        meow.update(idx, 1);
    }
    db(posB, posD, ret);
    return ret;
}

void solveCase()
{
    memset(dp, -1, sizeof dp);
    cin >> n;
    orders.resize(n * 2);
    invmapper.resize(2, vector<int>(n));
    meow = Bit(2 * n);
    for (size_t i = 0; i < 2 * n; i++)
    {
        meow.update(i, 1);
        cin >> orders[i].first >> orders[i].second;
        orders[i].second--;
        if (orders[i].first == 'B')
            invmapper[0][orders[i].second] = i;
        else
            invmapper[1][orders[i].second] = i;
    }
    db(invmapper[0]);
    db(invmapper[1]);
    cout << solve(0, 0) << '\n';
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