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
    string s;
    cin >> s;
    if (s[0] == '1')
    {
        bool check = true;
        for (size_t i = 1; i + 1 < s.size(); i++)
            check = check && s[i] == '0';
        if (s.back() > '1')
            check = false;
        if (check)
        {
            for (size_t i = 2; i < s.size(); i++)
                cout << 9;
            cout << '\n';
            return;
        }
    }
    int curr = 0;
    for (size_t i = 0; i < s.size(); i++)
        curr ^= 1 << (s[i] - '0');
    db(s, bitset<10>(curr));
    for (int i = s.size() - 1; i >= 0; i--)
    {
        curr ^= 1 << (s[i] - '0');
        db(i, bitset<10>(curr));
        int c = s[i] - '0';
        for (int j = c - 1; j >= 0; j--)
        {
            int now = curr ^ (1 << j);
            int cnt = __builtin_popcount(now);
            db(i, j, bitset<10>(now));
            if (cnt > s.size() - 1 - i)
                continue;
            string ans = s.substr(0, i);
            ans += char('0' + j);
            int lf = s.size() - 1 - i;
            while (lf > cnt)
            {
                lf -= 2;
                ans += "99";
            }
            for (int i = 10 - 1; i >= 0; i--)
            {
                if (now & (1 << i))
                    ans += char('0' + i);
            }
            cout << ans << '\n';
            return;
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
