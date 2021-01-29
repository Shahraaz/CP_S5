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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Bit
{
    int size;
    vector<ordered_set<int>> table;
    Bit(int size)
    {
        this->size = size;
        table.resize(size);
    }
    void add(int i, int delta)
    {
        while (i < size)
        {
            // table[i] += delta;
            table[i].insert(delta);
            i = i | (1 + i);
        }
    }
    void remove(int i, int delta)
    {
        while (i < size)
        {
            // table[i] += delta;
            table[i].erase(delta);
            i = i | (1 + i);
        }
    }
    int sum(int i, int x)
    {
        // db(i, x);
        int ret = 0;
        while (i >= 0)
        {
            // ret += table[i];
            //             db(i, x);
            // #ifdef LOCAL
            //             for (auto &x : table[i])
            //                 cout << x << ' ';
            //             cout << '\n';
            // #endif
            ret += table[i].order_of_key(x);
            i = (i & (i + 1)) - 1;
        }
        // db(ret);
        return ret;
    }
};

void solveCase()
{
    int n = 2e5, m = 2e5;
    cin >> n >> m;
    vector<int> a(n), b(n), inv_a(n), nice_array(n);
    for (size_t i = 0; i < n; i++)
    {
        int x = i;
        cin >> x;
        --x;
        a[i] = x;
        inv_a[x] = i;
    }
    Bit bit(NAX);
    for (size_t i = 0; i < n; i++)
    {
        int x = i;
        cin >> x;
        --x;
        b[i] = x;
        nice_array[i] = inv_a[b[i]];
        bit.add(i, nice_array[i]);
    }
    db(a);
    db(inv_a);
    db(b);
    db(nice_array);
    // db(mysets);
    for (size_t i = 0; i < m; i++)
    {
        int ch = 1;
        cin >> ch;
        if (ch == 1)
        {
            int la = 1, ra = n, lb = 2, rb = n - 1;
            cin >> la >> ra >> lb >> rb;
            --la, --lb, --ra, --rb;
            db(la, ra, lb, rb);
            // printf("%d\n",calc(la, ra, lb, rb));
            // cout << calc(la, ra, lb, rb) << '\n';
            db(nice_array);
            auto res_rb = bit.sum(rb, ra + 1) - bit.sum(rb, la);
            auto res_lb = bit.sum(lb - 1, ra + 1) - bit.sum(lb - 1, la);
            db(res_rb, res_lb);
            cout << res_rb - res_lb << '\n';
        }
        else
        {
            int x, y;
            cin >> x >> y;
            --x, --y;
            // mysets[x / B].erase(nice_array[x]);
            // mysets[y / B].erase(nice_array[y]);
            bit.remove(x, nice_array[x]);
            bit.remove(y, nice_array[y]);
            swap(nice_array[x], nice_array[y]);
            bit.add(x, nice_array[x]);
            bit.add(y, nice_array[y]);
            // mysets[x / B].insert(nice_array[x]);
            // mysets[y / B].insert(nice_array[y]);
        }
    }
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