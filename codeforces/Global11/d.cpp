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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<vector<int>> res;
    auto perform = [&](vector<int> vecc) {
        if (vecc.size() <= 1)
            return;
        db(vecc);
        vector<vector<int>> arr;
        int sz = 0;
        res.pb(vecc);
        // cout << vecc.size() << ' ';
        for (size_t i = 0; i < vecc.size(); i++)
        {
            vector<int> temp;
            // cout << vecc[i] << ' ';
            while (vecc[i]--)
                temp.pb(a[sz++]);
            arr.pb(temp);
        }
        // cout << '\n';
        db(arr);
        reverse(all(arr));
        sz = 0;
        for (auto &x : arr)
            for (auto &y : x)
                a[sz++] = y;
        db(a);
    };
    bool isF = n & 1;
    // cout << n << '\n';
    for (int i = 1; i <= n; i++)
    {
        vector<int> Q;
        int idxi = find(all(a), i) - a.begin();
        int idxim = find(all(a), i - 1) - a.begin();
        // db(i, a, idxi, idxim, isF);
        int ptr = 0;
        if (isF)
        {
            if (i == 1)
                idxim = n;
            db(i, a, idxi, idxim, isF);
            while (ptr < idxi)
            {
                Q.pb(1);
                ++ptr;
            }
            Q.pb(idxim - idxi);
            int len = n - idxim;
            while (len > 0)
            {
                Q.pb(1);
                len--;
            }
        }
        else
        {
            if (i == 1)
            {
                idxim = 0;
                db(i, a, idxi, idxim, isF);
                while (ptr < idxim)
                {
                    Q.pb(1);
                    ++ptr;
                }
                Q.pb(idxi - idxim + 1);
                int len = n - idxi - 1;
                while (len > 0)
                {
                    Q.pb(1);
                    len--;
                }
            }
            else
            {
                db(i, a, idxi, idxim, isF);
                while (ptr <= idxim)
                {
                    Q.pb(1);
                    ++ptr;
                }
                Q.pb(idxi - idxim);
                int len = n - idxi - 1;
                while (len > 0)
                {
                    Q.pb(1);
                    len--;
                }
            }
        }
        db(Q);
        isF = !isF;
        perform(Q);
    }
    cout << res.size() << '\n';
    for (auto &x : res)
    {
        cout << x.size() << ' ';
        for (auto &y : x)
        {
            cout << y << ' ';
        }
        cout << '\n';
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
