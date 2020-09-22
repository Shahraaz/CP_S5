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

void solve(int n)
{
    // db(n);
    vector<int> divisors;
    for (size_t i = 2; i <= n; i++)
        if (n % i == 0)
            divisors.pb(i);
    pair<int, vector<vector<int>>> res;
    auto check = [&]() -> int {
        int ret = 0;
        for (size_t i = 0; i < divisors.size(); i++)
            if (__gcd(divisors[i], divisors[(1 + i) % divisors.size()]) == 1)
                ret++;
        return ret;
    };
    res.f = MOD;
    do
    {
        int curr = check();
        if (curr == res.f)
            res.s.pb(divisors);
        else if (curr < res.f)
        {
            res.f = curr;
            res.s.clear();
            res.s.pb(divisors);
        }
    } while (next_permutation(all(divisors)));
    db(res.f, n, divisors.size());
    if (res.f == 0)
    {
    }
    else if (res.f == 1)
    {
        if (divisors.size() == 3)
        {
            db(divisors);
        }
        else
        {
            db(divisors);
            exit(1);
        }
    }
    else
    {
        db(divisors);
        exit(0);
    }
}

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binaryPower(u64 base, u64 e, u64 mod)
{
    u64 result = 1;
    base %= mod;
    while (e)
    {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool checkComposite(u64 n, u64 a, u64 d, int s)
{
    u64 x = binaryPower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    auto xCopy = x;
    for (int r = 1; r < s; ++r)
    {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(u64 n)
{
    const int iter = 16;
    if (n < 4)
        return n == 2 || n == 3;
    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0)
    {
        d >>= 1;
        s++;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if (n == a)
            return true;
        if (checkComposite(n, a, d, s))
            return false;
    }
    return true;
}

void solveCase()
{
    int n;
    cin >> n;
    deque<int> divisors;
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0)
            if (n % i == 0)
            {
                divisors.pb(i);
                divisors.pb(n / i);
            }
    sort(all(divisors));
    divisors.resize(unique(all(divisors)) - divisors.begin());
    if (divisors.size() && divisors.front() == 1)
        divisors.pop_front();
    db(divisors);
    int sz = divisors.size();
    vector<int> used(sz, 0);
    auto search_and_mark = [&](int x) -> bool {
        auto it = lower_bound(all(divisors), x);
        if (it == divisors.end())
            return false;
        auto &prev = used[it - divisors.begin()];
        // db("search_and_mark", x, prev);
        return prev ? 0 : (prev = 1);
    };
    vector<int> res;
    for (size_t i = 0; i < sz; i++)
    {
        if (used[i] || !MillerRabin(divisors[i]))
            continue;
        int j = i + 1;
        j %= sz;
        while (true)
        {
            if (MillerRabin(divisors[j]))
                break;
            ++j;
            j %= sz;
        }
        deque<int> temp;
        db(i, j);
        for (size_t k = 0; k < sz; k++)
        {
            if (divisors[k] % (divisors[i] * divisors[j]) == 0)
                if (search_and_mark(divisors[k]))
                {
                    temp.push_back(divisors[k]);
                    break;
                }
        }
        db(i, divisors[i], temp, used);
        if (search_and_mark(divisors[i]))
            res.pb(divisors[i]);
        for (auto &x : temp)
            res.pb(x);
    }
    vector<int> tempRes;
    for (size_t i = 0; i < res.size(); i++)
    {
        tempRes.pb(res[i]);
        for (size_t k = 0; k < divisors.size(); k++)
        {
            if (used[k])
                continue;
            if (__gcd(divisors[k], res[i]) > 1)
                if (__gcd(divisors[k], res[(i + 1) % res.size()]) > 1)
                {
                    tempRes.pb(divisors[k]);
                    used[k] = 1;
                }
        }
    }
    res = tempRes;
    for (auto &x : res)
        cout << x << ' ';
    cout << '\n';
    auto check = [&]() -> int {
        int ret = 0;
        for (size_t i = 0; i < res.size(); i++)
        {
            int curr = __gcd(res[i], res[(1 + i) % res.size()]);
            db(i, res[i], res[(1 + i) % res.size()], curr);
            if (curr == 1)
                ret++;
        }
        return ret;
    };
    cout << check() << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
