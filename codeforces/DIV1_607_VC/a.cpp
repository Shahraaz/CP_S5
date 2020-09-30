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
    int x;
    cin >> x;
    string str;
    cin >> str;
    // str = "$" + str;
    ll len = str.size();
    auto append = [&](int pos, int time) {
        // db(pos, time);
        ll tempLern = len - pos - 1;
        tempLern %= MOD;
        if (tempLern < 0)
            tempLern += MOD;
        for (size_t i = 0; i < time; i++)
        {
            len += tempLern;
            len %= MOD;
        }
        if (str.size() < x)
        {
            auto suff = str.substr(pos + 1);
            for (size_t i = 0; i < time; i++)
                str += suff;
        }
    };
    // db(str, x);
    for (size_t i = 0; i < x; i++)
    {
        // db(i, x, len);
        int cnt = str[i] - '1';
        append(i, cnt);
    }
    // cout << str << '\n';
    cout << len << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
