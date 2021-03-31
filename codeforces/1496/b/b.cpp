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
    set<int> a;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a.insert(x);
    }
    int mex = 0;
    while (a.find(mex) != a.end())
        ++mex;
    int i = 0;
    int prevmex = -1, prevmax = -1;
    for (i = 0; i < min(n, k); i++)
    {
        while (a.find(mex) != a.end())
            ++mex;
        int maxi = *a.rbegin();
        db(i, prevmex, prevmax, mex, maxi, a);
        if (prevmex == mex && prevmax == maxi)
            break;
        a.insert((mex + maxi + 1) / 2);
        prevmex = mex, prevmax = maxi;
    }
    k -= i;
    db(k);
    if (k == 0)
    {
        cout << a.size() << '\n';
    }
    else
    {
        while (a.find(mex) != a.end())
            ++mex;
        int maxi = *a.rbegin();
        db("c", prevmex, prevmax, mex, maxi, a);
        if (prevmex == mex && prevmax == maxi)
        {
            cout << a.size() << '\n';
        }
        else
        {
            cout << a.size() + k << '\n';
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
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}