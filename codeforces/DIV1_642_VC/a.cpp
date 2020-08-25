// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

int cnt[NAX];
int cnt2[NAX];
vector<int> divisors[NAX];
vector<int> idk[NAX];
int isPrime[NAX];

void Solution::solveCase()
{
    for (size_t i = 2; i < NAX; i += 1)
        isPrime[i] = true;
    for (size_t i = 2; i < NAX; i++)
    {
        if (isPrime[i])
            for (size_t j = i; j < NAX; j += i)
            {
                isPrime[j] = j == i;
                divisors[j].pb(i);
            }
    }
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto &x : a)
    {
        cin >> x;
        for (auto &y : divisors[x])
        {
            // db(y, divisors[x]);
            int x1 = x;
            int cnt = 0;
            while (x1 % y == 0)
            {
                x1 /= y;
                cnt++;
            }
            idk[y].pb(cnt);
        }
    }
    function<ll(ll, ll)> power = [&](ll a, ll idx) -> ll {
        if (idx == 0)
            return 1;
        auto temp = power(a, idx / 2);
        temp = (temp * temp);
        if (idx & 1)
            temp = (temp * a);
        return temp;
    };
    ll res = 1;
    for (size_t i = 1; i < NAX; i++)
        if (idk[i].size() == n || (idk[i].size() + 1) == n)
        {
            int a = 0, b = 0;
            sort(all(idk[i]));
            db(i, idk[i]);
            if ((idk[i].size() + 1) == n)
                a = 0, b = idk[i].front();
            else
                a = idk[i][1], b = 0;
            res = res * power(i, a + b);
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
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
