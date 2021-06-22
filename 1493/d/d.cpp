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

const int NAX_PRIME = 2e5 + 5;
bool is_composite[NAX_PRIME];
vector<int> primes;
vector<vector<pair<int, int>>> pf(NAX);

void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
        {
            primes.push_back(i);
            for (size_t j = i; j < n; j += i)
            {
                int j1 = j;
                int cnt = 0;
                while (j1 % i == 0)
                    j1 /= i, ++cnt;
                pf[j].pb({i, cnt});
            }
        }
        for (size_t j = 0; j < primes.size() && ((ll)i * primes[j] < n); j++)
        {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

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

vector<set<pair<int, int>>> ss(NAX);
int res = 1;
int n, q;

int get_cost(int p)
{
    int ret = 1;
    if (ss[p].size() == n)
        ret = power(p, ss[p].begin()->first);
    // db(p, ss[p].size(), n, ret);
    return ret;
}

void alter(int i, int pcnt, int p, int dx)
{
    int old = get_cost(p);
    res = mul(res, mod_inv(old));

    auto it = ss[p].find({pcnt, i});
    if (it != ss[p].end())
        ss[p].erase(it);
    ss[p].insert({pcnt + dx, i});
    int new_cost = get_cost(p);
    res = mul(res, new_cost);

    // db(ss[p]);
    // db(i, pcnt, p, dx, old, new_cost, res);
}

void solveCase()
{
    seive();
    cin >> n >> q;
    db(n, q);
    map<pair<int, int>, int> mppp;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        // db(x, pf[x]);
        for (auto &p : pf[x])
        {
            alter(i, 0, p.first, p.second);
            mppp[{i, p.first}] = p.second;
        }
    }
    for (size_t i = 0; i < q; i++)
    {
        int j, x;
        cin >> j >> x;
        --j;
        for (auto &p : pf[x])
        {
            alter(j, mppp[{j, p.first}], p.first, p.second);
            mppp[{j, p.first}] += p.second;
        }
#ifdef LOCAL
        for (size_t j = 0; j < NAX; j++)
            if (ss[j].size())
            {
                db(j, ss[j]);
            }

#endif
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