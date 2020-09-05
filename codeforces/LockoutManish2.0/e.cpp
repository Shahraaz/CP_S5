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
        return sum(j) - sum(i - 1);
    }
    void print()
    {
#ifdef LOCAL
        for (int i = 0; i < size; i++)
            cout << rangeSum(i, i) << ' ';
        cout << '\n';
#else

#endif
    }
};

void Solution::solveCase()
{
    int q;
    cin >> q;
    vector<pair<int, int>> vecc;
    vector<ll> ranges;
    for (size_t i = 0; i < q; i++)
    {
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            int x;
            cin >> x;
            vecc.pb({ch, x});
            ranges.pb(x);
        }
        else
        {
            vecc.pb({ch, 0});
            // ranges.pb(x);
        }
    }
    for (size_t i = 1; i < ranges.size(); i++)
        ranges[i] += ranges[i - 1];

    // ranges.erase(unique(all(ranges)), ranges.end());
    pair<int, int> mostRecent;
    int currPresent = 0;
    db(vecc);
    for (int i = 0; i < q; ++i)
    {
        int ch = vecc[i].f;
        if (ch == 1)
        {
            currPresent++;
            mostRecent.f = vecc[i].s;
        }
        else
        {
            int low = 0, high = i + 1;
            long double res = 0;
            db(i);
            auto check = [&](int num) -> long double {
                if (num <= 1 || num > currPresent)
                    return 0;
                num--;
                long long sum = mostRecent.f;
                if (num > 0)
                    sum += ranges[num - 1];
                num++;
                db(num, mostRecent.f, sum / (0.0 + num));
                return mostRecent.f - sum / (0.0 + num);
            };
            while (low + 10 <= high)
            {
                int mid1 = low + low + high;
                mid1 /= 3;
                int mid2 = low + high + high;
                mid2 /= 3;
                if (check(mid1) < check(mid2))
                    low = mid1;
                else
                    high = mid2;
            }
            while (low <= high)
            {
                res = max(res, check(low));
                low++;
            }
            cout << fixed << setprecision(9);
            cout << res << '\n';
        }
    }
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    cerr << fixed << setprecision(9);
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
