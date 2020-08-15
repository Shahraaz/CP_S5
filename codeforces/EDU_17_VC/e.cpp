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

const int NAX = 1e4 + 5, MOD = 1000000007;

const int NNN = 3e5 + 1;
struct Bit
{
    int size;
    vector<int> table;
    Bit(int size = 1)
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
        if (i >= size)
            i = size - 1;
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
        if (i <= 0)
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

int n, k;
// int x[NAX], r[NAX], f[NAX];
vector<vector<int>> vecc;
vector<int> indexer[NAX];
const int FMAX = 1e4 + 1;
Bit bits[NAX];

struct Solution
{
    Solution() {}
    void solveCase()
    {
        cin >> n >> k;
        for (size_t i = 0; i < n; i++)
        {
            int x, r, f;
            cin >> x >> r >> f;
            vecc.pb({-r, x, f});
            for (int j = -k; j <= k; j++)
            {
                int f1 = f + j;
                if (f1 < 0)
                    continue;
                if (f1 > FMAX)
                    continue;
                indexer[f1].pb(x);
                indexer[f1].pb(x - r);
                indexer[f1].pb(x + r);
            }
        }
        db("a");
        for (size_t i = 0; i < FMAX; i++)
        {
            int ptr = 1;
            // db(i);
            sort(all(indexer[i]));
            indexer[i].erase(unique(all(indexer[i])), indexer[i].end());
            bits[i] = Bit(indexer[i].size() + 10);
        }
        db("b");
        sort(all(vecc));
        ll res = 0;
        for (auto &tower : vecc)
        {
            int r = -tower[0];
            int x = tower[1];
            int f = tower[2];
            int low = x - r;
            int high = x + r;
            db(r, f, x, low, high);
            for (int i = -k; i <= k; i++)
            {
                int f1 = f + i;
                if (f1 < 0)
                    continue;
                if (f1 > FMAX)
                    continue;
                // bits[f1].print();
                // db(indexer[f1][low], indexer[f1][high]);
                auto l = lower_bound(all(indexer[f1]), low) - indexer[f1].begin();
                auto h = lower_bound(all(indexer[f1]), high) - indexer[f1].begin();
                db(i, l, h);
                res += bits[f1].rangeSum(l, h);
            }
            bits[f].update(lower_bound(all(indexer[f]), x) - indexer[f].begin(), 1);
        }
        cout << res << '\n';
    }
};

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
