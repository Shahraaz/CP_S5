// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

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

struct event
{
    int x, ly, ry, coef, id;
    event(int x, int ly, int ry, int coef, int id)
    {
        this->x = x;
        this->ly = ly;
        this->ry = ry;
        this->coef = coef;
        this->id = id;
    }
    bool operator<(const event &rhs) const
    {
        // if (x == rhs.x)
        //     return coef > rhs.coef;
        return x < rhs.x;
    }
};

ostream &operator<<(ostream &out, const event &e)
{
    out << "x " << e.x << " ly " << e.ly << " ry " << e.ry << " coef " << e.coef << " id " << e.id;
    return out;
}

int a[NAX], inva[NAX];
vector<int> d[NAX];
int ans[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
            inva[a[i]] = i;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; i * j <= n; j++)
                d[inva[i * j]].pb(inva[i]);
        vector<event> evs;
        for (size_t i = 0; i < m; i++)
        {
            int l, r;
            cin >> l >> r;
            --l, --r;
            if (l)
                evs.push_back(event(l - 1, l, r, -1, i));
            evs.push_back(event(r, l, r, 1, i));
        }
        sort(all(evs));
        pc(evs);
        int ptr = 0;
        Bit b(n + 1);
        for (size_t i = 0; i < n; i++)
        {
            db(i);
            pc(d[i]);
            b.print();
            for (size_t j = 0; j < d[i].size(); j++)
            {
                db(d[i][j]);
                b.update(d[i][j], 1);
                b.print();
            }
            while (ptr < evs.size() && evs[ptr].x == i)
            {
                db(evs[ptr]);
                ans[evs[ptr].id] += evs[ptr].coef * b.rangeSum(evs[ptr].ly, evs[ptr].ry);
                ++ptr;
            }
        }
        for (size_t i = 0; i < m; i++)
            cout << ans[i] << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}