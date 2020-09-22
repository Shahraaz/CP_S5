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
    int find_order(int k)
    {
        int low = 0, high = size - 1;
        int ans = high;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (sum(mid) >= k)
            {
                ans = min(ans, mid);
                high = mid - 1;
            }
            else
                low = mid + 1;
        }
        return ans;
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

void solveCase()
{
    int n, q;
    cin >> n >> q;
    Bit b(n + 1);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        b.update(x, 1);
    }
    for (size_t i = 0; i < q; i++)
    {
        int x;
        cin >> x;
        if (x > 0)
        {
            b.update(x, 1);
            n++;
        }
        else
        {
            x = -x;
            n--;
            b.update(b.find_order(x), -1);
        }
    }
    if (n)
        cout << b.find_order(1) << '\n';
    else
        cout << 0 << '\n';
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
