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

const int NAX = 3e5 + 5, MOD = 1000000007;

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
        if (i == 0)
            return sum(j);
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

int a[NAX];
int count_of_divisors[1000000 + 1];
set<pair<int, int>> greater_than_storage;
Bit one(NAX), two(NAX), greater_than_two(NAX);

void update(int ql, int qr)
{
    vector<pair<int, int>> temp;
    while (true)
    {
        auto low = greater_than_storage.lower_bound({ql, a[ql]});
        // auto up = greater_than_storage.lower_bound({qr, a[qr]});
        if (low == greater_than_storage.end())
            break;
        if (low->f > qr)
            break;
        int idx = low->f;
        int val = low->s;
        greater_than_two.update(idx, -val);
        greater_than_storage.erase(low);
        val = count_of_divisors[val];
        temp.pb({idx, val});
    }
    for (auto &x : temp)
    {
        a[x.f] = x.s;
        if (x.s == 1)
            one.update(x.f, 1);
        else if (x.s == 2)
            two.update(x.f, 2);
        else
        {
            greater_than_storage.insert(x);
            greater_than_two.update(x.f, x.s);
        }
    }
}

ll query(int ql, int qr)
{
    return one.rangeSum(ql, qr) + two.rangeSum(ql, qr) + greater_than_two.rangeSum(ql, qr);
}

void solveCase()
{
    for (int i = 1; i <= 1000000; ++i)
        for (size_t j = i; j <= 1000000; j += i)
            count_of_divisors[j]++;
    int n, m;
    cin >> n >> m;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] == 1)
            one.update(i, 1);
        else if (a[i] == 2)
            two.update(i, 2);
        else
        {
            greater_than_two.update(i, a[i]);
            greater_than_storage.insert({i, a[i]});
        }
    }
    for (size_t i = 0; i < m; i++)
    {
        int t, l, r;
        cin >> t >> l >> r;
        --l, --r;
        if (t == 1)
            update(l, r);
        else
            cout << query(l, r) << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
