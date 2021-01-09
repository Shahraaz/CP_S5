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

void solveCase()
{
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<vector<int>> i_len_ti(k + 2, vector<int>(n));
    vector<int> cumm_ways(n, 0);
    i_len_ti[0] = vector<int>(n, 1);
    for (size_t ti = 0; ti <= k; ti++)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (i > 0)
                i_len_ti[ti + 1][i] = add(i_len_ti[ti + 1][i], i_len_ti[ti][i - 1]);
            if (i + 1 < n)
                i_len_ti[ti + 1][i] = add(i_len_ti[ti + 1][i], i_len_ti[ti][i + 1]);
        }
        db(ti, i_len_ti[ti]);
    }
    for (size_t i = 0; i < n; i++)
    {
        for (size_t idx = 0; idx <= k; idx++)
        {
            /*
                no of ways that i is at index i in resultant array
                to left len  = idx
                len to right = k - idx
            */
            cumm_ways[i] = add(cumm_ways[i], mul(i_len_ti[idx][i], i_len_ti[k - idx][i]));
        }
    }
    db(a);
    db(cumm_ways);
    int res = 0;
    for (size_t i = 0; i < n; i++)
        res = add(res, (a[i] * 1LL * cumm_ways[i]) % MOD);
    db(res);
    for (size_t i = 0; i < q; i++)
    {
        int idx, nval;
        cin >> idx >> nval;
        --idx;
        res = sub(res, (a[idx] * 1LL * cumm_ways[idx]) % MOD);
        a[idx] = nval;
        res = add(res, (a[idx] * 1LL * cumm_ways[idx]) % MOD);
        db(i, idx, nval);
        db(a);
        db(cumm_ways);
        cout << res << '\n';
    }
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