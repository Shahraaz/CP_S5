// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = __int128;
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

struct Bit
{
    int size;
    vector<ll> table;
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
    ll sum(int i)
    {
        i = min(i, (int)table.size() - 1);
        ll ret = 0;
        while (i >= 0)
        {
            ret += table[i];
            i = (i & (i + 1)) - 1;
        }
        return ret;
    }
    ll rangeSum(int i, int j)
    {
        if (i == 0)
            return sum(j);
        return sum(j) - sum(i - 1);
    }
    void print()
    {
#ifdef LOCAL
        // for (int i = 0; i < size; i++)
        //     cout << rangeSum(i, i) << ' ';
        // cout << '\n';
#else

#endif
    }
};

std::ostream &
operator<<(std::ostream &dest, __int128_t value)
{
    std::ostream::sentry s(dest);
    if (s)
    {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = std::end(buffer);
        do
        {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0)
        {
            --d;
            *d = '-';
        }
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len)
        {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> ranges;
    vector<int> inp;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        inp.pb(x);
        ranges.pb(x - 3);
        ranges.pb(x - 2);
        ranges.pb(x - 1);
        ranges.pb(x);
        ranges.pb(x + 1);
        ranges.pb(x + 2);
        ranges.pb(x + 3);
    }
    sort(all(ranges));
    ranges.erase(unique(all(ranges)), ranges.end());
    Bit sumBit(ranges.size());
    Bit cntBit(ranges.size());
    ll res = 0;
    db(ranges);
    for (int i = n - 1; i >= 0; i--)
    {
        auto idx = lower_bound(all(ranges), inp[i] + 2) - ranges.begin();
        ll a = sumBit.rangeSum(idx, ranges.size());
        ll b = cntBit.rangeSum(idx, ranges.size());
        res += (a - b * inp[i]);

        idx = lower_bound(all(ranges), inp[i] - 2) - ranges.begin();
        a = sumBit.rangeSum(0, idx);
        b = cntBit.rangeSum(0, idx);
        res += (a - inp[i] * b);

        idx = lower_bound(all(ranges), inp[i]) - ranges.begin();
        sumBit.update(idx, inp[i]);
        cntBit.update(idx, 1);
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
