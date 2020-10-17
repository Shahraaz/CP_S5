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
    string str;
    cin >> str;
    ll res = 0;
    auto rev = str;
    reverse(all(rev));
    db(rev);
    deque<int> poses[27];
    for (size_t i = 0; i < n; i++)
        poses[str[i] - 'a'].pb(i);
    Bit b(n + 2);
    for (int i = 0; i < n; i++)
    {
        char j = rev[i];
        db(i, j);
        db(poses[j - 'a']);
        auto idx = poses[j - 'a'].front();
        poses[j - 'a'].pop_front();
        int realIdx = idx + b.sum(idx);
        db(idx, realIdx);
        res += realIdx - i;
        b.update(0, 1);
        b.update(idx, -1);
        b.print();
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
