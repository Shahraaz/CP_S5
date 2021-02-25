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

// If you don't need any of the fancy formatting options, writing your own << operator is trivial. Formally, I suspect that writing one for __int128_t would be considered undefined behavior, but practically, I think it would work, up until the library starts providing actual support for it (at which point, you'd retire your conversion operator).

// Anyway, something like the following should work:

std::ostream &operator<<(std::ostream &dest, __int128_t value)
{
    std::ostream::sentry s(dest);
    if (s)
    {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = std::end(buffer);
        do
        {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0)
        {
            --d;
            *d = '-';
        }
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len)
        {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

vector<__int128> f;

void pre()
{
    f.pb(1);
    // f.pb(1);
    __int128 curr = 1;
    while (curr < 1e25)
    {
        auto next = curr + f.back();
        db(curr, next);
        f.pb(curr);
        curr = next;
    }
    db(f);
    db(f.size());
}

void solveCase()
{
    pre();
    int n;
    cin >> n;
    vector<__int128> a(n);
    map<__int128, int> cnt;
    int res = 0;
    for (auto &x : a)
    {
        int y;
        cin >> y;
        x = y;
        db(x, y);
        // cin >> x;
        cnt[x]++;
        // res = max(res, cnt[x]);
    }
    // for (auto &x : cnt)
    // {
    //     int a = x.second;
    //     if (x.first == 0)
    //     {
    //         res = max(res, x.second);
    //         continue;
    //     }
    //     auto it = cnt.find(-x.first);
    //     if (it == cnt.end())
    //         continue;
    //     auto b = it->second;
    //     int zerocnt = cnt[0];
    //     zerocnt = min(zerocnt, a);
    //     int curr_cnt = 1;

    // }

    res = max(res, cnt[0]);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            __int128 f0 = a[i];
            __int128 f1 = a[j];

            // if ((f1 + f0) == 0)
            //     continue;

            if (f0 == 0 && f1 == 0)
                continue;

            auto f_n = [&](int idx) -> __int128 {
                if (idx == 1)
                    return f0;
                if (idx == 2)
                    return f1;
                return f0 * f[idx - 3] + f1 * f[idx - 2];
            };

            vector<__int128> curr_f;
            int idx = 1;
            while (true)
            {
                auto f_cnt = f_n(idx);
                db(f0, f1, idx, f_cnt);
                if (cnt[f_cnt] == 0)
                {
                    --idx;
                    break;
                }
                cnt[f_cnt]--;
                curr_f.pb(f_cnt);
                ++idx;
            }
            res = max(res, idx);
            for (auto &c : curr_f)
                cnt[c]++;
        }
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
        solveCase();
    return 0;
}