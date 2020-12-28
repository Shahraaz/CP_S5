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
        if(i < 0)
            i = 0;
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
    void print()
    {
#ifdef LOCAL
        for (int i = 0; i < size; i++)
            cout << sum(i) << ' ';
        cout << '\n';
#else

#endif
    }
};

void solveCase()
{
    int n;
    cin >> n;
    vector<int> b(n), a;
    vector<int> vis(2 * n);
    for (auto &x : b)
    {
        cin >> x;
        --x;
        vis[x] = 1;
    }
    sort(all(b));

    for (size_t i = 0; i < 2 * n; i++)
        if (!vis[i])
            a.pb(i);
    // for (size_t i = 0; i < n; i++)
    //     a.pb(a[i]);

    Bit bit(2 * n);
    for (int i = 0; i < n; i++)
    {
        auto it = lower_bound(a.begin(), a.begin() + n, b[i]) - a.begin();
        if (i <= it)
        {
            // it -= i;
            bit.update(it - i, 1);
            bit.update(n - i, -1);
        }
        else
        {
            bit.update(it - i, 1);
            bit.update(n - i, -1);

            int diff = i - it;
            bit.update(n - diff, 1);
            bit.update(n, -1);
        }
    }
    bit.print();
    set<int> myset;
    for (size_t i = 0; i < n; i++)
    {
        db(bit.sum(i));
        myset.insert(bit.sum(i));
    }
    cout << myset.size() << '\n';
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
        solveCase();
    return 0;
}