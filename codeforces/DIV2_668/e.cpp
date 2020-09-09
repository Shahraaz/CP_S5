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
    vector<int> table;
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
    int sum(int i)
    {
        int ret = 0;
        while (i >= 0)
        {
            ret += table[i];
            i = (i & (i + 1)) - 1;
        }
        return ret;
    }
    int rangeSum(int i, int j)
    {
        if (i == 0)
            return sum(j);
        return sum(j) - sum(i - 1);
    }
    void print(int off = 0)
    {
#ifdef LOCAL
        for (int i = 0; i < size; i++)
            cout << rangeSum(0, i) + off << ' ';
        cout << '\n';
#else

#endif
    }
};

void Solution::solveCase()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        --a[i];
        a[i] = i - a[i];
        // cout << i - a[i] << ' ';
    }
    vector<int> Queries[n + 1];
    vector<int> ans(q), leftBound(q);
    for (size_t i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        leftBound[i] = x;
        Queries[n - y - 1].pb(i);
    }
    int global = 0;
    Bit b(n);
    db(a);
    for (size_t r = 0; r < n; r++)
    {
        int targ = a[r];
        if (targ >= 0 && targ <= global)
        {
            int low = 0, high = r, ans = 0;
            while (low <= high)
            {
                int mid = low + high;
                mid /= 2;
                int currVal = global + b.sum(mid);
                // db(mid, currVal, targ);
                if (currVal >= targ)
                {
                    low = mid + 1;
                    ans = max(ans, mid);
                }
                else
                    high = mid - 1;
            }
            b.print(global);
            db(r, targ, ans);
            ++global;
            b.update(ans + 1, -1);
        }
        for (auto &iQ : Queries[r])
            ans[iQ] = global + b.sum(leftBound[iQ]);
    }
    b.print(global);

    for (auto &x : ans)
    {
        cout << x << '\n';
    }
    // cout << '\n';
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
