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

void solveCase()
{
    int n, k;
    cin >> n >> k;
    vector<int> base(n);
    int lptr = 0, dx = 1;
    for (size_t i = 0; i < n; i++)
    {
        base[i] = lptr;
        lptr += dx;
        if (lptr == k)
        {
            dx = -1;
            lptr = k - 2;
        }
    }
    deque<int> res;
    int rptr = base.back();
    for (size_t i = 0; i < rptr; i++)
        res.pb(i);
    rptr = k - 1;
    while (res.size() < k)
    {
        res.pb(rptr);
        --rptr;
    }
    for (auto &x : res)
    {
        cout << x + 1 << ' ';
    }
    cout << '\n';

    // db(n, k);
    // db(base);
    // vector<int> p(k);
    // for (size_t i = 0; i < k; i++)
    //     p[i] = i;
    // vector<vector<int>> pres = {p};
    // auto inv_cnt = [&](vector<int> p) -> ll {
    //     ll res = 0;
    //     auto base2 = base;
    //     for (auto &x : base2)
    //         x = p[x];
    //     for (size_t i = 0; i < base2.size(); i++)
    //         for (size_t j = i + 1; j < base2.size(); j++)
    //             res += base2[i] > base2[j];
    //     // db(p, res);
    //     return res;
    // };
    // ll invcnt = MOD, fixed = inv_cnt(p);
    // do
    // {
    //     auto curr = inv_cnt(p);
    //     if (invcnt > curr && curr <= fixed)
    //     {
    //         invcnt = curr;
    //         pres = {p};
    //     }
    //     else if (invcnt == curr)
    //         pres = {p};
    // } while (next_permutation(all(p)));
    // db(invcnt);
    // db(pres);
    // assert(pres.size() == 1);
    // for (auto &x : pres[0])
    //     cout << x + 1 << ' ';
    // cout << '\n';
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