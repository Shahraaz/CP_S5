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

vector<__int128_t> excess(70);

std::ostream &
operator<<(std::ostream &dest, __int128_t value)
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

void solveCase()
{
    int q;
    cin >> q;
    for (size_t i = 0; i < q; i++)
    {
        ll t, x, k;

        cin >> t >> x;

        if (t == 1)
        {
            cin >> k;
            db(t, x, k);
            // k = -k;

            int level = __lg(x);

            excess[level] += k;
            __int128_t MOD = __int128_t(1) << level;
            excess[level] = (excess[level] % MOD + MOD) % MOD;

            excess[level + 1] -= 2 * k;
            MOD = __int128_t(1) << (level + 1);
            excess[level + 1] = (excess[level + 1] % MOD + MOD) % MOD;
        }
        else if (t == 2)
        {
            cin >> k;
            db(t, x, k);
            // k = -k;

            int level = __lg(x);

            excess[level] += k;
            __int128_t MOD = __int128_t(1) << level;
            excess[level] = (excess[level] % MOD + MOD) % MOD;
        }
        else
        {
            db(t, x);
            int level = __lg(x);
            while (x > 0)
            {
                cout << x << ' ';
                __int128_t MOD = __int128_t(1) << level;
                x -= MOD;
                db(x, level, excess[level], MOD);
                x = MOD + (x + excess[level]) % MOD;
                x = x / 2;
                level--;
                if (level < 0)
                    break;
            }
            cout << '\n';
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}