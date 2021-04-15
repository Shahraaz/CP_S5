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
const int NAX = 3e5 + 5, MOD = 998244353;

const int kmod = 998244353;

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

// const int _n = 2e5 + 10;
// vector<int> Fact(_n), Inv(_n);

// void pre()
// {
//     Fact[0] = 1;
//     for (int i = 1; i < _n; ++i)
//         Fact[i] = mul(Fact[i - 1], i);
//     Inv[_n - 1] = mod_inv(Fact[_n - 1]);
//     for (int i = _n - 2; i >= 0; --i)
//         Inv[i] = mul(Inv[i + 1], (1 + i));
// }

// int ncr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], mul(Inv[r], Inv[n - r]));
// }

// int npr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], Inv[n - r]);
// }

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    int total = 0;
    for (auto &x : grid)
    {
        cin >> x;
        total += count(all(x), 'o');
    }
    if (total <= 1)
    {
        cout << 0 << '\n';
        return;
    }
    vector<vector<int>> maxright(n, vector<int>(m));
    vector<vector<int>> maxdown(n, vector<int>(m));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (grid[i][j] == '*')
                continue;
            maxright[i][j] = maxdown[i][j] = 1;

            if (i + 1 < n && grid[i + 1][j] == 'o')
                maxdown[i][j] += maxdown[i + 1][j];

            if (j + 1 < m && grid[i][j + 1] == 'o')
                maxright[i][j] += maxright[i][j + 1];
        }
    }

    vector<int> pow2(NAX);
    pow2[0] = 1;
    for (size_t i = 1; i < NAX; i++)
        pow2[i] = mul(2, pow2[i - 1]);
    map<int, vector<int>> pre_compute_contrib;
    for (int x : {total, total - 1, total - 2})
    {
        pre_compute_contrib[x].resize(NAX);
        if (x <= 0)
            continue;
        pre_compute_contrib[x][0] = 0;
        pre_compute_contrib[x][1] = 0;
        for (int i = 2; i <= x; i++)
        {
            pre_compute_contrib[x][i] = mul(i / 2, pow2[x - i]);
            pre_compute_contrib[x][i] = add(pre_compute_contrib[x][i], pre_compute_contrib[x][i - 1]);
        }
    }

    vector<int> dx = {0, 0, 1, -1};
    vector<int> dy = {1, -1, 0, 0};
    int res = 0, inv_2 = mod_inv(2);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '*')
                continue;

            int toright = maxright[i][j];

            if (toright > 1)
            {
                int rem = total;
                if (j - 1 >= 0 && grid[i][j - 1] == 'o')
                    rem--;
                // if (i - 1 >= 0 && grid[i - 1][j] == 'o')
                //     rem--;

                if (rem - toright >= 0)
                    res = add(res, mul(toright / 2, pow2[rem - toright]));
                db(res, toright / 2, rem - toright);
                if (rem - 1 >= 0)
                    res = add(res, pre_compute_contrib[rem - 1][toright - 1]);
                db(res, rem - 1, toright - 1);
            }
            db(i, j, toright, res);
            int todown = maxdown[i][j];

            if (todown > 1)
            {
                int rem = total;
                if (i - 1 >= 0 && grid[i - 1][j] == 'o')
                    rem--;
                // if (j - 1 >= 0 && grid[i][j - 1] == 'o')
                //     rem--;

                if (rem - todown >= 0)
                    res = add(res, mul(todown / 2, pow2[rem - todown]));
                db(res, todown / 2, rem - todown);
                if (rem - 1 >= 0)
                    res = add(res, pre_compute_contrib[rem - 1][todown - 1]);
                db(res, rem - 1, todown - 1);
            }
            db(i, j, todown, res);
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