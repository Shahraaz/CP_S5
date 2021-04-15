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
    vector<pair<int, int>> o, e;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            if ((i + j) & 1)
                o.pb({i, j});
            else
                e.pb({i, j});
    auto read = [&]() -> int {
        int x;
        cin >> x;
        if (x == 3)
            return o.size() ? 1 : 2;
        if (o.size() && e.size())
            return 1 ^ 2 ^ x;
        if (o.size())
            return x == 1 ? 3 : 1;
        assert(e.size());
        return x == 2 ? 3 : 2;
    };
    for (size_t i = 0; i < n * n; i++)
    {
        int x = read();
        pair<int, int> p;
        if (x == 1)
        {
            assert(o.size());
            p = o.back();
            o.pop_back();
        }
        else if (x == 2)
        {
            assert(e.size());
            p = e.back();
            e.pop_back();
        }
        else
        {
            assert(e.size() || o.size());
            if (o.size())
            {
                p = o.back();
                o.pop_back();
            }
            else
            {
                p = e.back();
                e.pop_back();
            }
        }
        cout << x << ' ' << p.first + 1 << ' ' << p.second + 1 << endl;
        cout.flush();
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
        solveCase();
    return 0;
}