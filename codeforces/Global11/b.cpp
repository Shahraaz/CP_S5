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

void solveCase()
{
    int n, k;
    string bs;
    cin >> n >> k;
    cin >> bs;
    if (count(all(bs), 'L') == n)
    {
        if (n <= k)
            cout << 2 * n - 1 << '\n';
        else
            cout << max(0, 2 * k - 1) << '\n';
        return;
    }
    vector<vector<int>> ss;
    ll res = 0;
    int lleft = 0, rright = 0;
    for (int i = 0; i < n;)
    {
        if (bs[i] == 'W')
        {
            ++i;
            continue;
        }
        int j = i;
        while (j < n && bs[j] == 'L')
            j++;
        db(i, j);
        int left = 0, right = 0;
        if (j < n && bs[j] == 'W')
            right = 1;
        if (i - 1 >= 0 && bs[i - 1] == 'W')
            left = 1;
        db(bs, i, j, left, right);
        if (left == 0)
            lleft = j - i;
        else if (right == 0)
            rright = j - i;
        else
            ss.pb({j - i,
                   j - i + j - i - 1 + left + right,
                   i});
        i = j;
    }
    sort(all(ss));
    db(ss);
    db(bs);
    char prev = 'L';
    for (size_t i = 0; i < n; i++)
    {
        if (bs[i] == 'W')
            res += 1 + (prev == 'W');
        prev = bs[i];
    }
    ll tempRes = 0;
    int tempK = k, ptr = 0;
    if (lleft)
        ss.pb({lleft, 2 * lleft});
    if (rright)
        ss.pb({rright, 2 * rright});
    db(ss, res);
    while (tempK > 0)
    {
        if (ptr == ss.size())
            break;
        if (ss[ptr][0] <= tempK)
        {
            tempRes += ss[ptr][1];
            tempK -= ss[ptr][0];
        }
        else
        {
            tempRes += 2 * tempK;
            // tempK -= ss[ptr][0];
            tempK = 0;
        }
        ++ptr;
    }
    cout << res + tempRes << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
