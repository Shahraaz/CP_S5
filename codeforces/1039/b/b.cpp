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

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

void solveCase()
{
    ll n, k, p;
    n = 500000000000000000LL, k = 10, p = 238177452815227575;
    cin >> n >> k;
    ll low = 1;
    ll high = n;
    int cnt = 0;

    auto ask = [&](ll l, ll r) -> string {
        cnt++;
        assert(cnt <= 450);
        cout << l << ' ' << r << endl;
        string str;

        cin >> str;
        // db(cnt, p);
        // if (l <= p && p <= r)
        //     str = "Yes";
        // else
        //     str = "No";
        // ptr = (ptr + 1) % n + 1;

        if (str == "Yes" && l == r)
            exit(0);
        return str;
    };
    // for (int i = 0; i < cnt; i++)
    while (true)
    {
        auto currlen = high - low + 1;
        auto nextlen = (currlen + 1) / 2 + 2 * k;
        db(low, high, currlen, nextlen);
        if (currlen <= 50 || currlen - nextlen <= k)
        {
            auto r = (Random<int>(0, high - low)(rng)) + low;
            auto res = ask(r, r);
            low = max(1LL, low - k);
            high = min(n, high + k);
        }
        else
        {
            auto mid = (low + high) >> 1;
            if (Random<int>(0, 1)(rng))
            {
                auto q = ask(1, mid);
                if (q == "Yes")
                {
                    low = max(1LL, low - k);
                    high = min(n, mid + k);
                }
                else
                {
                    low = max(1LL, mid - k);
                    high = min(n, high + k);
                }
            }
            else
            {
                auto q = ask(mid, n);
                if (q == "Yes")
                {
                    low = max(1LL, mid - k);
                    high = min(n, high + k);
                }
                else
                {
                    low = max(1LL, low - k);
                    high = min(n, mid + k);
                }
            }
        }
    }
    // assert(false);
}

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}