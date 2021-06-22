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
    int H, M;
    cin >> H >> M;
    map<char, char> mp;
    mp['0'] = '0';
    mp['1'] = '1';
    mp['2'] = '5';
    mp['5'] = '2';
    mp['8'] = '8';

    string tt;
    cin >> tt;
    int hh = (tt[0] - '0') * 10 + (tt[1] - '0');
    int mm = (tt[3] - '0') * 10 + (tt[4] - '0');
    auto valid = [&](int o, int LIM) -> bool
    {
        auto O = to_string(o);
        if (O.size() < 2)
            O = "0" + O;
        reverse(all(O));
        int r = 0;
        for (auto &x : O)
        {
            if (mp.count(x) == 0)
                return false;
            r = r * 10 + mp[x] - '0';
        }
        db(o, O, r);
        return r < LIM;
    };
    while (true)
    {
        if (valid(mm, H))
        {
            if (valid(hh, M))
            {
                break;
            }
        }
        ++mm;
        if (mm == M)
        {
            mm = 0;
            ++hh;
            if (hh >= H)
                hh = 0;
        }
    }
    if (hh < 10)
        cout << 0;
    cout << hh << ':';
    if (mm < 10)
        cout << 0;
    cout << mm << '\n';
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