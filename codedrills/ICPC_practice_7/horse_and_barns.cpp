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

const int kmod = 1000000007;

int mul(int a, int b, int mod = kmod)
{
    return (long long)a * b % mod;
}

int add(int a, int b, int mod = kmod)
{
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

int sub(int a, int b, int mod = kmod)
{
    a -= b;
    if (a < 0)
        a += mod;
    return a;
}

int power(int base, int index, int mod = kmod)
{
    if (index == 0)
        return 1;
    int temp = power(base, index / 2, mod);
    temp = mul(temp, temp, mod);
    if (index & 1)
        temp = mul(temp, base, mod);
    return temp;
}

int mod_inv(int x, int mod = kmod)
{
    return power(x, mod - 2, mod);
}

const int _n = 1e6 + 10;
vector<int> Fact(_n), Inv(_n);

void pre()
{
    Fact[0] = 1;
    for (int i = 1; i < _n; ++i)
        Fact[i] = mul(Fact[i - 1], i);
    Inv[_n - 1] = mod_inv(Fact[_n - 1]);
    for (int i = _n - 2; i >= 0; --i)
        Inv[i] = mul(Inv[i + 1], (1 + i));
}

int ncr(int n, int r)
{
    if (n < 0 || r < 0 || n - r < 0)
        return 0;
    return mul(Fact[n], mul(Inv[r], Inv[n - r]));
}

int npr(int n, int r)
{
    if (n < 0 || r < 0 || n - r < 0)
        return 0;
    return mul(Fact[n], Inv[n - r]);
}

void solveCase()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    for (auto &x : grid)
        cin >> x;
    vector<vector<int>> dist(n, vector<int>(m, MOD));
    queue<pair<int, int>> Q;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (grid[i][j] == 'X')
            {
                Q.push({i, j});
                dist[i][j] = 0;
            }
    vector<pair<int, int>> dirs;
    for (int i = -3; i < 4; i++)
        for (int j = -3; j < 4; j++)
            if (i != 0 && j != 0)
                if (abs(i) + abs(j) == 3)
                    dirs.pb({i, j});
    assert(dirs.size() == 8);
    // db(dirs);
    auto isvalid = [&](int i, int j) -> bool {
        return i >= 0 && i < n && j >= 0 && j < m;
    };
    map<int, int> cnt;
    while (Q.size())
    {
        auto top = Q.front();
        Q.pop();
        cnt[dist[top.first][top.second]]++;
        for (auto &d : dirs)
        {
            int x = top.first + d.first;
            int y = top.second + d.second;
            if (isvalid(x, y) && dist[x][y] == MOD)
            {
                dist[x][y] = dist[top.first][top.second] + 1;
                Q.push({x, y});
            }
        }
    }
    int res = 0;
    int less = 0;
    for (auto &d : cnt)
    {
        db(d);
        int now = d.second, temp = 0;
        for (int j = 1; j <= now; j++)
            temp = add(temp, mul(ncr(now, j), ncr(less, k - j)));
        res = add(res, mul(temp, d.first));
        less += now;
    }
    res = mul(res, mod_inv(ncr(n * m, k)));
    cout << res << '\n';
}

int32_t main()
{
    pre();
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