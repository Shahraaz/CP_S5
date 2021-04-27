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
const int NAX = 2e5 + 5, MOD = 998244353;

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

int solve(deque<int> a, int k)
{
    db(a, k);
    if (a.empty())
        return 1;

    if (*max_element(all(a)) == -1)
        return mul(k, power(k - 1, a.size() - 1));

    int ans = 1;
    while (a.front() == -1)
    {
        ans = mul(ans, k - 1);
        a.pop_front();
    }
    while (a.back() == -1)
    {
        ans = mul(ans, k - 1);
        a.pop_back();
    }

    int prev = a.front();

    int pcnt = 1, npcnt = k - 1;
    int pways = 1, nways = 0;

    for (size_t i = 1; i < a.size(); i++)
    {
        db(i, ans, a[i], prev, pcnt, npcnt, pways, nways);
        if (a[i] == -1)
        {
            int new_pways = mul(nways, npcnt);
            int new_npways = mul(pways, pcnt);
            new_npways = add(new_npways, mul(npcnt - 1, nways));

            pways = new_pways;
            nways = new_npways;
        }
        else
        {
            if (a[i] == prev)
                ans = mul(ans, mul(npcnt, nways));
            else
                ans = mul(ans, add(pways, mul(npcnt - 1, nways)));

            prev = a[i];

            pcnt = 1, npcnt = k - 1;
            pways = 1, nways = 0;
        }
    }
    db(a, ans);
    return ans;
}

void solveCase()
{
    int n, k;
    cin >> n >> k;
    vector<deque<int>> vecc(2);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        vecc[i & 1].pb(x);
    }
    cout << mul(solve(vecc[0], k), solve(vecc[1], k)) << '\n';
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