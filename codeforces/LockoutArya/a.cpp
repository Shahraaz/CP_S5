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

struct BIT
{
    int N;
    vector<long long> bit;

    void init(int n)
    {
        N = n;
        bit.assign(n + 1, MOD);
    }

    void update(int idx, long long val)
    {
        while (idx <= N)
        {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    void updateMin(int idx, long long val)
    {
        while (idx <= N)
        {
            bit[idx] = min(bit[idx], val);
            idx += idx & -idx;
        }
    }

    long long pref(int idx)
    {
        long long ans = 0;
        while (idx > 0)
        {
            ans += bit[idx];
            idx -= idx & -idx;
        }
        return ans;
    }

    long long rsum(int l, int r)
    {
        return pref(r) - pref(l - 1);
    }

    long long prefMin(int idx)
    {
        long long ans = 2e9;
        while (idx > 0)
        {
            ans = min(ans, bit[idx]);
            idx -= idx & -idx;
        }
        return ans;
    }
};

void solveCase()
{
    BIT forFirstOpen(1000001);
    BIT forFirstOpen(1000001);
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
