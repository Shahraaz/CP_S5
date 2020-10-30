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
        bit.assign(n + 1, 0);
    }

    void updateMax(int idx, long long val)
    {
        while (idx <= N)
        {
            bit[idx] = max(bit[idx], val);
            idx = idx | (1 + idx);
        }
    }

    long long prefMax(int idx)
    {
        long long ans = -2e9;
        while (idx > 0)
        {
            ans = max(ans, bit[idx]);
            idx = (idx & (idx + 1)) - 1;
        }
        return ans;
    }
};

int LIS(vector<int> a)
{
    int n = a.size();
    if (n == 0)
        return 0;
    db(a);
    auto aCopy = a;
    sort(all(aCopy));
    aCopy.resize(unique(all(aCopy)) - aCopy.begin());
    for (auto &x : a)
        x = lower_bound(all(aCopy), x) - aCopy.begin();
    BIT b;
    b.init(n + 2);
    for (size_t i = 0; i < n; i++)
    {
        auto prev = b.prefMax(a[i] + 1);
        if (prev < 0)
            prev = 0;
        b.updateMax(a[i] + 1, prev + 1);
    }
    auto res = b.prefMax(n + 1);
    db(res);
    return res;
}
void solveCase()
{
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 2);
    vector<bool> Fixed(n + 2);
    for (size_t i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> events;
    events.pb(0);
    for (size_t i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        events.pb(x);
        Fixed[x] = 1;
    }
    Fixed[0] = Fixed[n + 1] = 1;
    events.pb(n + 1);
    a[0] = -MOD, a[n + 1] = 2 * MOD;
    int res = 0;
    for (size_t i = 0; i + 1 < events.size(); i++)
    {
        int lptr = events[i], rptr = events[i + 1];
        if (a[rptr] - a[lptr] >= rptr - lptr)
        {
            vector<int> myList;
            int ptr = lptr + 1;
            while (ptr < rptr)
            {
                if ((a[lptr] - lptr) <= (a[ptr] - ptr) && (a[ptr] - ptr) <= (a[rptr] - rptr))
                    myList.pb(a[ptr] - ptr);
                else
                    res++;
                ++ptr;
            }
            res += myList.size() - LIS(myList);
        }
        else
        {
            cout << -1 << '\n';
            return;
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
