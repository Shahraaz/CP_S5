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
    string a, b;
    cin >> a >> b;
    int res = 0;
    bool cnting = false;
    for (size_t i = 0; i < a.size(); i += 2)
    {
        if (a[i] == b[i])
        {
            if (cnting)
                cnting = false, res++;
        }
        else
        {
            cnting = true;
        }
    }
    if (cnting)
        cnting = false, res++;
    for (size_t i = 1; i < a.size(); i += 2)
    {
        if (a[i] == b[i])
        {
            if (cnting)
                cnting = false, res++;
        }
        else
        {
            cnting = true;
        }
    }
    if (cnting)
        cnting = false, res++;
    cout << res << '\n';
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