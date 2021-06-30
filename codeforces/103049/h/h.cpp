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
    int n;
    cin >> n;
    vector<int> t(n);
    for (auto &x : t)
        cin >> x;
    sort(all(t));
    int fptr = 0, rptr = n - 1, turn = false;
    vector<int> res;
    while (fptr <= rptr)
    {
        if (turn)
            res.pb(t[fptr++]);
        else
            res.pb(t[rptr--]);
        //     cout << t[fptr++] << ' ';
        // else
        //     cout << t[rptr--] << ' ';
        turn = !turn;
    }
    reverse(all(res));
    for (auto &x : res)
        cout << x << ' ';
    cout << '\n';
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