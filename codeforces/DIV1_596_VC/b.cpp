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

const int NAX_PRIME = 1e5 + 5;
bool is_composite[NAX_PRIME];
int spf[NAX_PRIME];
vector<int> primes;

void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    memset(spf, -1, sizeof spf);
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
            primes.push_back(i);
        if (spf[i] == -1)
            spf[i] = i;
        for (size_t j = 2 * i; j < n; j += i)
        {
            is_composite[j] = true;
            if (spf[j] == -1)
                spf[j] = i;
            // if (i % primes[j] == 0)
            //     break;
        }
    }
}

int mod_expo(int base, int idx)
{
    int ret = 1;
    while (idx)
    {
        if (idx & 1)
            ret = (ret * 1LL * base) % MOD;
        base = (base * 1LL * base) % MOD;
        idx /= 2;
    }
    return ret;
}

void solveCase()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    map<pair<ll, ll>, int> hash;
    seive();
    ll res = 0;
    for (auto &x : a)
    {
        cin >> x;
        int temp = x;
        pair<ll, ll> hh;
        pair<ll, ll> hh_inv;
        db(temp, spf[temp]);
        while (spf[temp] != -1)
        {
            auto cnt = 0;
            int p = spf[temp];
            while (temp % p == 0)
            {
                temp /= p;
                cnt++;
                if (cnt >= k)
                    cnt -= k;
            }
            db(p, cnt);
            if (cnt)
            {
                hh.first = hh.first * 101 + mod_expo(p, cnt);
                if (hh.first >= MOD)
                    hh.first -= MOD;
                hh.second = hh.second * 8087 + mod_expo(p, cnt);
                if (hh.second >= MOD)
                    hh.second -= MOD;

                hh_inv.first = hh_inv.first * 101 + mod_expo(p, k - cnt);
                if (hh_inv.first >= MOD)
                    hh_inv.first -= MOD;
                hh_inv.second = hh_inv.second * 8087 + mod_expo(p, k - cnt);
                if (hh_inv.second >= MOD)
                    hh_inv.second -= MOD;
            }
        }
        auto it = hash.find(hh_inv);
        if (it != hash.end())
            res += it->second;
        hash[hh]++;
        db(hh, hh_inv, '\n');
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